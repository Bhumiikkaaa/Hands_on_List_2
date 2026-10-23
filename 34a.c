/*
 * Name     : Bhumika
 * Question : 34. Write a program to execute ls -l | wc using: a. dup
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
        // ---- child runs "ls -l" : its output must go INTO the pipe ----
        close(fd[0]);
        close(1);                    // free file descriptor 1 (stdout)
        dup(fd[1]);                  // dup uses lowest free fd = 1, so stdout -> pipe
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    } else {
        // ---- parent runs "wc" : its input must come FROM the pipe ----
        close(fd[1]);
        close(0);                    // free file descriptor 0 (stdin)
        dup(fd[0]);                  // dup uses lowest free fd = 0, so stdin <- pipe
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
