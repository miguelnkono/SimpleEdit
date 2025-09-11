//
// Created by gost on 9/10/25.
//

#include "terminal.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "../defines.h"

void enableRawMode() {
	if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr");
	atexit(disableRawMode);
	// this register the disableRawMode function to be call when the exit function is call, typically when the entire program exit.

	// the raw terminal state.
	struct termios raw = E.orig_termios;

	// this turn off the echoing on the terminal. Meaning that when the user type in they see nothing appearing.
	// turn of the canonical mode. Meaning we are now able to read bytes-by-bytes not line by lines.
	// c_lflag	-> local flag
	// c_iflag	-> input flag
	// c_oflag	-> output flag
	// c_cflag	-> control flag
	// ISIG manage the SIGINT(Ctrl-c) and the SIGTSTP(Ctrl-z) signal which sent a terminated and a suspend signals respectivily to the program.
	// Ctrl-v makes the terminal to waits until the user type in a character and sent it literally.
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

	// turning off some input flags.
	raw.c_iflag &= ~(
		ICRNL // by default the terminal translate the carriage return('\r') into new-line('\n').
		| IXON // IXON for Ctrl-S and Ctrl-Q which stop the data transfer to the program and restore it respectivily.
		| BRKINT // if turn on, a break condition will cause SIGINT signal to be sent to the program.
		| INPCK // turn of the parity check(somehow nothing present in modern terminal emulator).
		| ISTRIP // cause the 8 bits of input byte to be strip to 0.
	);

	// turning off some output flags.
	raw.c_oflag &= ~(
		OPOST
		// by default the terminal translate any new line it receives into a combination of cariage followed by new-line('\r\n').
	);

	// turning off some control flags.
	raw.c_cflag |= (CS8); // this is a bit mask that set the byte size to 8 bits.

	// changes the time settings for the terminal.
	raw.c_cc[VMIN] = 0; // set the minimum number of byte of input needed before read() returns.
	raw.c_cc[VTIME] = 1; // set the maximum amount of time to wait before read() can return.

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

void disableRawMode() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1) die("tcsetattr");
}

void die(const char *msg) {
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[1;1H", 3);

	perror(msg); // looks for the erno variable previous error and print it.
	exit(1);
}

char editorReadKey() {
	char c;
	ssize_t nread;

	while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
		if (nread == -1 && errno == EAGAIN) die("read");
	}

	return c;
}

int getWindowSize(int *rows, int *cols) {
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
		if (write(STDOUT_FILENO, CURSOR_BOTTOM_RIGHT, CURSOR_BOTTOM_RIGHT_SIZE) != 12) return -1;

		return getCursorPosition(rows, cols);
	} else {
		*cols = ws.ws_col;
		*rows = ws.ws_row;
		return 0;
	}
}

int getCursorPosition(int *rows, int *cols) {
	char buf[32];
	unsigned int i = 0;

	if (write(STDOUT_FILENO, CURSOR_POSITION, CURSOR_POSITION_SIZE) != 4) return -1;

	while (i < sizeof(buf) - 1) {
		if (read(STDIN_FILENO, &buf[i], 1) == -1) break;
		if (buf[i] == 'R') break;
		i++;
	}
	buf[i] = '\0';	// terminate the string.

	if (buf[0] != ESCAPE_SEQUENCE || buf[1] != '[') return -1;
	if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;

	return 0;
}
