/*
 * Name     : Bhumika
 * Question : 37. Write two programs to enable communication through FIFO using one-way communication.
 *             (Program 2 of 2: READER. Program 1 is 37a.c)
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    int fd, n;
    char buf[100];

    mkfifo("fifo1", 0666);

    fd = open("fifo1", O_RDONLY);    // blocks until a writer opens the FIFO
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    n = read(fd, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    close(fd);

    printf("Reader received: %s\n", buf);
    return 0;
}

/*
 * Terminal 1: ./37b.out   Terminal 2: ./37a.out
 *
 * Sample output:
 *
 * Reader received: Hello from writer
 */
