//
// Created by gost on 9/10/25.
//

#include "input.h"

#include <stdlib.h>
#include <unistd.h>

#include "../defines.h"
#include "../terminal/terminal.h"

void editorProcessKeypress() {
	char c = editorReadKey();	// we read the character from the terminal.

	switch (c) {
		case CTRL_KEY('q'):
			write(STDOUT_FILENO, "\x1b[2J", 4);
			write(STDOUT_FILENO, "\x1b[1;1H", 3);
			exit(0);
			break;
	}
}
