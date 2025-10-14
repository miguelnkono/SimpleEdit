#include "insertions.h"
#include "operations.h"
#include <stdlib.h>
#include <string.h>

void editorRowInsertCharacter(erow *erow, int at, int c)
{
  if (at < 0 || at > erow->size)
    at = erow->size;

  erow->chars = realloc(erow->chars, erow->size + 2);
  memmove(&erow->chars[at + 1], &erow->chars[at], erow->size - at + 1);
  erow->size++;
  erow->chars[at] = c;
  editorUpdateRow(erow);
  E.dirty++;
}

void editorRowAppendString(erow *row, const char *s, int len)
{
  row->chars = (char *)realloc(row->chars, row->size + len + 1);
  memcpy(&row->chars[row->size], s, len);
  row->size += len;
  row->chars[row->size] = '\0';
  editorUpdateRow(row);
  E.dirty++;
}
