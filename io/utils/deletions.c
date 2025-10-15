#include "deletions.h"

#include "operations.h"
#include <stdlib.h>
#include <string.h>

void editorRowDelChar(erow *row, int at)
{
  if (at < 0 || at > row->size)
    return;

  // truncate the string.
  memmove(&row->chars[at], &row->chars[at + 1], row->size - at);
  row->size--;

  editorUpdateRow(row);
  E.dirty++;
}

void editorFreeRow(erow *row)
{
  free(row->chars);
  free(row->render);
  free(row->hl);
}

void editorDelRow(int at)
{
  if (at < 0 || at > E.numrows)
    return;

  editorFreeRow(&E.row[at]);
  memmove(&E.row[at], &E.row[at + 1], sizeof(erow) * (E.numrows - at - 1));
  E.numrows--;
  E.dirty++;
}
