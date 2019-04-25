/** System Programming (3) : read **/

#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int fd, n;
    char buf[10];

    fd = open("erica.txt", O_RDONLY);

    if( fd == -1 )
    {
        perror("open : O_RDONLY");
	exit(1);
    }

    n = read (fd, buf, 8);

    printf("read(2) : nbytes = %d, buf = %s \n", n, buf);

    close(fd);

    return 0;
}
