/*
 * Name     : Bhumika
 * Question : 59. Write separate programs using the signal system call to catch the following signals: b.
 *             SIGINT
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
    char msg[] = "Caught SIGINT (Ctrl+C)\n";
    write(1, msg, sizeof(msg) - 1);
    _exit(0);
}

int main()
{
    signal(SIGINT, handler);

    printf("Press Ctrl+C ...\n");
    while (1)
        pause();                     // wait for a signal
}

/*
 * Run it and press Ctrl+C.
 *
 * Sample output:
 *
 * Press Ctrl+C ...
 * ^C
 * Caught SIGINT (Ctrl+C)
 */
