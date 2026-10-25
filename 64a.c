/*
 * Name     : Bhumika
 * Question : 64. Create two programs: the first program awaits the SIGSTOP signal, while the second
 *             program sends the signal using the kill system call. Determine whether the
 *             first program successfully catches the signal or not. (Program 1 of 2:
 *             receiver. Program 2 is 64b.c)
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
    (void)sig;
    printf("Caught SIGSTOP\n");
}

int main()
{
    // try to catch SIGSTOP - this is expected to FAIL
    if (signal(SIGSTOP, handler) == SIG_ERR)
        perror("signal(SIGSTOP)");

    printf("My pid = %d. Waiting for SIGSTOP ...\n", getpid());
    while (1)
        pause();
}

/*
 * Run this first, then run 64b.c in a second terminal.
 *
 * Sample output:
 *
 * signal(SIGSTOP): Invalid argument
 * My pid = 499. Waiting for SIGSTOP ...
 * 
 * (in another terminal: ./64b.out 499 )
 * $ grep State /proc/499/status
 * State:  T (stopped)
 * 
 * Result: SIGSTOP cannot be caught (signal() fails with EINVAL); the process is
 * simply stopped. Resume it with:  kill -CONT 499
 */
