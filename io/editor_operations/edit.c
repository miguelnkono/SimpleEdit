#include "edit.h"
#include "../../data.h"
#include "../utils/deletions.h"
#include "../utils/insertions.h"
#include "../utils/operations.h"

void editorInsertChar(int c)
{
  if (E.cy == E.numrows)
  {
    editorInsertRow(E.numrows, "", 0);
  }
  editorRowInsertCharacter(&E.row[E.cy], E.cx, c);
  E.cx++;
}

void editorDelChar()
{
  if (E.cy == E.numrows)
    return;
  if (E.cx == 0 && E.cy == 0)
    return;

  // get the row where the cursor is on.
  erow *row = &E.row[E.cy];

  // if there is a character after the cursor.
  if (E.cx > 0)
  {
    editorRowDelChar(row, E.cx - 1);
    E.cx--;
  }
  else
  {
    E.cx = E.row[E.cy - 1].size;
    editorRowAppendString(&E.row[E.cy - 1], row->chars, row->size);
    editorDelRow(E.cy);
    E.cy--;
  }
}

void editorInsertNewLine()
{
  if (E.cx == 0)
  {
    editorInsertRow(E.cy, "", 0);
  }
  else
  {
    erow *row = &E.row[E.cy];
    editorInsertRow(E.cy + 1, &row->chars[E.cx], row->size - E.cx);
    row = &E.row[E.cy];
    row->size = E.cx;
    row->chars[row->size] = '\0';
    editorUpdateRow(row);
  }

  E.cy++;
  E.cx = 0;
}
