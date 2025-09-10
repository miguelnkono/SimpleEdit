#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>		// use to manipulate error of the system.

#include "terminal/terminal.h"

int main(void) {
	enableRawMode();

	// read keypresses from the user.
	// STDIN_FILENO represent the standard input.
	// here we are reading one byte from the standard input into the c char variable until there is no more to read.
	// when there is no more to read the read() function will return 0 instead of the number of byte read.
	while (1) {
		char c = '\0';
		if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
		if (iscntrl(c)) {
			printf("%d\r\n", c);
		} else {
			printf("%d ('%c')\r\n", c, c);
		}
		if (c == 'q')
			break;
	}

	return 0;
}
