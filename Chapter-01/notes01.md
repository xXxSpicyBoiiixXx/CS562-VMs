# Introduction to Virtual Machines 

As the World Wide Web grew, so did the use of many different types of computers. In the exciting new world where many different computers were being implemetned from their operating systems, programming languages, compilers, etc. There was one restricitve issue here, that the diversity that was in networked computers becomes very restricitive as we can only operate in certain parameters. In today's world, we want to move data pretty freely between on computer to another that may have different underlining systems. 

The underlying assumption is taht the hardware resources of a system are managed by a single operating system. But this isn't always the case.. So we can see the restrictive nature here.. one operating system for one set of hardware resources. Which can be kinda problematic in today's world of networked computers? 

This is where virtualization comes in play. Virtualizing probides a way of relaxing the such restrictions and increase flexibility. Which is everything we exactly want in today's world of computing. When a system is virtualized, its interface and all resources visible through the interface are mapped on the the interface and resources of a real systems actually implementing it.

So let's talk about virtual machines, which this course is about. A virtual machine adds a layer of software to a real machine to support some type other or the same architecture. 

The benefits of having operating systems running is that it can provide isolation and enhanced security wiht multiple layers of OSs on top of one another. This also add isolation from one another so to the user it can look like completely different systems. 

Despite there being differences in this or that operating system, there are some common underlying technoliogies that support them. So we'll see here in a minute. 

### Computer Architecutre 

Revisting computer architectural design, since virtual machines quite often bridge architecture boundaries, and one thing that is useful for VMs to consider is the implemetned architected infterfaces. 

### Virtual Machine Basics 

In general a VM either executes software either individual process or a full system as the same manner as the machine for which the software was developed. Virtual machines often have less performance than the real machine. 

So there is process persepective and systems perspective, so essentially there is also a process-level and system-level virtual machines. So you might have guess there is some virtualization that go here too lol.

There are process-level and system-level virtual machines. So a process virtual machien is capable of supporting an individual process. In process VMs virtualized software is referred to as the runtime, aka runtime software. From there a system virtual machine provides a complete system environment. 
