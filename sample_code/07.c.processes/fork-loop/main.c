#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

char* indent(int tabs);

char* indent(int tabs) {
	char * indentation = (char *) malloc(tabs + 1);

	for (int i = 0; i < tabs; ++i) {
//		indentation[i] = '\t';
		indentation[i] = ' ';
	}

	indentation[tabs] = '\0';
	return indentation;
}

const int N = 4;

int main(void) {
	for (int i = 0; i < N; ++i) {
		int pid = fork();
		char * indentation = indent(i);

		if (pid > 0) {
			printf("%s%d: I'm parent PID: %d PPID: %d\n", indentation, i,
				getpid(), getppid());
			// wait(NULL); // 1 - uncomment to order the tree
			// printf("%s%d: I'm parent PID: %d PPID: %d done waiting\n", indentation, i, getpid(), getppid());
			free(indentation);
		} else if (pid == 0) {
			printf("%s%d: I'm child PID %d PPID: %d\n", indentation, i,
				getpid(), getppid());
			free(indentation);
			// exit(0); // 2 - uncomment to create a vine
		}
	}
}
