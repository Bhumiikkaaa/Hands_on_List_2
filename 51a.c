/*
 * Name     : Bhumika
 * Question : 51. Write a program to communicate between two machines using sockets. (Program 1 of 2:
 *             SERVER. Program 2 is 51b.c)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main()
{
    int s, c, n, opt = 1;
    struct sockaddr_in addr;
    char buf[100];

    s = socket(AF_INET, SOCK_STREAM, 0);                 // TCP socket
    if (s < 0) {
        perror("socket");
        exit(1);
    }
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;                   // accept on any network interface
    addr.sin_port = htons(PORT);                         // host byte order -> network byte order

    // attach socket to the port
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        exit(1);
    }
    // start listening (queue of 5)
    if (listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }

    printf("Server waiting on port %d ...\n", PORT);
    c = accept(s, NULL, NULL);                           // blocks until a client connects
    if (c < 0) {
        perror("accept");
        exit(1);
    }

    n = read(c, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("Server received: %s\n", buf);

    write(c, "Hello from server", 17);

    close(c);
    close(s);
    return 0;
}

/*
 * Terminal 1: ./51a.out    Terminal 2: ./51b.out <server-ip>
 *
 * Sample output:
 *
 * Server waiting on port 8080 ...
 * Server received: Hello from client
 */
