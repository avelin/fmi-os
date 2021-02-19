/*
	Да се напише програма на C, която е аналогична на горния пример, но принуждава бащата да изчака сина си да завърши.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
	int n = 1000000;
	int status;

	if (fork() > 0) {
		wait(&status);
		for (int i = 0; i < n; i++) {
			printf("father\n");
		}
	} else {
		for (int i = 0; i < n; i++) {
			printf("son\n");
		}
	}

	exit(0);
}
