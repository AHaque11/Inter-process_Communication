# Inter-process_Communication

This is a C program that communicates the value of an integer x between processes. x begins with the hard-coded value of 19530, which is printed. A shared memory segment is created using System V IPC mechanisms. The initial value is stored in shared memory.

The program enters a loop of 5 iterations, where each iteration involves forking a new process. In the child process, the value in shared memory is decremented by 5. In the parent process, the value is divided by 5 after waiting for the child process to finish. The updated values of x are printed for each iteration for both child and parent processes.


 
