/*
 * Name     : Bhumika
 * Question : 59. Write separate programs using the signal system call to catch the following signals: f.
 *             SIGVTALRM (using the setitimer system call)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handler(int sig)
{
    (void)sig;
    char msg[] = "Caught SIGVTALRM (ITIMER_VIRTUAL)\n";
    write(1, msg, sizeof(msg) - 1);
    _exit(0);
}

int main()
{
    struct itimerval t;

    signal(SIGVTALRM, handler);

    t.it_value.tv_sec = 2;           // expire after 2 sec of USER CPU time
    t.it_value.tv_usec = 0;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_VIRTUAL, &t, NULL) == -1) {
        perror("setitimer");
        exit(1);
    }

    while (1)
        ;                            // keep the CPU busy so the timer runs
}

/*
 * Sample output:
 *
 * Caught SIGVTALRM (ITIMER_VIRTUAL)
 */
