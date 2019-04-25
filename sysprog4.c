/** System Programming (4) : read, write **/

#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int read_fd, write_fd, n;
    char buf[10];

    read_fd = open("erica.txt", O_RDONLY);

    if( read_fd == -1 )
    {
        perror("open : O_RDONLY");
	exit(1);
    }

    write_fd = open("erica2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if( write_fd == -1 )
    {
        perror("open : O_WRONLY");
	exit(1);
    }

    while( (n = read( read_fd, buf, 8)) > 0 )
        if( write( write_fd, buf, n) != n)
	    perror("Write");

    if( n == -1 )
        perror("Read");

    close(read_fd);
    close(write_fd);

    return 0;
}
