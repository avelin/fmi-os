/*
	Реализирайте команда head без опции (т.е. винаги да извежда
	на стандартния изход само първите 10 реда от съдържанието на
	файл подаден като първи параматър)
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int fd1;
	int i = 0;
	char c;

	if (argc != 2) {
		write(2, "err\n", 4);
		exit(-1);
	}

	if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
		write(2, "File failed to open in read mode\n", 33);
		exit(-1);
	}

	while (read(fd1, &c, 1)) {
		if (c == '\n') {
			i=i+1;
		}

		write(1, &c, 1);

		if (i == 10) {
			break;
		}
	}

	close(fd1);
	exit(0);
}
