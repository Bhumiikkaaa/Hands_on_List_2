/*
 * Name     : Bhumika
 * Question : 63. Write a program to create an orphan process. Utilize the kill system call to send a
 *             SIGKILL signal from the child process to the parent process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    int pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // ---- child ----
        printf("Child : my pid = %d, parent pid = %d\n", getpid(), getppid());
        sleep(1);                    // let the parent print its pid first
        // child kills its own parent
        if (kill(getppid(), SIGKILL) == -1) {
            perror("kill");
            exit(1);
        }
        sleep(2);                    // give the kernel time to re-parent the child
        printf("Child : I am an orphan now, new parent pid = %d\n", getppid());
    } else {
        // ---- parent ----
        printf("Parent: my pid = %d\n", getpid());
        sleep(10);                   // will be killed before this ends
    }
    return 0;
}

/*
 * Sample output:
 *
 * Parent: my pid = 966
 * Child : my pid = 968, parent pid = 966
 * Child : I am an orphan now, new parent pid = 1
 */
