#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

static void do_ls(char *path);

int main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        fprintf(stderr, "%s: no arguments\n", argv[0]);
        exit(1);
    }
    for (i = 1; i < argc; i++) {
        do_ls(argv[i]);
    }
    exit(0);
}

static void do_ls(char *path)
{
    DIR *d;
    struct dirent *ent;

	struct stat st; // for st_uid
	char *mtime; // hold time

    d = opendir(path);          /* (1) */
    if (!d) {
        perror(path);
        exit(1);
    }

	
    while (ent = readdir(d)) {  /* (2) */
		if(lstat(ent->d_name, &st) < 0) exit(1);
        printf("%s\n", ent->d_name);
		printf("%ld\n", st.st_uid);
		mtime = ctime(&st.st_mtime);
		printf("%s\n", mtime);
    }
    closedir(d);                /* (1') */
}
