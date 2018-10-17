#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#define pwned "\tAdrielFreud\n\n"

static void filetype(const char *filename);

int main(int argc, char **argv){
	char **fn;
	if(argc < 2){
		puts(pwned);
		fprintf(stderr, "Use: %s [arquivo...]\n", *argv);
		return 1;
	}else{
		fn = ++argv;
	}

	while(--argc){
		puts(pwned);
		filetype(*fn++);
	}
	return 0;
}

static void filetype(const char *filename){
	int size;
	struct stat st;
	char temp[1024];
	if(lstat(filename, &st) == -1){
		perror("stat");
		return;
	}
	size = (int)st.st_size;
	memset(temp, 0, sizeof(temp));
	if(S_ISREG(st.st_mode)){
		fprintf(stdout, "%s: Arquivo Comum, %d bytes\n", filename, size);
	}

	if(S_ISDIR(st.st_mode)){
		fprintf(stdout, "%s: Diretorio, %d bytes\n", filename, size);
	}

	if(S_ISCHR(st.st_mode)){
		fprintf(stdout, "%s: Character device!\n", filename);
	}

	if(S_ISBLK(st.st_mode)){
		fprintf(stdout, "%s: Block device!\n", filename);
	}

	if(S_ISFIFO(st.st_mode)){
		fprintf(stdout, "%s: FIFO\n", filename);
	}

	if(S_ISLNK(st.st_mode)){
		readlink(filename, temp, sizeof(temp));
		fprintf(stdout, "%s: Link para %s\n", filename, temp);
	}

	if(S_ISSOCK(st.st_mode)){
		fprintf(stdout, "%s: Unix domain socket!\n", filename);
	}
}
