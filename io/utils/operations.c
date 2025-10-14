#include "operations.h"

#include "../../defines.h"
#include <string.h>

void editorAppendRow(const char *s, size_t size)
{
  E.row = realloc(E.row, sizeof(erow) * (E.numrows + 1));

  int at = E.numrows;
  E.row[at].size = size;
  E.row[at].chars = malloc(size + 1);
  memcpy(E.row[at].chars, s, size);
  E.row[at].chars[size] = '\0';

  E.row[at].rsize = 0;
  E.row[at].render = NULL;
  editorUpdateRow(&E.row[at]);

  E.numrows++;
  E.dirty++;
}

void editorInsertRow(int at, const char *s, size_t size)
{
  if (at < 0 || at > E.numrows)
    return;

  E.row = realloc(E.row, sizeof(erow) * (E.numrows + 1));
  memmove(&E.row[at + 1], &E.row[at], sizeof(erow) * (E.numrows - at));

  E.row[at].size = size;
  E.row[at].chars = malloc(size + 1);
  memcpy(E.row[at].chars, s, size);
  E.row[at].chars[size] = '\0';

  E.row[at].rsize = 0;
  E.row[at].render = NULL;
  editorUpdateRow(&E.row[at]);

  E.numrows++;
  E.dirty++;
}

void editorUpdateRow(erow *row)
{
  int tabs = 0;
  int j;
  // count the number of tabs in the row.
  for (j = 0; j < row->size; j++)
  {
    if (row->chars[j] == '\t')
    {
      tabs++;
    }
  }

  free(row->render);
  row->render = malloc(row->size + tabs * (EDITOR_TAB_STOP - 1) + 1);

  int idx = 0;
  for (j = 0; j < row->size; j++)
  {
    // render the tab.
    if (row->chars[j] == '\t')
    {
      row->render[idx++] = ' ';
      while (idx % EDITOR_TAB_STOP != 0)
      {
        row->render[idx++] = ' ';
      }
    }
    else
    {
      row->render[idx++] = row->chars[j];
    }
  }
  row->render[idx] = '\0';
  row->rsize = idx;
}
