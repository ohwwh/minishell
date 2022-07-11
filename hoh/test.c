#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	int fd;

	printf("%d: %s\n", getpid(), "freaking test");
	while(1);
}