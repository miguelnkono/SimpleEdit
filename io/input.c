//
// Created by gost on 9/10/25.
//

#include "editor_operations/edit.h"
#include "output.h"
#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include "input.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "../data.h"
#include "../defines.h"
#include "../terminal/terminal.h"
#include "utils/operations.h"

void editorProcessKeypress()
{
  static int quit_times = EDITOR_QUIT_TIME;

  const int c = editorReadKey(); // we read the character from the terminal.

  switch (c)
  {
  case '\r':
    // todo
    break;
  case CTRL_KEY('q'):
    if (E.dirty && quit_times > 0)
    {
      editorSetStatusMessage("WARNING!!! File has unsaved changes. "
                             "Press Ctrl-Q %d more times to quite.",
                             quit_times);
      quit_times--;
      return;
    }

    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[1;1H", 3);
    exit(0);
    break;

  case CTRL_KEY('s'):
    editorSave();
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
    if (c == PAGE_UP)
      E.cy = E.rowoff;
    else if (c == PAGE_DOWN)
    {
      E.cy = E.rowoff + E.screenrows - 1;
      if (E.cy > E.numrows)
        E.cy = E.numrows;
    }

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

  case BACKSPACE:
  case CTRL_KEY('h'):
  case DEL_KEY:
    // todo
    break;

  case END_KEY:
    // E.cx = E.screencols - 1;
    if (E.cy < E.numrows)
      E.cx = E.row[E.cy].size;
    break;

  case CTRL_KEY('l'):
  case '\x1b':
    break;

  default:
    editorInsertChar(c);
    break;
  }

  quit_times = EDITOR_QUIT_TIME;
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
  free(E.filename);
  E.filename = strdup(filename);

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
  E.dirty = 0;
}

char *editorRowsToString(int *buflen)
{
  int totallength = 0;
  for (int i = 0; i < E.numrows; i++)
    totallength += E.row[i].size + 1;
  *buflen = totallength;

  char *buf = malloc(totallength);
  char *p = buf;

  for (int i = 0; i < E.numrows; i++)
  {
    memcpy(p, E.row[i].chars, E.row[i].size);
    p += E.row[i].size; // here we do pointer arithmetic to properly repositionate the p pointer address to wait for the next character slice.
    *p = '\n';
    p++;
  }

  return buf;
}

void editorSave()
{
  if (E.filename == NULL)
    return;

  int len;
  char *content = editorRowsToString(&len);

  int fd = open(E.filename, O_RDWR | O_CREAT, 0644);
  if (fd != -1)
  {
    if (ftruncate(fd, len) != -1)
    {
      if (write(fd, content, len) == len)
      {
        close(fd);
        free(content);
        E.dirty = 0;
        editorSetStatusMessage("%d bytes written to disk", len);
        return;
      }
    }
    close(fd);
  }
  free(content);
  editorSetStatusMessage("Can't save. I/O error: %s", strerror(errno));
}
