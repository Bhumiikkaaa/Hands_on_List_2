/*
 * Name     : Bhumika
 * Question : 61. Write separate programs using the sigaction system call to catch the following signals:
 *             a. SIGSEGV
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
    (void)sig;
    char msg[] = "Caught SIGSEGV (segmentation fault)\n";
    write(1, msg, sizeof(msg) - 1);
    _exit(1);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = handler;         // function to call
    sigemptyset(&sa.sa_mask);        // no extra signals blocked inside handler
    sa.sa_flags = 0;

    if (sigaction(SIGSEGV, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    int *p = NULL;
    *p = 10;                         // invalid memory access -> SIGSEGV
    return 0;
}

/*
 * Sample output:
 *
 * Caught SIGSEGV (segmentation fault)
 */
