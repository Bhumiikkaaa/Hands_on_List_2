/*
 * Name     : Bhumika
 * Question : 45. Write a program to change the existing message queue permissions using the msqid_ds
 *             structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    key_t key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }
    struct msqid_ds q;

    // 1. read current settings
    if (msgctl(msqid, IPC_STAT, &q) == -1) {
        perror("msgctl");
        exit(1);
    }
    printf("Old permission: %o\n", q.msg_perm.mode & 0777);

    q.msg_perm.mode = 0600;                  // 2. change permission to rw-------

    if (msgctl(msqid, IPC_SET, &q) == -1) {  // 3. write the settings back
        perror("msgctl");
        return 1;
    }

    // read again to confirm
    if (msgctl(msqid, IPC_STAT, &q) == -1) {
        perror("msgctl");
        exit(1);
    }
    printf("New permission: %o\n", q.msg_perm.mode & 0777);
    return 0;
}

/*
 * Sample output:
 *
 * Old permission: 666
 * New permission: 600
 */
