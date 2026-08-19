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

### Experiment 1 - Executable Path

**Question:** Can one process obtain the executable path of another process?

**Method:** TODO

**Result:** TODO

**Observation:** TODO

---

## Open Questions

- Can one process read the memory of another process?
- Can one process modify the memory of another process?
- How do process access rights affect these operations?
- Does running with elevated privileges change the results?