# ICC bug and MASM oddity. Converting vmlatency to Windows.

For my PhD thesis I wrote a simple tool to measure VM-entry and VM-exit turnaround time - [vmlatency](https://github.com/yulyugin/vmlatency). The tool was initially implemented for Linux only. Later ported to macOS. Windows port wan't finished because I have other activities to deal with prior to the PhD defense. In 2021 I ported the tool on Windows but the port only worked with ICC compiler. The main reason for using ICC compiler is that inline assembler was used a lot to run different processor instructions.

In spring 2022 I finally had time to make vmlatency work with Microsoft compiler. It is well known that Microsoft compiler only supports inline assembler for x86 but not x64 architecture. Microsoft's inline assembler is also completely different compared to GNU inline assembler. Obvious decision here was to use as much intrinsics as possible to avoid writing all the wrappers around processor instructions in [MASM](https://docs.microsoft.com/cpp/assembler/masm/masm-for-x64-ml64-exe) assembler. It was impossible to avoid assembler completely as some instructions are not available through intrinsics.

To make the transition more gradual and easier to debug I decided to convert all inline assembly-based instructions wrappers to intrinsics or assembler one by one while still compiling with ICC until everything is converted and can be compiled with Microsoft compiler.

# Buggy ICC intrinsics

As noted above, not all needed instructions are available as intrinsics but it's obviously better to use intrinsics for those that are. All VMX instructions for example have corresponding intrinsics.

The first problem I found was with `__vmx_off` intrinsic. I rewrote my `VMXOFF` instruction wrapper to look like this:

```
static inline void
__vmxoff(void)
{
#ifdef WIN32
        __vmx_off();
#else
        __asm__ __volatile__("vmxoff");
#endif
}
```

Recompiled the tool using ICC, ran the tool and... The host rebooted.

I looked at Windows kernel dump while being a little bit surprised to see the reboot assuming I shouldn't have changed the tool's behavior. Windows debugger showed that the crash is caused by an unhandled exception:

```
SYSTEM_THREAD_EXCEPTION_NOT_HANDLED (7e)
This is a very common bugcheck.  Usually the exception address pinpoints
the driver/function that caused the problem.  Always note this address
as well as the link date of the driver/image that contains this address.
Arguments:
Arg1: ffffffffc0000096, The exception code that was not handled
Arg2: fffff8026b94238b, The address that the exception occurred at
Arg3: fffffe0d863c1de8, Exception Record Address
Arg4: fffffe0d863c1630, Context Record Address
<...omitted...>
EXCEPTION_CODE: (NTSTATUS) 0xc0000096 - {EXCEPTION}  Privileged instruction.

FAULTING_IP: 
vmlatency+238b
fffff802`6b94238b 480f22e0        mov     cr4,rax
```

The code above corresponds to this source line:

```
__set_cr4(__get_cr4() & ~CR4_VMXE);
```

Clearing `CR4.VMXE` bit caused an exception which may only happen if the logical processor was in VMX root mode (see [SDM](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)). Thus, `VMXOFF` instruction never executed in the setup. Manual inspection of the driver binary confirmed that the instruction was not present in the binary. That was interesting and definitely needed additional investigation to understand what's going on.

## Do not use `static inline` wrappers for intrinsics

Direct usage of the intrinsic instead of the `static inline` wrapper executed with not issues. Manual inspection confirmed - `VMXOFF` instruction was used by the driver. Here is the change:

```
diff --git a/vmm/vmx.c b/vmm/vmx.c
index 996b450..8082900 100644
--- a/vmm/vmx.c
+++ b/vmm/vmx.c
@@ -135,7 +135,7 @@ static inline void
 do_vmxoff(vm_monitor_t *vmm)
 {
         if (vmm->our_vmxon)
-                __vmxoff();
+                __vmx_off();

         /* Clear CR4.VMXE if necessary */
         if (!vmm->old_vmxe)
```

## Compiling with no optimizations

I also modified the build script to compile the driver with no optimization. Expectedly, this fixed the issue.

```
diff --git a/vmm/sources b/vmm/sources
index 1fc6586..114b1d3 100644
--- a/vmm/sources
+++ b/vmm/sources
@@ -3,3 +3,5 @@ TARGETTYPE=DRIVER_LIBRARY
 TARGETPATH=../build-$(DDK_TARGET_OS)-$(DDKBUILDENV)

 SOURCES=vmx.c
+
+MSC_OPTIMIZATION=/O0
```

Optimization level `/O1` removes the instruction.

## Looking at optimization report

ICC can generate an optimization report with [`/Qopr-report`](https://www.intel.com/content/www/us/en/develop/documentation/cpp-compiler-developer-guide-and-reference/top/compiler-reference/compiler-options/optimization-report-options/qopt-report-qopt-report.html) option.

Optimization report clearly indicated that call to the function containing `VMXOFF` intrinsic was removed by [interprocedural optimizations](https://www.intel.com/content/www/us/en/develop/documentation/cpp-compiler-developer-guide-and-reference/top/compiler-reference/compiler-options/interprocedural-optimization-options/ip-qip.html).

```
Begin optimization report for: measure_vmlatency()

    Report from: Interprocedural optimizations [ipo]

INLINE REPORT: (measure_vmlatency()) [43] c:\users\Evgenii\vmlatency\vmm\vmx.c(490,1)

<part of uninteresting output omitted>

  -> INLINE: (542,9) do_vmxoff(vm_monitor_t *)
    -> DELETED: (138,17) __vmxoff(void)
    -> INLINE: (142,17) __set_cr4(u64)
```

It seemed that interprocedural optimizations decided that the intrinsic wrapped in a function had no effect on processor state and removed it as dead code.

As expected, once interprocedural optimizations were disabled (`/Qip-` option) `VMXOFF` was back in the binary.

## Conclusions

The behavior described [above](#buggy-icc-intrinsics) for `__vmx_off` intrinsic repeats exactly for `__vmx_vmwrite` - that was the next problematic intrinsic I found.

More thorough look at optimization report for complete Windows port of vmlatency showed that few more intrinsics wrapped in an inline function are getting removed by interprocedural optimizations as well: `__sidt`, `__lidt` and `__writecr4`. There is a common property for all the five problematic intrinsics - they all access system state and do not modify general purpose registers. I haven't checked other similar intrinsics but all such intrinsics used in vmlatency are getting removed by the interprocedural optimizations.

It looks like the important intrinsic property - being something with side-effect not reflected in general-purpose registers - is not propagated to static inline wrapper functions and thus being removed by interprocedural optimizations as code with no state changes.

A simple memory barrier or any other way to disable compiler optimizations for such a function wrapper around an intrinsic will fix the problem:

```
#ifdef __INTEL_COMPILER
        /* XXX: Workaround for ICC bug. The memory barrier prevents ICC from
         * removing vmwrite instruction. */
        __asm__ __volatile__("": : :"memory");
#endif
```

I used Intel C++ Compiler Version 19.1.3.311 Build 20201010 for all the experiments.

# MASM oddity

While doing the port I found a minor oddity in MASM. I needed a function that simply calls `LGDT` instruction thus loading Global Descriptor Table register from a given memory location. This is done as a part of host state restoring routine performed by vmlatency.

The tool runs in 64-bit mode only at the moment therefore I only had to write x64 assembly wrappers. `LGDT` instruction has the following format in 64-bit mode: `LGDT m16&64` thus having a pointer to 10 byte (referred as [TBYTE](https://docs.microsoft.com/cpp/assembler/masm/tbyte) by MASM) memory location. Based on the information I expected this assembly code to encode `LGDT` instruction:

```
lgdt tbyte ptr [rcx]
```

But this code doesn't compile with MASM and produces this error:

```
error A2024:invalid operand size for instruction
```

With a bit of experimenting I found that MASM expects a 6 byte (referred as [FWORD](https://docs.microsoft.com/cpp/assembler/masm/fword)) memory location for `LGDT` instruction. This is valid for 32-bit mode where `LGDT` has the following format: `LGDT m16&32`.

This is just a minor oddity that is easy to find. In spite of this oddity the right binary sequence is generated as shown by manual inspect of the binary and error less execution.
