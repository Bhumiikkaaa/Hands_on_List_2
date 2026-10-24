/*
 * Name     : Bhumika
 * Question : 52. Write a program to create a concurrent server: a. Use fork
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main()
{
    int s, c, n, opt = 1;
    struct sockaddr_in addr;
    char buf[100];

    signal(SIGCHLD, SIG_IGN);                            // do not leave zombie children

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("socket");
        exit(1);
    }
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        exit(1);
    }
    if (listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }
    printf("Concurrent server (fork) waiting on port %d ...\n", PORT);

    while (1) {
        c = accept(s, NULL, NULL);                       // wait for next client
        if (c < 0) {
            perror("accept");
            continue;
        }

        int pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            // ---- child: serves this one client ----
            close(s);                                    // child does not need listening socket
            n = read(c, buf, sizeof(buf) - 1);
            buf[n] = '\0';
            printf("Child %d received: %s\n", getpid(), buf);
            sleep(3);                                    // pretend to do some work
            write(c, "Hello from server", 17);
            close(c);
            exit(0);
        }
        close(c);                                        // parent does not need this client socket
    }
}

/*
 * Compile: gcc 52a.c -o 52a.out     Clients: run ./51b.out in 2-3 terminals.
 *
 * Sample output:
 *
 * Concurrent server (fork) waiting on port 8080 ...
 * Child 931 received: Hello from client
 * Child 932 received: Hello from client
 * Child 933 received: Hello from client
 * 
 * (three clients started together are served at the same time by three children)
 */
