/*
 * Name     : Bhumika
 * Question : 35. Write a program to find the total number of directories in the present working directory
 *             using ls -l | grep ^d | wc. Implement the solution using only dup2.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int p1[2];                       // pipe between ls and grep
    int p2[2];                       // pipe between grep and wc

    if (pipe(p1) == -1) {
        perror("pipe");
        exit(1);
    }
    if (pipe(p2) == -1) {
        perror("pipe");
        exit(1);
    }

    int pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        // ---- process 1 : ls -l  (stdout -> p1) ----
        dup2(p1[1], 1);
        close(p1[0]); close(p1[1]);
        close(p2[0]); close(p2[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        // ---- process 2 : grep ^d  (stdin <- p1, stdout -> p2) ----
        dup2(p1[0], 0);
        dup2(p2[1], 1);
        close(p1[0]); close(p1[1]);
        close(p2[0]); close(p2[1]);
        execlp("grep", "grep", "^d", NULL);
        perror("execlp");
        exit(1);
    }

    // ---- process 3 (parent) : wc  (stdin <- p2) ----
    dup2(p2[0], 0);
    close(p1[0]); close(p1[1]);      // close unused ends, else wc never sees end-of-file
    close(p2[0]); close(p2[1]);
    execlp("wc", "wc", NULL);
    perror("execlp");
    exit(1);

    return 0;
}

/*
 * Sample output:
 *
 * (run inside a folder that has 2 sub-directories)
 *       2      18     130
 * --- check with the shell command ---
 *       2      18     130
 */
