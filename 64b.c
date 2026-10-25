/*
 * Name     : Bhumika
 * Question : 64. Create two programs: the first program awaits the SIGSTOP signal, while the second
 *             program sends the signal using the kill system call. (Program 2 of 2: sender.
 *             Program 1 is 64a.c)
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    // send SIGSTOP to the given pid
    if (kill(atoi(argv[1]), SIGSTOP) == -1) {
        perror("kill");
        exit(1);
    }
    printf("SIGSTOP sent to %s\n", argv[1]);
    return 0;
}

/*
 * Usage: ./64b.out <pid of 64a.out>
 *
 * Sample output:
 *
 * SIGSTOP sent to 499
 */
