/*
 * Name     : Bhumika
 * Question : 32. Develop a simple program to send data from the parent process to the child process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int fd[2];
    char buf[100];
    int n;

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
        // ---- child: reads ----
        close(fd[1]);                // child does not write, so close write end
        n = read(fd[0], buf, sizeof(buf));
        buf[n] = '\0';
        printf("Child received: %s\n", buf);
    } else {
        // ---- parent: writes ----
        close(fd[0]);                // parent does not read, so close read end
        write(fd[1], "Hello from parent", 17);
    }
    return 0;
}

/*
 * Sample output:
 *
 * Child received: Hello from parent
 */
