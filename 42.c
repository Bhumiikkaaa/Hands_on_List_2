/*
 * Name     : Bhumika
 * Question : 42. Write a program to print information about a message queue using msqid_ds and ipc_perm
 *             structures: a. Access permission b. UID, GID c. Time of last message sent and
 *             received d. Time of last change in the message queue e. Size of the queue f.
 *             Number of messages in the queue g. Maximum number of bytes allowed h. PID of
 *             the msgsnd and msgrcv
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void show_time(char *label, time_t t)
{
    if (t == 0){
        printf("%s: never\n", label);
   } else{
	char *time_str = ctime(&t);
	if(time_str == NULL){
		printf("%s: unavailable\n", label);
	} else{
		printf("%s: %s", label, time_str);
	}
   }
}

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

    // copy queue information into q
    if (msgctl(msqid, IPC_STAT, &q) == -1) {
        perror("msgctl");
        exit(1);
    }

    printf("a. Access permission        : %o\n", q.msg_perm.mode);
    printf("b. uid                      : %d\n", q.msg_perm.uid);
    printf("   gid                      : %d\n", q.msg_perm.gid);
    show_time("c. Last message sent       ", q.msg_stime);
    show_time("   Last message received   ", q.msg_rtime);
    show_time("d. Last change             ", q.msg_ctime);
    printf("e. Size of queue (bytes)    : %lu\n", (unsigned long)q.__msg_cbytes);
    printf("f. Number of messages       : %lu\n", (unsigned long)q.msg_qnum);
    printf("g. Max bytes allowed        : %lu\n", (unsigned long)q.msg_qbytes);
    printf("h. pid of last msgsnd       : %d\n", q.msg_lspid);
    printf("   pid of last msgrcv       : %d\n", q.msg_lrpid);
    return 0;
}

/*
 * Sample output:
 *
 * a. Access permission        : 666
 * b. uid                      : 0
 *    gid                      : 0
 * c. Last message sent       : never
 *    Last message received   : never
 * d. Last change             : Wed Oct 21 06:52:43 2026
 * e. Size of queue (bytes)    : 0
 * f. Number of messages       : 0
 * g. Max bytes allowed        : 16384
 * h. pid of last msgsnd       : 0
 *    pid of last msgrcv       : 0
 */
