# Investigation 003 - Windows Process Isolation

## Question

How isolated is one Windows process from another process?

What information can one process obtain about another process, and what prevents it from accessing everything?

---

## Hypothesis

Based on my current understanding, I think one process can obtain some basic information about another process, such as its name, number of threads, and possibly the path to its executable.

I also think it may be possible for one process to read the memory of another process.

However, modifying another process's memory probably requires additional permissions or privileges.

At this point, I do not know exactly where Windows draws the boundary between information that is accessible and information that is protected.

---

## Experiments

### Experiment 1 - Thread Enumeration

**Question:** Can I identify the threads owned by a specific process?

**Method:**

First, I enumerated the running processes and searched for a process by its executable name.

After finding the target process, I recorded its PID.

I then created a thread snapshot and enumerated the thread entries in the system. Since each `THREADENTRY32` contains both a thread ID (`th32ThreadID`) and the PID of its owner process (`th32OwnerProcessID`), I compared each owner PID with the PID of my target process.

If they matched, I recorded the thread ID.

**Result:**

I was able to enumerate all threads belonging to the target process.

For example, in one test with `Notepad.exe`:

    PID: 71256
    thread #1: 71260
    thread #2: 71272
    thread #3: 71288
    ...
    thread #64: 45376

I also compared the number of threads I found manually with `PROCESSENTRY32::cntThreads`. In this test, both reported 64 threads.

**Observation:**

A thread snapshot contains threads belonging to different processes. To determine which threads belong to a target process, I have to reconstruct the relationship by comparing `THREADENTRY32::th32OwnerProcessID` with the target PID.

This experiment also made the process-thread relationship more concrete to me. A process has its own PID, while each thread inside it has a separate TID.

The thread count from `PROCESSENTRY32::cntThreads` matched my enumeration result in this test. However, the process snapshot and thread snapshot are created separately, so I do not expect the two values to always match if threads are created or terminated between the snapshots.

---

### Experiment 2 - Executable Path

**Question:** Can one process obtain the executable path of another process?

**Method:** 
I reuse the process lookup to find the target's PID for me to get the module snapshot of it. Then, by using first module information, we can then bring out the `MODULEENTRY32::szExePath` to get the executable path of a process. 

**Result:** 
I successfully find and print the executable path of another process on screen.

**Observation:** 
In my experiment, the first module returned by `Module32First` provided the path to the target process's executable through `MODULEENTRY32::szExePath`. I still need to understand why the first module corresponds to the main executable.

---

## Open Questions

- Can one process read the memory of another process?
- Can one process modify the memory of another process?
- How do process access rights affect these operations?
- Does running with elevated privileges change the results?