#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

int main() {
	
	// 0 = READ
	// 1 = WRITE
	
	srand(time(NULL));
	
	int pipe1[2];
	int pipe2[2];
	pipe(pipe1);
	pipe(pipe2);
	int f = fork();
	int x = 0;
	int y = 0;
	int z = 0;
	
	// parent
	if (f == 0) {
		close(pipe1[0]);
		x = rand() % 100;
		write(pipe1[1], &x, sizeof(int));
		printf("[parent] sending: %d\n", x);
	}
	// child
	if (f != 0) {
		close(pipe1[1]);
		read(pipe1[0], &x, sizeof(int));
		printf("[child] doing maths on: %d\n", x);
		y = x * x;
		close(pipe2[0]);
		write(pipe2[1], &y, sizeof(int));
	}
	// parent
	if (f == 0) {
		close(pipe2[1]);
		read(pipe2[0], &z, sizeof(int));
		printf("[parent] received: %d\n", z);
	}
	return 0;
}