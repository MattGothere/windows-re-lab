# Investigation 004 - Process Handles and Access Rights

## Question

Can I access the prcess with its PID

How do the requested access rights affect whether Windows allows me to obtain a handle to that process?

---

## Current Understanding

A PID identifies a process, but knowing the PID does not necessarily mean that I can operate on the process.

`OpenProcess` can be used to get a handle to a process. The `dwDesiredAccess` parameter specifies the access rights being requested.

My current understanding is that the returned handle can later be used by other Windows APIs, but what I can do through that handle depends on the access rights that were granted.

---

## Hypothesis

For this experiment, `SeDebugPrivilege` will not be enabled.

I expect processes owned by the current user to be easier to access than Windows services or system processes.

### Predictions

| Target | PROCESS_VM_READ | PROCESS_SUSPEND_RESUME | PROCESS_DUP_HANDLE |
|---|---|---|---|
| Notepad | Success | Success | Unsure |
| My test process | Success | Success | Success |
| Windows service/process | Unsure | Fail | Fail |

---

## Experiment 1 - Requesting Process Access

### Question

Does changing `dwDesiredAccess` change whether `OpenProcess` succeeds for the same target process?

### Method

TODO

### Result

TODO

### Observation

TODO

---