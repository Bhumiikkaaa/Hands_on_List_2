/*
 * Name     : Bhumika
 * Question : 41. Write a program to create a message queue, and print the key and message queue ID.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    key_t key;
    int msqid;

    key = ftok(".", 'a');                    // make a key from current directory + 'a'
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    msqid = msgget(key, IPC_CREAT | 0666);   // create queue (or open it if it exists)
    if (msqid == -1) {
        perror("msgget");
        return 1;
    }

    printf("Key              : %d (0x%x)\n", key, key);
    printf("Message queue id : %d\n", msqid);
    return 0;
}

/*
 * Sample output:
 *
 * Key              : 1627439342 (0x6100c0ee)
 * Message queue id : 1
 */
