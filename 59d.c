/*
 * Name     : Bhumika
 * Question : 59. Write separate programs using the signal system call to catch the following signals: d.
 *             SIGALRM (using the alarm system call)
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
    (void)sig;
    char msg[] = "Caught SIGALRM (alarm)\n";
    write(1, msg, sizeof(msg) - 1);
    _exit(0);
}

int main()
{
    signal(SIGALRM, handler);

    printf("alarm set for 3 seconds\n");
    alarm(3);                        // kernel sends SIGALRM after 3 sec

    while (1)
        pause();
}

/*
 * Sample output:
 *
 * Caught SIGALRM (alarm)
 */
