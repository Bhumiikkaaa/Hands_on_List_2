/*
 * Name     : Bhumika
 * Question : 49. Write a program to implement a semaphore to protect any critical section: b. Protect
 *             shared memory from concurrent write access
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main()
{
    int semid = semget(ftok(".", 'b'), 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }
    int shmid = shmget(ftok(".", 'm'), sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    int *counter = (int *)shmat(shmid, NULL, 0);
    if (counter == (void *)-1) {
        perror("shmat");
        exit(1);
    }
    union semun arg;
    struct sembuf lock = {0, -1, 0};
    struct sembuf unlock = {0, 1, 0};
    int i, temp;

    arg.val = 1;
    // binary semaphore, value 1
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }
    *counter = 0;                        // shared counter starts at 0

    // now parent and child both write to the shared counter
    if (fork() == -1) {
        perror("fork");
        exit(1);
    }

    for (i = 0; i < 5; i++) {
        // lock before touching shared memory
        if (semop(semid, &lock, 1) == -1) {
            perror("semop");
            exit(1);
        }
        temp = *counter;
        usleep(1000);                    // small delay: without the semaphore updates get lost
        *counter = temp + 1;
        printf("pid %d wrote counter = %d\n", getpid(), *counter);
        // unlock
        if (semop(semid, &unlock, 1) == -1) {
            perror("semop");
            exit(1);
        }
    }

    if (wait(NULL) > 0) {                // only the parent waits for the child
        printf("Final counter = %d (expected 10)\n", *counter);
        if (shmdt(counter) == -1) {
            perror("shmdt");
            exit(1);
        }
        // remove shared memory
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
    }
    return 0;
}

/*
 * Parent and child each increment the shared counter 5 times.
 *
 * Sample output:
 *
 * pid 891 wrote counter = 1
 * pid 892 wrote counter = 2
 * pid 891 wrote counter = 3
 * pid 892 wrote counter = 4
 * ...
 * Final counter = 10 (expected 10)
 */
