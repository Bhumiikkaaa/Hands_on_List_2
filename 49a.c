/*
 * Name     : Bhumika
 * Question : 49. Write a program to implement a semaphore to protect any critical section: a. Rewrite the
 *             ticket number creation program using a semaphore
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
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
    key_t key = ftok(".", 'b');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    int semid, fd, ticket = 0;
    union semun arg;
    struct sembuf lock = {0, -1, 0};     // P operation : wait  (value - 1)
    struct sembuf unlock = {0, 1, 0};    // V operation : signal (value + 1)

    // create the semaphore with value 1; if it already exists, just open it
    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid >= 0) {
        arg.val = 1;
        if (semctl(semid, 0, SETVAL, arg) == -1) {
            perror("semctl");
            exit(1);
        }
    } else {
        semid = semget(key, 1, 0);
    }

    fd = open("ticket.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // ---- enter critical section ----
    if (semop(semid, &lock, 1) == -1) {
        perror("semop");
        exit(1);
    }

    read(fd, &ticket, sizeof(int));      // read last ticket (0 if file is new)
    ticket++;
    lseek(fd, 0, SEEK_SET);
    write(fd, &ticket, sizeof(int));     // store new ticket
    printf("Your ticket number is %d\n", ticket);
    printf("Press Enter to leave the critical section...\n");
    getchar();                           // hold the lock so another process has to wait

    // ---- leave critical section ----
    if (semop(semid, &unlock, 1) == -1) {
        perror("semop");
        exit(1);
    }

    close(fd);
    return 0;
}

/*
 * Run two copies at the same time in two terminals.
 *
 * Sample output:
 *
 * Terminal 1:                              Terminal 2 (started while T1 is waiting):
 * Your ticket number is 1                  (nothing - blocked on semaphore)
 * Press Enter to leave the critical...     
 * <Enter>                                  Your ticket number is 2
 *                                          Press Enter to leave the critical...
 */
