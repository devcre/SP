#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int i;
	mode_t old; // original umask value
	old = umask(0);

	if(argc<2){
		fprintf(stderr,"%s : no arguments\n", argv[0]);
		exit(1);	
	}
	for(i=1; i<argc; i++){
		mkdir(argv[i], S_IRUSR| S_IWUSR| S_IXUSR| S_IRGRP| S_IWGRP| S_IXGRP| S_IROTH| S_IWOTH| S_IXOTH);
	//mkdir 함수를 이용해 argv를 통해 들어온 디렉토리 이름을 가진 폴더를 권한 0777번으로 생성
	}
	umask(old); // <- if this code is missed, dirctory's authority level maintain?
}
