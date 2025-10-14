#include "search.h"
#include <stdlib.h>
#include <string.h>

#include "../data.h"
#include "input.h"
#include "output.h"

void editorFind()
{
  char *query = editorPrompt("Search: %s (ESC to cancle)");
  if (query == ((void *)0))
    return;

  int i;
  for (i = 0; i < E.numrows; i++)
  {
    erow *row = &E.row[i];
    char *match = strstr(row->render, query);

    if (match != ((void *)0))
    {
      E.cy = i;
      E.cx = editorRowRxToCx(row, match - row->render);
      E.rowoff = E.numrows;
      break;
    }
  }

  free(query);
}
