/*
 * Name     : Bhumika
 * Question : 52. Write a program to create a concurrent server: b. Use pthread_create
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

void *serve(void *arg)
{
    int c = (int)(long)arg;                              // client socket passed to the thread
    char buf[100];
    int n;

    n = read(c, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("Thread %lu received: %s\n", (unsigned long)pthread_self(), buf);
    sleep(3);                                            // pretend to do some work
    write(c, "Hello from server", 17);
    close(c);
    return NULL;
}

int main()
{
    int s, c, opt = 1;
    struct sockaddr_in addr;
    pthread_t t;

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
    printf("Concurrent server (pthread) waiting on port %d ...\n", PORT);

    while (1) {
        c = accept(s, NULL, NULL);
        if (c < 0) {
            perror("accept");
            continue;
        }
        // one thread per client
        if (pthread_create(&t, NULL, serve, (void *)(long)c) != 0) {
            perror("pthread_create");
            exit(1);
        }
        pthread_detach(t);                                  // thread cleans up by itself
    }
}

/*
 * Compile: gcc 52b.c -o 52b.out -pthread     Clients: run ./51b.out in 2-3 terminals.
 *
 * Sample output:
 *
 * Concurrent server (pthread) waiting on port 8080 ...
 * Thread 140105417225920 received: Hello from client
 * Thread 140105408833216 received: Hello from client
 * Thread 140105400440512 received: Hello from client
 */
