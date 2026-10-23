/*
 * Name     : Bhumika
 * Question : 37. Write two programs to enable communication through FIFO using one-way communication.
 *             (Program 1 of 2: WRITER. Program 2 is 37b.c)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    int fd;
    char msg[] = "Hello from writer";

    mkfifo("fifo1", 0666);           // create FIFO (fails harmlessly if it already exists)

    fd = open("fifo1", O_WRONLY);    // blocks until a reader opens the FIFO
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    write(fd, msg, strlen(msg));
    close(fd);

    printf("Writer sent: %s\n", msg);
    return 0;
}

/*
 * Terminal 1: ./37b.out   Terminal 2: ./37a.out
 *
 * Sample output:
 *
 * Writer sent: Hello from writer
 */
