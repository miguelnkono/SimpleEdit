//
// Created by gost on 9/10/25.
//

#include "output.h"

#include <unistd.h>

#include "../defines.h"
#include "../types/string_buf.h"

void editorRefreshScreen() {
	abuf ab = ABUF_INIT;

	abAppend(&ab, CURSOR_HIDE, CURSOR_HIDE_SIZE);
	abAppend(&ab, CURSOR_BEGIN, CURSOR_BEGIN_SIZE);

	// draw the tildes and reposition the cursor.
	editorDrawRows(&ab);

	abAppend(&ab, CURSOR_BEGIN, CURSOR_BEGIN_SIZE);
	abAppend(&ab, CURSOR_SHOW, CURSOR_SHOW_SIZE);

	// then one big write.
	write(STDOUT_FILENO, ab.buf, ab.len);
	abFree(&ab);
}

void editorDrawRows(abuf *ab) {
	int y;

	for (y = 0; y < E.screenrows; y++) {
		// write(STDOUT_FILENO, SCREEN_TILDE, SCREEN_TILDE_SIZE);
		abAppend(ab, SCREEN_TILDE, SCREEN_TILDE_SIZE);

		abAppend(ab, SCREEN_CLEAR_LINE, SCREEN_CLEAR_LINE_SIZE);
		if (y < E.screenrows - 1) {
			// write(STDOUT_FILENO, SCREEN_NEW_LINE, SCREEN_NEW_LINE_SIZE);
			abAppend(ab, SCREEN_NEW_LINE, SCREEN_NEW_LINE_SIZE);
		}
	}
}
