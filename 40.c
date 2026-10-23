/*
 * Name     : Bhumika
 * Question : 40. Write a program to print the maximum number of files that can be opened within a process
 *             and the size of a pipe (circular buffer).
 */

#define _GNU_SOURCE
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

    printf("Max open files per process : %ld\n", sysconf(_SC_OPEN_MAX));
    printf("PIPE_BUF (atomic write)    : %ld bytes\n", fpathconf(fd[0], _PC_PIPE_BUF));
    printf("Pipe buffer size (Linux)   : %d bytes\n", fcntl(fd[0], F_GETPIPE_SZ));
    return 0;
}

/*
 * Sample output:
 *
 * Max open files per process : 20000
 * PIPE_BUF (atomic write)    : 4096 bytes
 * Pipe buffer size (Linux)   : 65536 bytes
 */
