//
// Created by gost on 9/10/25.
//

#include "init.h"

#include "terminal/terminal.h"

void initEditor() {
	if (getWindowSize(&E.screenrows, &E.screencols) == -1) {
		die("GetWindowSize failed");
	}
}
