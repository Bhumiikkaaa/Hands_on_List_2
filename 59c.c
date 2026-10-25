/*
 * Name     : Bhumika
 * Question : 59. Write separate programs using the signal system call to catch the following signals: c.
 *             SIGFPE
 */

#include <stdio.h>
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
    volatile int a = 10, b = 0, c;   // volatile: stops compiler from optimising the division away

    signal(SIGFPE, handler);

    c = a / b;                       // division by zero -> SIGFPE
    printf("%d\n", c);
    return 0;
}

/*
 * Sample output:
 *
 * Caught SIGFPE (divide by zero)
 */
