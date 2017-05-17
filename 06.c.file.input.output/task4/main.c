/*
	Реализирайте команда swap, разменяща съдържанието на два файла, подадени като
	входни параметри. Приемаме, че двата файла имат еднакъв брой символи. Може да
	модифицирате решението, да работи и когато нямат еднакъв брой символи.
*/

#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char* argv[])
{
	if (argc != 3) {
		errx(1, "err");
	}

	int fd1;
	fd1 = open(argv[1], O_RDWR);
	if (fd1 == -1) {
		err(2, "%s", argv[1]);
	}

	int fd2;
	fd2 = open(argv[2], O_RDWR);
	if (fd2 == -1) {
		close(fd1);
		err(3, "%s", argv[2]);
	}

	int fd3;
	fd3 = open("my_temp_file", O_CREAT | O_RDWR | O_TRUNC);
	if (fd3 == -1) {
		close(fd1);
		close(fd2);
		err(4, "%s", "my_temp_file");
	}

	char c[4096];
	ssize_t read_size;


	while ((read_size = read(fd1, &c, sizeof(c))) > 0) {
		if (write(fd3, &c, read_size) != read_size ) {
			close(fd1);
			close(fd2);
			close(fd3);
			err(1, "Error while writing");
		}
	}

	lseek(fd1, 0, SEEK_SET);

	while ((read_size = read(fd2, &c, sizeof(c))) > 0 ) {
		if (write(fd1, &c, read_size) != read_size) {
			close(fd1);
			close(fd2);
			close(fd3);
			err(1, "Error while writing");
		}
	}

	lseek(fd2, 0, SEEK_SET);
	lseek(fd3, 0, SEEK_SET);

	while ((read_size = read(fd3, &c, sizeof(c))) > 0) {
		if (write(fd2, &c, read_size) != read_size) {
			close(fd1);
			close(fd2);
			close(fd3);
			err(1, "Error while writing");
		}
	}

	close(fd1);
	close(fd2);
	close(fd3);

	exit(0);
}

