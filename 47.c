/*
 * Name     : Bhumika
 * Question : 47. Write a program to create shared memory and perform the following operations: a. Write
 *             some data to the shared memory b. Attach with O_RDONLY and check whether you
 *             are able to overwrite c. Detach the shared memory d. Remove the shared memory
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main()
{
    key_t key = ftok(".", 's');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    int shmid = shmget(key, 1024, IPC_CREAT | 0666);   // create 1024 byte shared memory
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    char *ptr;
    int status;

    // ---- a. attach for read/write and write some data ----
    ptr = (char *)shmat(shmid, NULL, 0);
    if (ptr == (void *)-1) {
        perror("shmat");
        exit(1);
    }
    strcpy(ptr, "Hello shared memory");
    printf("a. Written data : %s\n", ptr);
    if (shmdt(ptr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // ---- b. attach read-only and try to overwrite ----
    ptr = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (ptr == (void *)-1) {
        perror("shmat");
        exit(1);
    }
    printf("b. Read-only attach, data = %s\n", ptr);

    int pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        strcpy(ptr, "overwrite");    // writing to a read-only page -> SIGSEGV
        printf("   Overwrite worked\n");
        return 0;
    }
    wait(&status);                   // the child is killed by SIGSEGV, so parent survives
    if (WIFSIGNALED(status))
        printf("   Overwrite FAILED: child killed by signal %d (SIGSEGV)\n", WTERMSIG(status));

    // ---- c. detach ----
    if (shmdt(ptr) == -1) {
        perror("shmdt");
        exit(1);
    }
    printf("c. Detached\n");

    // ---- d. remove ----
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
    printf("d. Shared memory removed\n");
    return 0;
}

/*
 * Sample output:
 *
 * a. Written data : Hello shared memory
 * b. Read-only attach, data = Hello shared memory
 *    Overwrite FAILED: child killed by signal 11 (SIGSEGV)
 * c. Detached
 * d. Shared memory removed
 */
