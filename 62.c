/*
 * Name     : Bhumika
 * Question : 62. Write a program to ignore a SIGINT signal and then reset it to the default action using
 *             the sigaction system call.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sa.sa_handler = SIG_IGN;         // ignore
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    printf("SIGINT ignored for 5 sec - try Ctrl+C, nothing happens\n");
    sleep(5);

    sa.sa_handler = SIG_DFL;         // default action
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    printf("Default action restored - press Ctrl+C now to kill me\n");
    sleep(5);

    printf("Finished normally\n");
    return 0;
}

/*
 * Press Ctrl+C during the first 5 sec (ignored), then again after (kills).
 *
 * Sample output:
 *
 * SIGINT ignored for 5 sec - try Ctrl+C, nothing happens
 * ^C^C   (nothing happens)
 * Default action restored - press Ctrl+C now to kill me
 * ^C   (process is killed)
 */
