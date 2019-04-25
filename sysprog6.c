/** System Programming (6) : fork(2) **/

#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;

    switch( pid = fork() )
    {
        case -1 :	// fork failed
	    perror("fork failed");
	    exit(1);
	    break;

        case 0 :	// child process
	    printf("Child Process --- \n");
	    printf("PID : %d, PPID : %d \n", (int)getpid(), (int)getppid());
	    break;
	
        default :      	// parent process
	    printf("Parent Process --- \n");
	    printf("PID : %d, PPID : %d, Child PID : %d \n", (int)getpid(), (int)getppid(), (int)pid);
	    break;
    }

    printf("- - - - - - \n");

    return 0;
}
