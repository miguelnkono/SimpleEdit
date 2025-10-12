//
// Created by gost on 9/10/25.
//

#include "output.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../data.h"
#include "../defines.h"
#include "../types/string_buf.h"

static int editorRowCxToRx(erow *row, int cx)
{
  int rx = 0;

  int j;
  for (j = 0; j < cx; j++)
  {
    if (row->chars[j] == '\t')
      rx += (EDITOR_TAB_STOP - 1) - (rx % EDITOR_TAB_STOP);

    rx++;
  }

  return rx;
}

void editorRefreshScreen()
{
  editorScroll();

  abuf ab = ABUF_INIT;

  abAppend(&ab, CURSOR_HIDE, CURSOR_HIDE_SIZE);
  abAppend(&ab, CURSOR_BEGIN, CURSOR_BEGIN_SIZE);

  // draw the tildes and reposition the cursor.
  editorDrawRows(&ab);
  // draw the status bar.
  editorDrawStatusBar(&ab);
  // draw the status bar message.
  editorDrawMessageBar(&ab);

  // allow the user to move the cursor.
  char buf[32];
  snprintf(buf, sizeof(buf), CURSOR_SET_POSITION, (E.cy - E.rowoff) + 1, (E.rx - E.coloff) + 1);
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
        if (welcomelen > E.screencols)
          welcomelen = E.screencols;

        // centering the message on the screen.
        int padding = (E.screencols - welcomelen) / 2;
        if (padding)
        {
          abAppend(ab, "~", 1);
          padding--;
        }
        while (padding--)
          abAppend(ab, " ", 1);

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
      if (len < 0)
        len = 0;
      if (len > E.screencols)
      {
        len = E.screencols;
      }
      abAppend(ab, &E.row[filerow].render[E.coloff], len);
    }

    abAppend(ab, SCREEN_CLEAR_LINE, SCREEN_CLEAR_LINE_SIZE);
    // if (y < E.screenrows - 1)
    // {
    //   // write(STDOUT_FILENO, SCREEN_NEW_LINE, SCREEN_NEW_LINE_SIZE);
    //   abAppend(ab, SCREEN_NEW_LINE, SCREEN_NEW_LINE_SIZE);
    // }
    abAppend(ab, SCREEN_NEW_LINE, SCREEN_NEW_LINE_SIZE);
  }
}

void editorScroll()
{
  E.rx = 0;
  if (E.rx < E.numrows)
  {
    E.rx = editorRowCxToRx(&E.row[E.cy], E.cx);
  }

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
  if (E.rx < E.coloff)
  {
    E.coloff = E.rx;
  }
  if (E.rx >= E.coloff + E.screencols)
  {
    E.coloff = E.rx - E.screencols + 1;
  }
}

void editorDrawStatusBar(abuf *ab)
{
  abAppend(ab, COLOR_INVERTED_COLOR, COLOR_INVERTED_COLOR_SIZE);

  char status[80], rstatus[80];
  int len = snprintf(status, sizeof(status), "%.20s - %d lines",
                     E.filename ? E.filename : "[No Name]", E.numrows);
  int rlen = snprintf(rstatus, sizeof(rstatus), "%d/%d", E.cy + 1, E.numrows);
  if (len > E.screencols)
    len = E.screencols;
  abAppend(ab, status, len);
  while (len < E.screencols)
  {
    if (E.screencols - len == rlen)
    {
      abAppend(ab, rstatus, rlen);
      break;
    }
    else
    {
      abAppend(ab, " ", 1);
      len++;
    }
  }

  abAppend(ab, COLOR_NORMAL, COLOR_NORMAL_SIZE);
  abAppend(ab, SCREEN_NEW_LINE, SCREEN_NEW_LINE_SIZE);
}

void editorSetStatusMessage(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(E.statussmg, sizeof(E.statussmg), fmt, ap);
  va_end(ap);
  E.statussmg_time = time(((void *)0)); // time(NULL)
}

void editorDrawMessageBar(abuf *ab)
{
  abAppend(ab, SCREEN_CLEAR_LINE, SCREEN_CLEAR_LINE_SIZE);
  int msglen = strlen(E.statussmg);
  if (msglen > E.screencols)
    msglen = E.screencols;
  if (msglen && time((void *)0) - E.statussmg_time < 5)
    abAppend(ab, E.statussmg, msglen);
}
