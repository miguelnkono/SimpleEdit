#include "search.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../data.h"
#include "../defines.h"
#include "input.h"
#include "output.h"

void editorFindCallback(char *query, int key)
{
  static int last_match = -1;
  static int direction = 1;

  if (key == '\r' || key == ESCAPE_SEQUENCE)
  {
    last_match = -1;
    direction = 1;
    return;
  }
  else if (key == ARROW_RIGHT || key == ARROW_DOWN)
  {
    direction = 1;
  }
  else if (key == ARROW_UP || key == ARROW_LEFT)
  {
    direction = -1;
  }
  else
  {
    last_match = -1;
    direction = 1;
  }

  if (last_match == -1)
    direction = 1;
  int current_match = last_match;
  int i;
  for (i = 0; i < E.numrows; i++)
  {
    current_match += direction;
    if (current_match == -1)
      current_match = E.numrows - 1;
    else if (current_match == E.numrows)
      current_match = 0;

    erow *row = &E.row[current_match];
    char *match = strstr(row->render, query);

    if (match != ((void *)0))
    {
      last_match = current_match;
      E.cy = current_match;
      E.cx = editorRowRxToCx(row, match - row->render);
      E.rowoff = E.numrows;
      break;
    }
  }
}

void editorFind()
{
  int save_cx = E.cx;
  int save_cy = E.cy;
  int save_coloff = E.coloff;
  int save_rowoff = E.rowoff;

  char *query = editorPrompt("Search: %s (Use ESC/Arrow/Enter)", editorFindCallback);
  if (query == ((void *)0))
    return;

  if (query)
    free(query);
  else
  {
    E.cx = save_cx;
    E.cy = save_cy;
    E.coloff = save_coloff;
    E.rowoff = save_rowoff;
  }
}
