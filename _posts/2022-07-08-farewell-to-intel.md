---
layout: post
title: "Farewell to Intel"
date: 2022-07-08
---

![Intel logo]{: style="float: left; width: 15%; padding: 1%"} I've spent the last ten year working at Intel. For the first four and a half years, I was working at Krylatsky Hills office in Moscow, Russia. The rest of the time at Intel I spent at Drottningholms office in Stockholm, Sweden. It was a long and interesting journey from intern to senior software engineer, from bachelor student at [MIPT](https://mipt.ru/english/) to PhD.

I started at Intel in June 2012 as an intern working on a research project focused on [supercomputer technologies](https://rscgroup.ru/en/project/mipt-iscalare-rsc-tornado/) for biomedicine and pharmacology. My main task at that moment was to analyze how different network topologies influence the overall performance of experiments running in the cluster. [Intel Simics](https://www.intel.com/content/www/us/en/developer/articles/tool/simics-simulator.html) simulator was used to model different configurations of a (usually bigger) cluster while running on a smaller real cluster.

After that, I worked on different processor models in Simics. I was mostly focused on x86 architecture during all the years at Intel, but Itanium was actually the first processor model I worked on. It happened couple of months before Itanium project was officially discontinued by Intel.

Back to x86, a lot of exciting things happened during all these years. Starting with model development for x86 instructions set extensions, like [CET](../papers/2017-ieee-ucode-assist.pdf); continuing to [long and challenging debugs]({{ site.baseurl }}/blog/2022/vmp-debug), cross-platform development (including macOS port of Simics VT-x based kernel-mode accelerator) and ending up with lots of performance optimization activities. Many of the performance activities (like [page scanning](../papers/2018-dvcon-page-scanning.pdf) to get around incompatibilities between different generations) became part of my PhD. I want to say additional thank you to all my Intel colleagues who helped me with my PhD journey. The PhD defense was celebrated by a great mountain trip leading to [Simics flag delivered to the top](https://www.intel.com/content/www/us/en/developer/articles/technical/simics-6-at-the-mountain-top.html) of Europe's highest mountain Elbrus:

![]({{ site.baseurl }}/images/simics-elbrus.jpg ){: style="float: center; width: 95%; padding: 1%"}

I worked with great people and learned a lot of new things over the ten years at Intel, but I've decided that it is time to move on. So, today I farewell with my colleagues and leave Intel.

[Intel logo]: {{ site.baseurl }}/images/intel.svg
