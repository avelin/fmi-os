/*
	Да се напише програма на C, която изпълнява команда ls с точно един аргумент.
*/

#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

int main (int argc, char* argv[])
{

	if (argc != 2) {
		errx(1, "err");
	}

	if (execlp("/bin/ls", "ls", argv[1], 0) == -1) {
		err(99, "err execling");
	} else {
		printf("foobar\n");
	}

	exit(0);
}
