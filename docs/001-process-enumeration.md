# Investigation 001 - How does Windows know what processes are running?

## Question

How does Windows know what processes are currently running?

---

## My Understanding

Windows doesn't appear to search for processes one by one.

Instead, it creates a snapshot of the current system state and then iterates through the processes stored in that snapshot.

Each process is represented by a "PROCESSENTRY32" structure while iterating.

---

## Evidence

- Enumerated processes using the Tool Help API.
- Observed that the snapshot contains information about running processes.
- Learned that the snapshot represents a single moment in time.

---

## New Questions

* What exactly is a Windows process?
* Where does the process snapshot come from?
* Why does Windows use a snapshot instead of accessing the process list directly?
