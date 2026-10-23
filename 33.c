/*
 * Name     : Bhumika
 * Question : 33. Write a program to send and receive data between the parent and child processes using
 *             two-way communication.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int p2c[2];                      // pipe 1: parent -> child
    int c2p[2];                      // pipe 2: child -> parent
    char buf[100];
    int n;

    if (pipe(p2c) == -1) {
        perror("pipe");
        exit(1);
    }
    if (pipe(c2p) == -1) {
        perror("pipe");
        exit(1);
    }

    int pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        // ---- child ----
        close(p2c[1]);               // child only reads from p2c
        close(c2p[0]);               // child only writes to c2p

        n = read(p2c[0], buf, sizeof(buf));
        buf[n] = '\0';
        printf("Child received : %s\n", buf);

        write(c2p[1], "Hello parent", 12);
    } else {
        // ---- parent ----
        close(p2c[0]);               // parent only writes to p2c
        close(c2p[1]);               // parent only reads from c2p

        write(p2c[1], "Hello child", 11);

        n = read(c2p[0], buf, sizeof(buf));
        buf[n] = '\0';
        printf("Parent received: %s\n", buf);
        wait(NULL);
    }
    return 0;
}

/*
 * Sample output:
 *
 * Child received : Hello child
 * Parent received: Hello parent
 */
