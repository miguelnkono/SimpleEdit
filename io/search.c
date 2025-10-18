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

  static int save_hl_line;
  static char *save_hl = NULL;

  if (save_hl)
  {
    // restore the previous color.
    memcpy(E.row[save_hl_line].hl, save_hl, E.row[save_hl_line].rsize);
    free(save_hl);
    save_hl = NULL;
  }

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
    // we circle the match here.
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

      save_hl_line = current_match;
      save_hl = (char *)malloc(row->rsize);
      memcpy(save_hl, row->hl, row->rsize);
      memset(&row->hl[match - row->render], HL_MATCH, strlen(query));
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
