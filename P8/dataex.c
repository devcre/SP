#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fd;
    pid_t pid;
    caddr_t addr;
    struct stat statbuf;

    if (argc != 2) {
        fprintf(stderr, "Usage : %s filename\n", argv[0]);
        exit(1);
    }

    if (stat(argv[1], &statbuf) == -1) {
        perror("stat");
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        exit(1);
    }

    //mmap을 이용해 메모리 맵핑 실시
	addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);
	if(addr == MAP_FAILED){
		perror("mmap\n");
		exit(1);
	}

    close(fd);

    switch (pid = fork()) {
        case -1 :  /* fork failed */
            perror("fork");
            exit(1);
            break;
        case 0 :   /* child process */
            //printf로 데이터 확인
			printf("addr(child): %s\n", addr);
            //데이터 변경 및 동기화
			addr[0] = '0';
			msync(addr, statbuf.st_size, MS_SYNC);
            //바뀐 데이터 확인
			printf("changed addr(child): %s\n", addr);
            break;
        default :   /* parent process */
            //printf로 데이터 확인
			printf("addr(parent): %s\n", addr);
            //데이터 변경 및 동기화
			addr[1] = '1';
			msync(addr, statbuf.st_size, MS_SYNC);
            //바뀐 데이터 확인
			printf("changed addr(parent): %s\n", addr);

			// wait
			sleep(1);
            break;
    }

	// munmap
	if(munmap(addr, statbuf.st_size) == -1){
		perror("munmap failed\n");
		exit(1);
	}
	printf("access already unmaped space\n");
	printf("%s\n", addr);

    return 0;
}
