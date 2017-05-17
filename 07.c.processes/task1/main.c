/*
	Да се напише програма на C, която изпълнява команда date.
*/

#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

int main ()
{
	if (execl("/bin/date", "date", (char *)NULL) == -1) {
		err(99, "err execling");
	} else {
		printf("foobar\n");
	}

	exit(0);
}
