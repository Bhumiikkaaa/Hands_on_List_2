/*
 * Name     : Bhumika
 * Question : 53. Write separate programs for each time domain to set an interval timer for 10 seconds and
 *             10 microseconds. c. Use ITIMER_PROF
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

int count = 0;

void handler(int sig)
{
    char msg[] = "ITIMER_PROF expired (SIGPROF)\n";
    write(1, msg, sizeof(msg) - 1);
    count++;
    if (count == 5)
        _exit(0);
}

int main()
{
    struct itimerval t;

    signal(SIGPROF, handler);        // ITIMER_PROF sends SIGPROF

    t.it_value.tv_sec = 10;
    t.it_value.tv_usec = 0;
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_PROF, &t, NULL) == -1) {
        perror("setitimer");
        exit(1);
    }

    while (1)
        ;                            // busy loop: counts user + system CPU time
}

/*
 * Sample output:
 *
 * ITIMER_PROF expired (SIGPROF)
 * ITIMER_PROF expired (SIGPROF)
 * ITIMER_PROF expired (SIGPROF)
 * ITIMER_PROF expired (SIGPROF)
 * ITIMER_PROF expired (SIGPROF)
 */
