//
// Created by gost on 9/10/25.
//

#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "../data.h"
#include "../defines.h"
#include "../terminal/terminal.h"
#include "operations.h"

void editorProcessKeypress()
{
  const int c = editorReadKey(); // we read the character from the terminal.

  switch (c)
  {
  case CTRL_KEY('q'):
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[1;1H", 3);
    exit(0);
    break;
  case ARROW_LEFT:
  case ARROW_RIGHT:
  case ARROW_UP:
  case ARROW_DOWN:
    editorMoveCursor(c);
    break;

  case PAGE_UP:
  case PAGE_DOWN:
  {
    int times = E.screenrows;
    while (times--)
    {
      editorMoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
    }
  }
  break;

  case HOME_KEY:
    E.cx = 0;
    break;
  case END_KEY:
    E.cx = E.screencols - 1;
    break;
  }
}

void editorMoveCursor(const int key)
{
  erow *row = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];

  switch (key)
  {
  case ARROW_LEFT:
    if (E.cx != 0)
    {
      E.cx--;
    }
    else if (E.cy > 0)
    {
      E.cy--;
      E.cx = E.row[E.cy].size;
    }

    break;
  case ARROW_RIGHT:
    if (row && E.cx < row->size)
    {
      E.cx++;
    }
    else if (row && E.cx == row->size)
    {
      E.cy++;
      E.cx = 0;
    }

    break;
  case ARROW_UP:
    if (E.cy != 0)
    {
      E.cy--;
    }
    break;
  case ARROW_DOWN:
    if (E.cy < E.numrows)
    {
      E.cy++;
    }
    break;
  }

  row = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];
  int rowlen = row ? row->size : 0;
  if (E.cx > rowlen)
  {
    E.cx = rowlen;
  }
}

void editorOpen(const char *filename)
{
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
    die("fopen");
  }

  char *line = NULL;
  ssize_t linelen;
  size_t linecap = 0;
  while ((linelen = getline(&line, &linecap, fp)) != -1) // at and getline returns -1.
  {
    if (linelen != -1)
    {
      while (linelen > 0 && (line[linelen - 1] == '\n' || line[linelen - 1] == '\r'))
      {
        linelen--;
      }
      editorAppendRow(line, linelen);
    }
  }

  free(line);
  fclose(fp);
}
