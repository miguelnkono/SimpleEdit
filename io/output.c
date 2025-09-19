//
// Created by gost on 9/10/25.
//

#include "output.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../defines.h"
#include "../types/string_buf.h"

void editorRefreshScreen() {
	editorScroll();

	abuf ab = ABUF_INIT;

	abAppend(&ab, CURSOR_HIDE, CURSOR_HIDE_SIZE);
	abAppend(&ab, CURSOR_BEGIN, CURSOR_BEGIN_SIZE);

	// draw the tildes and reposition the cursor.
	editorDrawRows(&ab);

	// allow the user to move the cursor.
	char buf[32];
	snprintf(buf, sizeof(buf), CURSOR_SET_POSITION, (E.cy - E.rowoff) + 1, (E.cx - E.coloff) + 1);
	abAppend(&ab, buf, (int)strlen(buf));

	abAppend(&ab, CURSOR_SHOW, CURSOR_SHOW_SIZE);

	// then one big write.
	write(STDOUT_FILENO, ab.buf, ab.len);
	abFree(&ab);
}

void editorDrawRows(abuf *ab) 
{
	int y;

	for (y = 0; y < E.screenrows; y++) 
	{
		int filerow = y + E.rowoff;
		if (filerow >= E.numrows)
		{
			if (E.numrows == 0 && y == E.screenrows / 3) 
			{
				char welcome[32];
				int welcomelen = snprintf(welcome, sizeof(welcome), "Kilo editor --version %s", EDITOR_VERSION);
				if (welcomelen > E.screencols) welcomelen = E.screencols;

				// centering the message on the screen.
				int padding = (E.screencols - welcomelen) / 2;
				if (padding) 
				{
					abAppend(ab, "~", 1);
					padding--;
				}
				while (padding--) abAppend(ab, " ", 1);

				abAppend(ab, welcome, welcomelen);
			}
			else 
			{
				abAppend(ab, SCREEN_TILDE, SCREEN_TILDE_SIZE);
			}
		}
		else 
		{
			int len = E.row[filerow].rsize - E.coloff;
			if (len < 0) len = 0;
			if (len > E.screencols)
			{
				len = E.screencols;
			}
			abAppend(ab, &E.row[filerow].render[E.coloff], len);
		}

		abAppend(ab, SCREEN_CLEAR_LINE, SCREEN_CLEAR_LINE_SIZE);
		if (y < E.screenrows - 1) {
			// write(STDOUT_FILENO, SCREEN_NEW_LINE, SCREEN_NEW_LINE_SIZE);
			abAppend(ab, SCREEN_NEW_LINE, SCREEN_NEW_LINE_SIZE);
		}
	}
}

void editorScroll()
{
	// vertical scrolling.
	if (E.cy < E.rowoff)
	{
		E.rowoff = E.cy;
	}
	if (E.cy >= E.rowoff + E.screenrows)
	{
		E.rowoff = E.cy - E.screenrows + 1;
	}

	// horizontal scrolling.
	if (E.cx < E.coloff)
	{
		E.coloff = E.cx;
	}
	if (E.cx >= E.coloff + E.screencols)
	{
		E.coloff = E.cx - E.screencols + 1;
	}
}

