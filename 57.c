/*
 * Name     : Bhumika
 * Question : 57. Write a program to print system limitations for: a. Maximum length of arguments in the
 *             exec family of functions. b. Maximum number of simultaneous processes per user
 *             ID. c. Number of clock ticks (jiffies) per second. d. Maximum number of open
 *             files. e. Size of a page. f. Total number of pages in physical memory. g.
 *             Number of currently available pages in physical memory.
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("a. Max length of exec arguments   : %ld\n", sysconf(_SC_ARG_MAX));
    printf("b. Max processes per user         : %ld\n", sysconf(_SC_CHILD_MAX));
    printf("c. Clock ticks (jiffies) per sec  : %ld\n", sysconf(_SC_CLK_TCK));
    printf("d. Max open files                 : %ld\n", sysconf(_SC_OPEN_MAX));
    printf("e. Page size (bytes)              : %ld\n", sysconf(_SC_PAGESIZE));
    printf("f. Total pages in physical memory : %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("g. Available pages in memory      : %ld\n", sysconf(_SC_AVPHYS_PAGES));
    return 0;
}

/*
 * Sample output:
 *
 * a. Max length of exec arguments   : 2097152
 * b. Max processes per user         : 15899
 * c. Clock ticks (jiffies) per sec  : 100
 * d. Max open files                 : 20000
 * e. Page size (bytes)              : 4096
 * f. Total pages in physical memory : 1022924
 * g. Available pages in memory      : 989348
 */
