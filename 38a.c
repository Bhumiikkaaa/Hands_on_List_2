/*
 * Name     : Bhumika
 * Question : 38. Write two programs to establish communication through FIFO using two-way communication.
 *             (Program 1 of 2. Program 2 is 38b.c)
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

    mkfifo("fifo_a_to_b", 0666);    // one FIFO for each direction
    mkfifo("fifo_b_to_a", 0666);

    fd1 = open("fifo_a_to_b", O_WRONLY);   // A -> B
    if (fd1 == -1) {
        perror("open");
        exit(1);
    }
    fd2 = open("fifo_b_to_a", O_RDONLY);   // B -> A
    if (fd2 == -1) {
        perror("open");
        exit(1);
    }

    write(fd1, "Hello from A", 12);

    n = read(fd2, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("A received: %s\n", buf);

    close(fd1);
    close(fd2);
    return 0;
}

/*
 * Terminal 1: ./38b.out   Terminal 2: ./38a.out
 *
 * Sample output:
 *
 * A received: Hello from B
 */
