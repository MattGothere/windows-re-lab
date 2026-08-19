# Investigation 002 - Windows process

## Question

What exactly is a Windows process?

---

## My Current Understanding

At first, I thought process is like a running "application".

But after reading *Windows Internals* and Microsoft Learn documentation, I came to the realization that my understanding was incomplete.

A process is more like a container that holds the resources needed to run a program. One application can create one or more processes, and each process has its own PID and resources.

A process cannot execute code by itself. Instead, one or more threads execute the code using the resources owned by the process. Every process must have at least one thread.

---

## Evidence

* Microsoft Learn documentation
* *Windows Internals, Part 1*

---

## Open Questions

* Why does Windows separate a process from its threads?
* What resources are actually owned by a process?
* Why does every process need at least one thread?

---

## Experiment

I used `PROCESSENTRY32::cntThreads` to observe the number of threads owned by different processes.

The results showed that a process usually contains more than one thread, and the number of threads can vary significantly between processes.

This supports my current understanding that a process itself is not a single unit of execution. Instead, a process can contain multiple threads that execute within the environment and share the resources provided by the process.