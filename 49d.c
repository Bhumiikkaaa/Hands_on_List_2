/*
 * Name     : Bhumika
 * Question : 49. Write a program to implement a semaphore to protect any critical section: d. Remove the
 *             created semaphore
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main()
{
    char proj[3] = {'b', 'c', 'd'};      // project ids used in 48a, 48b, 49c
    int i, semid;

    for (i = 0; i < 3; i++) {
        semid = semget(ftok(".", proj[i]), 1, 0);    // open existing semaphore
        if (semid == -1) {
            printf("Semaphore '%c' not found\n", proj[i]);
            continue;
        }
        // remove it
        if (semctl(semid, 0, IPC_RMID) == -1) {
            perror("semctl");
            exit(1);
        }
        printf("Semaphore '%c' (id %d) removed\n", proj[i], semid);
    }
    return 0;
}

/*
 * Sample output:
 *
 * Semaphore 'b' (id 0) removed
 * Semaphore 'c' (id 1) removed
 * Semaphore 'd' (id 2) removed
 */
