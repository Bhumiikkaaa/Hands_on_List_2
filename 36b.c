/*
 * Name     : Bhumika
 * Question : 36. Create a FIFO file using: e. mkfifo library function
 */

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    // mkfifo(path, permissions) - simpler than mknod
    if (mkfifo("myfifo_mkfifo", 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    printf("FIFO created using mkfifo: myfifo_mkfifo\n");
    return 0;
}

/*
 * Sample output:
 *
 * FIFO created using mkfifo: myfifo_mkfifo
 * prw-r--r-- 1 root root 0 Oct 21 06:52 myfifo_mkfifo
 */
