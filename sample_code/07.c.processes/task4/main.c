/*
	Да се напише програма на C, която създава процес дете и демонстрира
принцина на конкурентност при процесите.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

int main(void)
{
	int n = 1000000;

	pid_t a = fork();
	if (a == -1) {
		err(1, "BOO");
	}
	if (a > 0) {
		for (int i = 0; i < n; i++) {
//			printf("father\n");
			write(1,"F", 1);
		}
	} else {
		for (int i = 0; i < n; i++) {
//			printf("son\n");
			write(1,"S", 1);
		}
	}

	write(1,"\n", 1);

	exit(0);
}
