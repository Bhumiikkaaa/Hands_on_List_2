/*
 * Name     : Bhumika
 * Question : 34. Write a program to execute ls -l | wc using: c. fcntl
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
        close(1);
        fcntl(fd[1], F_DUPFD, 1);    // duplicate fd[1] to the lowest free fd >= 1  (= 1)
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    } else {
        // ---- parent runs "wc" ----
        close(fd[1]);
        close(0);
        fcntl(fd[0], F_DUPFD, 0);    // duplicate fd[0] to the lowest free fd >= 0  (= 0)
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
