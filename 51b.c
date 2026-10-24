/*
 * Name     : Bhumika
 * Question : 51. Write a program to communicate between two machines using sockets. (Program 2 of 2:
 *             CLIENT. Program 1 is 51a.c)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char *argv[])
{
    int s, n;
    struct sockaddr_in addr;
    char buf[100];
    char *ip = "127.0.0.1";

    if (argc == 2)
        ip = argv[1];                                    // IP address of the other machine

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("socket");
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, ip, &addr.sin_addr);              // text IP -> binary IP

    if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("connect");
        return 1;
    }

    write(s, "Hello from client", 17);

    n = read(s, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("Client received: %s\n", buf);

    close(s);
    return 0;
}

/*
 * Terminal 1: ./51a.out    Terminal 2: ./51b.out <server-ip>
 * For two machines find the server's IP with:  hostname -I
 *
 * Sample output:
 *
 * Client received: Hello from server
 */
