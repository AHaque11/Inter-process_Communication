#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    
    int num = 19530; // Initial value to be shared between parent and child processes
    int iteration;

    // Create a shared memory segment
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    
    
    int *shm = shmat(shmid, NULL, 0);  // Attach the shared memory segment to the process
    *shm = num;  // Set the value in the shared memory to the initial value

    // Print the initial value
    printf("\n");
    printf("Initial value: x = %d\n", num);
    printf("\n");
    

    // Perform a loop with 5 iterations
    for (iteration = 0; iteration < 5; iteration++) {
        
        fflush(stdout); // Flush the output buffer

        
        int pid = fork(); // Fork a new process

        if (pid == 0) {
            
            // Child process: decrement the value in shared memory by 5
            *shm -= 5;
            printf("Child: x = %d\n", *shm);
            
            // Exit the child process
            exit(0);
            
        } else if (pid > 0) {
            
            // Parent process: wait for the child process to finish
            wait(NULL);
            
            // Divide the value in shared memory by 5
            *shm /= 5;
            printf("Parent: x = %d\n", *shm);
            
        }

        // Print the current iteration
        printf("ITERATION %d\n", iteration + 1);
        printf("\n");
    }

    // Detach the shared memory segment from the process
    shmdt(shm);
    
    // Remove the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);


    return 0;
}

