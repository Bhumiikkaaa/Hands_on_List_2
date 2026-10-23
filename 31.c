/*
 * Name     : Bhumika
 * Question : 31. Write a simple program to create a pipe, write to the pipe, read from the pipe, and
 *             display the content on the monitor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int fd[2];                       // fd[0] = read end, fd[1] = write end
    char buf[100];
    int n;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    write(fd[1], "Hello pipe", 10);  // write into the pipe

    n = read(fd[0], buf, sizeof(buf));
    if(n==-1){
	perror("read");
	close(fd[0]);
	close(fd[1]);
	return 1;
    }
    buf[n] = '\0';

    printf("Read from pipe: %s\n", buf);
    close(fd[0]);
    close(fd[1]);
    return 0;
}

/*
 * Sample output:
 *
 * Read from pipe: Hello pipe
 */
