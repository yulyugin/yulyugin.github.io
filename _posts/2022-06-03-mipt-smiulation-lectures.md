---
layout: post
title: "Simulation foundation lectures at MIPT"
date: 2022-06-03
---

In spring 2021, I received an offer to hold a course of lectures about simulation technologies for fourth year students at [Moscow Institute of Physics and Technology (MIPT)](https://mipt.ru/english/). The course was supposed to focus on fundamentals of computer system simulation and how different kinds of simulators are used in the industry. This was an interesting offer and I accepted it because I always liked talking to students about different research and engineering topics.

Luckily I had some experience in this field from the past. I also had materials that [Grigory Rechistov](https://github.com/grigory-rechistov) with a bit of my help used for a similar course several years ago. Grigory kindly shared all copies of the materials he had. All the old materials were in Russian thus it wasn't that simple to re-use them. Anyway, that was really helpful considering the short time window I had to prepare for the lectures.

# Course plan

After thorough review of all the existing materials and careful thinking I came out with a short plan for the course consisting of twelve lectures:

1. Simulation Role in Software and Hardware Development.
2. Terminology and General Requirements for Simulation.
3. Simulation Through Interpretation.
4. Simulation Through Just in Time Compilation.
5. Simulation Through Direct Execution.
6. Discrete Event Simulation.
7. Simulation of Architectural State.
8. Cycle Accurate Simulation.
9. Hardware Supported Virtualization.
10. Paravirtualization - Connecting Real Word With Simulation.
11. Programming Languages for Model and Hardware Development.
12. Parallel Discrete Event Simulation.

I wasn't sure about the last lecture - Parallel Discrete Event Simulation - as this topic is far beyond the fundamental simulation technologies. After some thinking and discussions with Grigory I decided to keep it because it's kind of hard to image the contemporary computing world without parallel execution.

To make the course more interactive I decided to start every new lecture with a few of questions about the previous one. Answers to the questions were used as one of criteria to build a student rating by the end of the course.

In order to make the course practical I added two tasks on top of the theoretical information:

1. Each student was supposed to choose one scientific article from a list I prepared, read the article, prepare a short talk about it and present summary of the article to all other attendees. That was a minimal requirement to get a credit for the course.
2. For those students who wanted to get a higher credit I prepared a set of practical projects to build. It was allowed to do the projects in small groups. Here are some ideas that were on my list:
    * Create a RISC-V processor model (possibly with some devices). Usage of publicly available simulation frameworks was allowed.
    * Create a model of a PCI device in Simics, implement a Linux driver to control the device. Example: 4x6 led matrix panel to print letters.
    * Implement several types of interpreters, do performance analysis and comparison. Architecture doesn't matter even [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) if fine.
    * Implement a simple template-based JIT for any architecture.
    * Create a simple hypervisor for 64-bit mode part of Intel 64 architecture using Intel VT-x.
    * Explore performance of ARM's, Intel's or AMD's virtualization support: how many cycles does it take to switch between hypervisor and virtual machine modes; how does additional state affect the switch time.

# Guest lectures

To add variability for the course I talked around our office and invited two guest lecturers:

1. [Jakob Engblom](http://jakob.engbloms.se/) held a "Using Virtual Platforms across the Product Life Cycle" lecture that mostly presented features and use cases of [Intel Simics](https://www.intel.com/content/www/us/en/developer/articles/tool/simics-simulator.html) simulator.
2. [Grigory Rechistov](https://github.com/grigory-rechistov) presented results of his PhD research in a "Simulation of Cluster Systems" lecture.

# Course materials

All the course materials are published on github: https://github.com/yulyugin/sim-lectures. Slides presented in the 2021 term can be downloaded from https://github.com/yulyugin/sim-lectures/releases/tag/slides-2021.

Still, there are a lot of possible improvements for the course. TeX source code of the slides is full with TODOs that needs to be addressed. Big thanks to Jakob who helped me with postmortem for the course and spent part of his Christmas holidays looking at the course materials in order to provide a lot of useful feedback.

# Results

Nine students in total attended the course. Big thanks to all of them for the time spent together! All of you showed amazing skills and I hope we will work together one day in the future.

Articles studied and presented by the students:

* *Keith Adams, Ole Agesen.*, "A Comparison of Software and Hardware Techniques for x86 Virtualization", 2006.
* *A. Sandberg, N. Nikoleris, T. E. Carlson, E. Hagersten, S. Kaxiras, D. Black-Schaffer*, "Full Speed Ahead: Detailed Architectural Simulation at Near-Native Speed," 2015.
* *Amanieu d’Antras, Cosmin Gorgovan, Jim Garside, Mikel Lujan*, "Optimizing Indirect Branches in Dinamyc Binary Translator", 2016.
* *Paul Barham , Boris Dragovic , Keir Fraser , Steven Hand , Tim Harris , Alex Ho , Rolf Neugebauer , Ian Pratt , Andrew Warﬁeld*, "Xen and the Art of Virtualization", 2003.
* *Ole Agesen, Jim Mattson, Radu Rugina, Jeffrey Sheldon*, "Software Techniques for Avoiding Hardware Virtualization Exits", 2011.
* *Edouard Bugnion, Scott Devine, Mendel Rosenblum, Jeremy Sugerman, Edward Wang*, "Bringing Virtualization to the x86 Architecture with the Original VMware Workstation", 2012.
* *Darek Mihocka, Stanislav Shwartsman*, "Virtualization Without Direct Execution or Jitting: Designing a Portable Virtual Machine Infrastructure", 2008.
* *Fredrik Larsson, Peter S. Magnusson, Bengt Werner*, "SimGen: Development of Efficient Instruction Set Simulators", 1997.
* *Yair Lifshitz, Omer Tabach, Robert Cohn, Mark Charney, Inbal Livni, Kim Hazelwood*, "Zsim: A Fast Architectural Simulator for ISA Design-Space Exploration", 2011.

Projects made by the students during the course:

* One student implemented an interpreter-based simulator of [К1986ВК025](https://ic.milandr.ru/products/mikrokontrollery_i_protsessory/32_razryadnye_mikrokontrollery/k1986vk025-okr-schetchik-m-/) 32-bit RISC-V microcontroller. Source code of the project: https://github.com/LotusBro98/MLDR187_simulator.
* A group of three students created this amazing setup: a Simics PCI device that implements wrapping accesses to an [STM32Discovery](https://www.st.com/en/evaluation-tools/stm32-discovery-kits.html#overview) board running simple firmware capable to take values from UART and show them on a seven-segment display. The device was connected to [Simics QSP](https://www.intel.com/content/www/us/en/developer/articles/guide/simics-simulator-get-started.html) virtual platform. Software running in the simulated system controlled the PCI device through a custom Linux kernel module loaded into the simulated OS. This setup allowed to show numbers on a physical STM32Discovery board from the simulated system. Source code of the project: https://github.com/leokondrashov/simics_device.
* A pair of students developed their own tiny architecture. One of the students built an assembler for the architecture. The other student implemented several different interpreters (switched, threaded, etc) for the architecture, compared and analyzed performance of the interpreters. Source code of the project: https://github.com/ShISA-VM/ShISA-VM.
