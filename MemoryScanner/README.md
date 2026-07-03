\# Windows Internals \& Reverse Engineering Journey



This repository documents my journey toward learning reverse engineering by building small tools from scratch.


My goal is to understand the operating system concepts that make these tools possible.



Instead of only reading books or watching tutorials, I explore Windows by asking questions, writing code, and verifying how things actually work.



\---



\## Why this project?



I became interested in reverse engineering after wondering how tools like Cheat Engine, debuggers, malware, and anti-cheat systems actually work.



Very quickly I realized that understanding reverse engineering requires understanding Windows itself.





\---



\## Current Question



> \*\*How does Windows enumerate running processes?\*\*



Current implementation:



\- \[x] Enumerate running processes using the Tool Help API



Current Windows APIs:



\- CreateToolhelp32Snapshot()

\- Process32First()

\- Process32Next()



\---



\## Learning Philosophy



Every milestone in this repository starts with a question.



For each question I try to:



1\. Understand the problem.

2\. Read the official documentation.

3\. Build a small experiment.

4\. Verify my understanding.

5\. Record what I learned.



The objective is not simply to finish a project, but to build a deeper understanding of how Windows works internally.



\---



\## Future Questions



Some questions I hope to answer in the future include:



\- How can one process open another process?

\- How does ReadProcessMemory work?

\- How is virtual memory organized?

\- Why do memory addresses change?

\- How are executable files loaded?

\- How do debuggers inspect running programs?

\- How do reverse engineers locate data without source code?

\- How do anti-cheat systems detect memory manipulation?



I don't expect to know the answers yet.



This repository exists to find them.



\---



\## Long-term Goal



Build a solid foundation in:



\- Windows Internals

\- Systems Programming

\- Reverse Engineering

\- Software Security



while documenting the entire learning journey.

