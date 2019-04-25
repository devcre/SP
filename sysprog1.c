/** System Programming (1) : open, close **/

#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int fd;
    mode_t mode;

    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    fd = open("erica.txt", O_CREAT, mode);

    if( fd == -1 )
    {
        perror("open : O_CREAT");
	exit(1);
    }

    close(fd);

    return 0;
}
