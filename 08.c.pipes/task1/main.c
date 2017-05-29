#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

	if (argc != 2) {
		errx(1, "Invalid number of arguments. Usage: %s <filename>", argv[0]);
	}

	const int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		err(1, "Could not open output file %s", argv[1]);
	}

	const char* str1 = "foo\n";
	const char* str2 = "bar\n";

	if (write(fd, str1, 2) != 2) {
		const int savederrorcode = errno;
		close(fd);
		errno = savederrorcode;
		err(1, "Could not write first two chars from parent");
	}

	const pid_t child_pid = fork();
	if (child_pid == -1) {
		const int savederrorcode = errno;
		close(fd);
		errno = savederrorcode;
		err(1, "Could not fork.");
	}

	if (child_pid == 0) {
		if (write(fd, str2, 4) != 4) {
			const int savederrorcode = errno;
			close(fd);
			errno = savederrorcode;
			err(1, "Could not write four chars from child.");
		}
		exit(0);
	}

	int child_status;
	const pid_t wait_code = wait(&child_status);

	if (wait_code == -1) {
		const int savederrorcode = errno;
		close(fd);
		errno = savederrorcode;
		err(1, "Could not wait for child.");
	}

	if (!WIFEXITED(child_status)) {
		const int savederrorcode = errno;
		close(fd);
		errno = savederrorcode;
		err(1, "Child did not terminate normally.");
	}

	if (WEXITSTATUS(child_status) != 0) {
		err(1, "Child exit code not 0, file should be already closed.");
	}

	if (write(fd, str1+2, 2) != 2) {
		const int savederrorcode = errno;
		close(fd);
		errno = savederrorcode;
		err(1, "Could not write the last two chars from parent");
	}

	close(fd);
	exit(0);
}
