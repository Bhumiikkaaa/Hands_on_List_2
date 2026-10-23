/*
 * Name     : Bhumika
 * Question : 46. Write a program to remove the message queue.
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
    int msqid = msgget(key, 0666);           // open existing queue (no IPC_CREAT)
    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {   // IPC_RMID = remove
        perror("msgctl");
        return 1;
    }

    printf("Message queue %d removed. Check with: ipcs -q\n", msqid);
    return 0;
}

/*
 * Sample output:
 *
 * Message queue 1 removed. Check with: ipcs -q
 */
