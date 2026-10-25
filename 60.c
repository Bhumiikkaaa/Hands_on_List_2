/*
 * Name     : Bhumika
 * Question : 60. Write a program to ignore a SIGINT signal and then reset it to the default action using
 *             the signal system call.
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    signal(SIGINT, SIG_IGN);         // ignore Ctrl+C
    printf("SIGINT ignored for 5 sec - try Ctrl+C, nothing happens\n");
    sleep(5);

    signal(SIGINT, SIG_DFL);         // restore default action (terminate)
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
