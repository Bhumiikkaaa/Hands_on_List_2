/*
 * Name     : Bhumika
 * Question : 48. Write a program to create a semaphore and initialize its value: b. Create a counting
 *             semaphore
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main()
{
    key_t key = ftok(".", 'c');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }
    union semun arg;

    arg.val = 5;                                    // counting semaphore: any value >= 0
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }

    printf("Counting semaphore created, id = %d, value = %d\n",
           semid, semctl(semid, 0, GETVAL));
    return 0;
}

/*
 * Sample output:
 *
 * Counting semaphore created, id = 4, value = 5
 */
