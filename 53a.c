/*
 * Name     : Bhumika
 * Question : 53. Write separate programs for each time domain to set an interval timer for 10 seconds and
 *             10 microseconds. a. Use ITIMER_REAL
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

int count = 0;

void handler(int sig)
{
    (void)sig;
    char msg[] = "ITIMER_REAL expired (SIGALRM)\n";
    write(1, msg, sizeof(msg) - 1);
    count++;
    if (count == 5)          // stop after 5 expiries
        _exit(0);
}

int main()
{
    struct itimerval t;

    signal(SIGALRM, handler);        // ITIMER_REAL sends SIGALRM

    t.it_value.tv_sec = 10;          // first expiry after 10 sec
    t.it_value.tv_usec = 0;
    t.it_interval.tv_sec = 0;        // then repeat every 10 microsec
    t.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_REAL, &t, NULL) == -1) {
        perror("setitimer");
        exit(1);
    }

    while (1)
        pause();                     // wait for signals
}

/*
 * Sample output:
 *
 * ITIMER_REAL expired (SIGALRM)
 * ITIMER_REAL expired (SIGALRM)
 * ITIMER_REAL expired (SIGALRM)
 * ITIMER_REAL expired (SIGALRM)
 * ITIMER_REAL expired (SIGALRM)
 */
