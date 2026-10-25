/*
 * Name     : Bhumika
 * Question : 55. Write a program to set a system resource limit using the setrlimit system call.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main()
{
    struct rlimit r;

    // read the current limit first
    if (getrlimit(RLIMIT_NOFILE, &r) == -1) {
        perror("getrlimit");
        exit(1);
    }
    printf("Before: soft = %lu, hard = %lu\n",
           (unsigned long)r.rlim_cur, (unsigned long)r.rlim_max);

    r.rlim_cur = 512;                // change only the soft limit (must be <= hard)

    if (setrlimit(RLIMIT_NOFILE, &r) == -1) {
        perror("setrlimit");
        return 1;
    }

    // read again to confirm
    if (getrlimit(RLIMIT_NOFILE, &r) == -1) {
        perror("getrlimit");
        exit(1);
    }
    printf("After : soft = %lu, hard = %lu\n",
           (unsigned long)r.rlim_cur, (unsigned long)r.rlim_max);
    return 0;
}

/*
 * Sample output:
 *
 * Before: soft = 20000, hard = 20000
 * After : soft = 512, hard = 20000
 */
