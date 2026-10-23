/*
 * Name     : Bhumika
 * Question : 36. Create a FIFO file using: d. mknod system call
 */

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    // S_IFIFO tells mknod that we want a FIFO file, 0666 = permissions
    if (mknod("myfifo_mknod", S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        return 1;
    }

    printf("FIFO created using mknod: myfifo_mknod\n");
    return 0;
}

/*
 * Sample output:
 *
 * FIFO created using mknod: myfifo_mknod
 * prw-r--r-- 1 root root 0 Oct 21 06:52 myfifo_mknod
 */
