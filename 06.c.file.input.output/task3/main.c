// Реализирайте команда wc, с един аргумент подаден като входен параметър
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main (int argc, char* argv[]){
	int fd1;
	char c;
	int lines = 0;
	int words = 0;
	int chars = 0;

	if (argc != 2) {
		fprintf(stderr, "err\n");
		exit(1);
	}

	if ( (fd1 = open(argv[1], O_RDONLY)) == -1 ) {
		fprintf(stderr, "Operation open failed\n");
		exit(1);
	}

	while ( read(fd1, &c, 1) > 0 ) {
		if (c=='\n') {
			lines++;
			words++;
		}

		if (c==' ') {
			words++;
		}

		chars++;
	}

	printf("File %s has:\n%d number of lines.\n%d number of words.\n%d number of chars.\n", argv[1], lines, words, chars);
	close(fd1);
}
