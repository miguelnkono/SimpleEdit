#include "terminal/terminal.h"
#include "init.h"
#include "io/input.h"
#include "io/output.h"
#include "data.h"

editorConfig E = {0};

int main(void) {
	enableRawMode();
	initEditor();

	while (1) {
		editorRefreshScreen();
		editorProcessKeypress();
	}
	return 0;
}
