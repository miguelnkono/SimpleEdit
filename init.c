//
// Created by gost on 9/10/25.
//

#include "init.h"

#include "terminal/terminal.h"
#include "data.h"

void initEditor() {
	E.cx = 0;
	E.cy = 0;
	E.numrows = 0;

	if (getWindowSize(&E.screenrows, &E.screencols) == -1) {
		die("GetWindowSize failed");
	}
}
