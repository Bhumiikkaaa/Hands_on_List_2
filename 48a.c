/*
 * Name     : Bhumika
 * Question : 48. Write a program to create a semaphore and initialize its value: a. Create a binary
 *             semaphore
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {                        // Linux requires us to define this ourselves
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main()
{
    key_t key = ftok(".", 'b');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    int semid = semget(key, 1, IPC_CREAT | 0666);   // 1 = a set with one semaphore
    if (semid == -1) {
        perror("semget");
        exit(1);
    }
    union semun arg;

    arg.val = 1;                                    // binary semaphore: value 0 or 1
    // initialise semaphore number 0
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }

    printf("Binary semaphore created, id = %d, value = %d\n",
           semid, semctl(semid, 0, GETVAL));
    return 0;
}

/*
 * Sample output:
 *
 * Binary semaphore created, id = 3, value = 1
 */
