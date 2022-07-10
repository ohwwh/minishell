#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	int fd;

	fd = open("file1", O_WRONLY | O_CREAT, 0644);
	dup2(fd, 1);
	close(fd);
	printf("%s\n", "freaking test");
}