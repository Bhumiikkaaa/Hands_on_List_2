/*
 * Name     : Bhumika
 * Question : 59. Write separate programs using the signal system call to catch the following signals: e.
 *             SIGALRM (using the setitimer system call)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handler(int sig)
{
    (void)sig;
    char msg[] = "Caught SIGALRM (ITIMER_REAL)\n";
    write(1, msg, sizeof(msg) - 1);
    _exit(0);
}

int main()
{
    struct itimerval t;

    signal(SIGALRM, handler);

    t.it_value.tv_sec = 3;           // expire after 3 sec of real time
    t.it_value.tv_usec = 0;
    t.it_interval.tv_sec = 0;        // 0 = do not repeat
    t.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &t, NULL) == -1) {
        perror("setitimer");
        exit(1);
    }

    while (1)
        pause();
}

/*
 * Sample output:
 *
 * Caught SIGALRM (ITIMER_REAL)
 */
