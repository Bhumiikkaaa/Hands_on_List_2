/*
 * Name     : Bhumika
 * Question : 61. Write separate programs using the sigaction system call to catch the following signals:
 *             c. SIGFPE
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
    (void)sig;
    char msg[] = "Caught SIGFPE (divide by zero)\n";
    write(1, msg, sizeof(msg) - 1);
    _exit(1);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = handler;         // function to call
    sigemptyset(&sa.sa_mask);        // no extra signals blocked inside handler
    sa.sa_flags = 0;

    if (sigaction(SIGFPE, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    volatile int a = 10, b = 0, c;
    c = a / b;                       // division by zero -> SIGFPE
    printf("%d\n", c);
    return 0;
}

/*
 * Sample output:
 *
 * Caught SIGFPE (divide by zero)
 */
