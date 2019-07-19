#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd1[2]; // child -> parent
	int fd2[2]; // parent -> child
    pid_t pid;
    char buf_childmge[257];
	char buf_parentmge[257];
    int len_c, status_c;
	int len_p, status_p;

    if ((pipe(fd1) == -1) || (pipe(fd2) == -1)) {
        perror("pipe");
        exit(1);
    }

    switch (pid = fork()) {
        case -1 :
            perror("fork");
            exit(1);
            break;
        case 0 : /* child */
            close(fd2[1]); // close fd2's function 'write'
			close(fd1[0]); // close fd1's function 'read'

			// read parent's message
            write(1, "Child Process:", 15);
            len_c = read(fd2[0], buf_parentmge, 256);
            write(1, buf_parentmge, len_c);

			// write child's message
			buf_parentmge[0] = '\0';
			write(fd1[1], "Test Message(c->p)\n", 20);
			close(fd1[1]);
			waitpid(pid, &status_c, 0);

            close(fd2[0]);
            break;
        default : /* parent */
            close(fd2[0]); // close fd2's function 'read'
			close(fd1[1]); // close fd1's function 'write'

			// write parent's message
            buf_childmge[0] = '\0';
            write(fd2[1], "Test Message(p->c)\n", 20);
            close(fd2[1]);
            waitpid(pid, &status_p, 0);

			// read child's message
			write(1, "Parent Process:", 15);
			len_p = read(fd1[0], buf_childmge, 256);
			write(1, buf_childmge, len_p);

			close(fd1[0]);
            break;
    }// do not have to make buffer as much as pipes

    return 0;
}
