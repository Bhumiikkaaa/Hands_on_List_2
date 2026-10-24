/*
 * Name     : Bhumika
 * Question : 50. Develop a program that intentionally induces a deadlock scenario using
 *             semaphores.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// P operation (lock) on semaphore number n of the set
void lock(int semid, int n)
{
    struct sembuf op = {n, -1, 0};
    if (semop(semid, &op, 1) == -1) {
        perror("semop");
        exit(1);
    }
}

int main()
{
    key_t key = ftok(".", 'x');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int semid = semget(key, 2, IPC_CREAT | 0666);   // a set of 2 semaphores: 0 = resource A, 1 = resource B
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    union semun arg;
    arg.val = 1;                                    // both resources are free
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }
    if (semctl(semid, 1, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }

    setbuf(stdout, NULL);                           // no output buffering, because we kill the children later

    int pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(1);
    }
    if (pid1 == 0) {
        // ---- Process 1 : takes A first, then wants B ----
        lock(semid, 0);
        printf("Process 1 locked resource A\n");
        sleep(1);                                   // give process 2 time to lock B
        printf("Process 1 is waiting for resource B ...\n");
        lock(semid, 1);                             // blocks forever: B is held by process 2
        printf("Process 1 got both (never printed)\n");
        exit(0);
    }

    int pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(1);
    }
    if (pid2 == 0) {
        // ---- Process 2 : takes B first, then wants A (opposite order) ----
        lock(semid, 1);
        printf("Process 2 locked resource B\n");
        sleep(2);                                   // different delay from process 1, so the messages do not mix
        printf("Process 2 is waiting for resource A ...\n");
        lock(semid, 0);                             // blocks forever: A is held by process 1
        printf("Process 2 got both (never printed)\n");
        exit(0);
    }

    // ---- parent: wait a few seconds, then show that both are stuck ----
    sleep(4);
    printf("\nNo progress after 4 seconds -> DEADLOCK\n");
    printf("Processes waiting for A : %d\n", semctl(semid, 0, GETNCNT));
    printf("Processes waiting for B : %d\n", semctl(semid, 1, GETNCNT));

    kill(pid1, SIGKILL);                            // break the deadlock by killing both
    kill(pid2, SIGKILL);
    wait(NULL);
    wait(NULL);
    semctl(semid, 0, IPC_RMID);                     // remove the semaphore set
    return 0;
}

/*
 * Each process holds one semaphore and waits for the other one, so both wait forever.
 * GETNCNT shows how many processes are blocked on each semaphore.
 *
 * Sample output:
 *
 * Process 1 locked resource A
 * Process 2 locked resource B
 * Process 1 is waiting for resource B ...
 * Process 2 is waiting for resource A ...
 * 
 * No progress after 4 seconds -> DEADLOCK
 * Processes waiting for A : 1
 * Processes waiting for B : 1
 */
