/*
 * Name     : Bhumika
 * Question : 44. Write a program to receive messages from the message queue: a. With 0 as a flag
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

    printf("Waiting for a message (flag = 0, will block)...\n");

    // type 1 = take the first message of type 1, flag 0 = wait if none is there
    if (msgrcv(msqid, &m, sizeof(m.mtext), 1, 0) == -1) {
        perror("msgrcv");
        return 1;
    }

    printf("Received: %s\n", m.mtext);
    return 0;
}

/*
 * Run 43.c first to put a message in the queue.
 *
 * Sample output:
 *
 * Waiting for a message (flag = 0, will block)...
 * Received: Hello message queue
 * 
 * (if the queue is empty it keeps waiting until some other process sends a message)
 */
