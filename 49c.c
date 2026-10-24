/*
 * Name     : Bhumika
 * Question : 49. Write a program to implement a semaphore to protect any critical section: c. Protect
 *             multiple pseudo resources (maybe two) using a counting semaphore
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
    key_t key = ftok(".", 'd');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    int semid;
    union semun arg;
    struct sembuf get = {0, -1, 0};      // take one resource
    struct sembuf release = {0, 1, 0};   // give one resource back

    // counting semaphore with value 2 = two resources available
    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid >= 0) {
        arg.val = 2;
        if (semctl(semid, 0, SETVAL, arg) == -1) {
            perror("semctl");
            exit(1);
        }
    } else {
        semid = semget(key, 1, 0);
    }

    printf("Waiting for a resource...\n");
    // third process will block here
    if (semop(semid, &get, 1) == -1) {
        perror("semop");
        exit(1);
    }
    printf("Got a resource (free resources left = %d)\n", semctl(semid, 0, GETVAL));

    printf("Press Enter to release the resource...\n");
    getchar();

    if (semop(semid, &release, 1) == -1) {
        perror("semop");
        exit(1);
    }
    printf("Resource released\n");
    return 0;
}

/*
 * Run three copies at the same time in three terminals.
 *
 * Sample output:
 *
 * Process 1: Got a resource (free resources left = 1)
 * Process 2: Got a resource (free resources left = 0)
 * Process 3: Waiting for a resource...      <- blocked until process 1 or 2 presses Enter
 */
