/*
 * Name     : Bhumika
 * Question : 56. Write a program to measure the time taken to execute 100 getppid() system calls using a
 *             time stamp counter.
 */

#include <stdio.h>
#include <unistd.h>

// rdtsc reads the CPU's Time Stamp Counter (number of clock cycles). x86 only.
unsigned long long rdtsc()
{
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long)hi << 32) | lo;
}

int main()
{
    unsigned long long start, end;
    int i;

    start = rdtsc();
    for (i = 0; i < 100; i++)
        getppid();
    end = rdtsc();

    printf("Cycles for 100 getppid() calls : %llu\n", end - start);
    printf("Cycles per call (average)      : %llu\n", (end - start) / 100);
    return 0;
}

/*
 * Sample output:
 *
 * Cycles for 100 getppid() calls : 26338
 * Cycles per call (average)      : 263
 */
