/*
 * Name     : Bhumika
 * Question : 43. Write a program to send messages to the message queue. Check using $ ipcs -q
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;                      // message type (must be > 0)
    char mtext[100];                 // message data
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

    m.mtype = 1;
    strcpy(m.mtext, "Hello message queue");

    // size = only the data part, not including mtype
    if (msgsnd(msqid, &m, strlen(m.mtext) + 1, 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    printf("Message sent: %s\n", m.mtext);
    printf("Now run:  ipcs -q\n");
    return 0;
}

/*
 * Sample output:
 *
 * Message sent: Hello message queue
 * Now run:  ipcs -q
 * 
 * $ ipcs -q
 * ------ Message Queues --------
 * key        msqid      owner      perms      used-bytes   messages
 * 0x6100c0ee 0          root       666        20           1
 */
