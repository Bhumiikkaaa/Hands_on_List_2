/*
 * Name     : Bhumika
 * Question : 54. Write a program to print system resource limits using the getrlimit system call.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void show(char *name, int resource)
{
    struct rlimit r;

    // fills soft (cur) and hard (max) limit
    if (getrlimit(resource, &r) == -1) {
        perror("getrlimit");
        exit(1);
    }

    printf("%-22s soft = ", name);
    if (r.rlim_cur == RLIM_INFINITY)
        printf("unlimited");
    else
        printf("%lu", (unsigned long)r.rlim_cur);

    printf("   hard = ");
    if (r.rlim_max == RLIM_INFINITY)
        printf("unlimited\n");
    else
        printf("%lu\n", (unsigned long)r.rlim_max);
}

int main()
{
    show("CPU time (sec)", RLIMIT_CPU);
    show("File size (bytes)", RLIMIT_FSIZE);
    show("Data segment", RLIMIT_DATA);
    show("Stack size", RLIMIT_STACK);
    show("Core file size", RLIMIT_CORE);
    show("Max processes", RLIMIT_NPROC);
    show("Max open files", RLIMIT_NOFILE);
    show("Locked memory", RLIMIT_MEMLOCK);
    show("Address space", RLIMIT_AS);
    return 0;
}

/*
 * Sample output:
 *
 * CPU time (sec)         soft = unlimited   hard = unlimited
 * File size (bytes)      soft = unlimited   hard = unlimited
 * Data segment           soft = unlimited   hard = unlimited
 * Stack size             soft = 8388608   hard = unlimited
 * Core file size         soft = 0   hard = unlimited
 * Max processes          soft = 15899   hard = 15899
 * Max open files         soft = 20000   hard = 20000
 * Locked memory          soft = 8388608   hard = 8388608
 * Address space          soft = unlimited   hard = unlimited
 */
