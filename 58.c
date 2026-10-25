/*
 * Name     : Bhumika
 * Question : 58. Write a simple program to create three threads and print the IDs of the created
 *             threads.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *work(void *arg)
{
    int n = *(int *)arg;
    printf("  Thread %d is running, its id = %lu\n", n, (unsigned long)pthread_self());
    return NULL;
}

int main()
{
    pthread_t t[3];
    int num[3] = {1, 2, 3};
    int i;

    for (i = 0; i < 3; i++) {
        if (pthread_create(&t[i], NULL, work, &num[i]) != 0) {   // start thread
            perror("pthread_create");
            exit(1);
        }
        printf("Main created thread %d, id = %lu\n", i + 1, (unsigned long)t[i]);
    }

    for (i = 0; i < 3; i++)
        pthread_join(t[i], NULL);                                 // wait for thread to finish

    printf("All threads finished\n");
    return 0;
}

/*
 * (thread ids are different on every run)
 *
 * Sample output:
 *
 *   Thread 1 is running, its id = 140463029876416
 * Main created thread 1, id = 140463029876416
 * Main created thread 2, id = 140462945990336
 * Main created thread 3, id = 140462937597632
 *   Thread 2 is running, its id = 140462945990336
 *   Thread 3 is running, its id = 140462937597632
 * All threads finished
 */
