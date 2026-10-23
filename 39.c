/*
 * Name     : Bhumika
 * Question : 39. Write a program to wait for data to be written into a FIFO within 10 seconds, utilizing
 *             the select system call with the FIFO.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/select.h>

int main()
{
    int fd, ret, n;
    char buf[100];
    fd_set rfds;
    struct timeval tv;

    mkfifo("fifo_sel", 0666);

    // O_NONBLOCK: open() will not wait until a writer appears
    fd = open("fifo_sel", O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    FD_ZERO(&rfds);                  // clear the set
    FD_SET(fd, &rfds);               // watch the FIFO for reading

    tv.tv_sec = 10;                  // wait at most 10 seconds
    tv.tv_usec = 0;

    printf("Waiting for data on fifo_sel for 10 seconds...\n");
    ret = select(fd + 1, &rfds, NULL, NULL, &tv);

    if (ret == -1) {
        perror("select");
    } else if (ret == 0) {
        printf("No data within 10 seconds (timeout)\n");
    } else {
        n = read(fd, buf, sizeof(buf) - 1);
        buf[n] = '\0';
        printf("Data is available: %s\n", buf);
    }

    close(fd);
    return 0;
}

/*
 * Sample output:
 *
 * Case 1 - nothing written:
 * Waiting for data on fifo_sel for 10 seconds...
 * No data within 10 seconds (timeout)
 * 
 * Case 2 - in another terminal:  echo "hi there" > fifo_sel
 * Waiting for data on fifo_sel for 10 seconds...
 * Data is available: hi there
 */
