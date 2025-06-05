#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/mman.h>
#include <assert.h>

// Catch page-fault exceptions
void pf_handler(int i) {
    exit(1);
}

void main() {
    // Initialize the state:
    // -registers
    asm volatile("mov $0x1, %eax");
    asm volatile("mov $0x08090004, %ebx");
    // - memory
    size_t page_size = 4096;
    void *page = mmap((void*)0x08090000, page_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    assert(page);
    memcpy((void*)0x08090008, "\x11\x22", 2);
    // - setup handlers to catch exceptions
    signal(SIGSEGV, pf_handler);
    //Execute the code: or %bh, 0x4(%ebx)
    asm volatile(".byte 0x08,0x7c,0xe3,0x04");
    // Compare the state (only the potentially
    // differing bytes) and exit accordingly
    if (memcmp((void*)0x08090008,"\x11\x26", 2) == 0) {
        munmap(page, page_size);
        exit(0);
    }
    munmap(page, page_size);
    exit(1);
}
