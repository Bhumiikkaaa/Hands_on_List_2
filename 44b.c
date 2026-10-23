/*
 * Name     : Bhumika
 * Question : 44. Write a program to receive messages from the message queue: b. With IPC_NOWAIT as a flag
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char mtext[100];
};

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
    struct msgbuf m;

    // IPC_NOWAIT: if there is no message, return immediately with an error
    if (msgrcv(msqid, &m, sizeof(m.mtext), 1, IPC_NOWAIT) == -1) {
        perror("msgrcv");            // prints "No message of desired type"
        return 1;
    }

    printf("Received: %s\n", m.mtext);
    return 0;
}

/*
 * With a message in the queue it prints  Received: Hello message queue
 *
 * Sample output:
 *
 * msgrcv: No message of desired type
 * 
 * (queue was empty, so it returns immediately instead of waiting)
 */
