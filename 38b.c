/*
 * Name     : Bhumika
 * Question : 38. Write two programs to establish communication through FIFO using two-way communication.
 *             (Program 2 of 2. Program 1 is 38a.c)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    int fd1, fd2, n;
    char buf[100];

    mkfifo("fifo_a_to_b", 0666);
    mkfifo("fifo_b_to_a", 0666);

    fd1 = open("fifo_a_to_b", O_RDONLY);   // A -> B  (same order as A, so no deadlock)
    if (fd1 == -1) {
        perror("open");
        exit(1);
    }
    fd2 = open("fifo_b_to_a", O_WRONLY);   // B -> A
    if (fd2 == -1) {
        perror("open");
        exit(1);
    }

    n = read(fd1, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("B received: %s\n", buf);

    write(fd2, "Hello from B", 12);

    close(fd1);
    close(fd2);
    return 0;
}

/*
 * Terminal 1: ./38b.out   Terminal 2: ./38a.out
 *
 * Sample output:
 *
 * B received: Hello from A
 */
