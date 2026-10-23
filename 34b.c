/*
 * Name     : Bhumika
 * Question : 34. Write a program to execute ls -l | wc using: b. dup2
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    int pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        // ---- child runs "ls -l" ----
        close(fd[0]);
        dup2(fd[1], 1);              // make fd 1 (stdout) a copy of the pipe write end
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    } else {
        // ---- parent runs "wc" ----
        close(fd[1]);
        dup2(fd[0], 0);              // make fd 0 (stdin) a copy of the pipe read end
        close(fd[0]);
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(1);
    }
    return 0;
}

/*
 * Sample output:
 *
 *     141    1262    6861
 */
