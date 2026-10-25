/*
 * Name     : Bhumika
 * Question : 59. Write separate programs using the signal system call to catch the following signals: a.
 *             SIGSEGV
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
    char msg[] = "Caught SIGSEGV (segmentation fault)\n";
    write(1, msg, sizeof(msg) - 1);
    _exit(1);                        // must exit, else the faulty instruction repeats forever
}

int main()
{
    int *p = NULL;

    signal(SIGSEGV, handler);

    *p = 10;                         // invalid memory access -> SIGSEGV
    return 0;
}

/*
 * Sample output:
 *
 * Caught SIGSEGV (segmentation fault)
 */
