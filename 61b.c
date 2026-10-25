/*
 * Name     : Bhumika
 * Question : 61. Write separate programs using the sigaction system call to catch the following signals:
 *             b. SIGINT
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
    (void)sig;
    char msg[] = "Caught SIGINT (Ctrl+C)\n";
    write(1, msg, sizeof(msg) - 1);
    _exit(1);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = handler;         // function to call
    sigemptyset(&sa.sa_mask);        // no extra signals blocked inside handler
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("Press Ctrl+C ...\n");
    while (1)
        pause();
    return 0;
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
