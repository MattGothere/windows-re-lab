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

## Process vs Thread

Windows 將 process 和 thread 分成兩個不同的概念。

Process 主要提供程式執行所需要的環境與資源，例如虛擬位址空間、handle 和安全性資訊；thread 則負責實際執行程式碼。

CPU 並不是直接執行一個 process，而是執行 process 中的 thread。一個 process 可以包含多個 thread，這些 thread 共享 process 所提供的部分資源，但各自具有自己的執行狀態。

因此目前我可以先把兩者理解成：

- Process：資源與執行環境的容器
- Thread：實際執行程式碼的單位

這也產生了一個新的問題：如果多個 thread 屬於同一個 process，它們究竟共享哪些資源，又有哪些資源是各自獨立的？
