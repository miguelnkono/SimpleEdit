#include "edit.h"
#include "../../data.h"
#include "../utils/insertions.h"
#include "../utils/operations.h"

void editorInsertChar(int c)
{
  if (E.cy == E.numrows)
  {
    editorAppendRow("", 1);
  }
  editorRowInsertCharacter(&E.row[E.cy], E.cx, c);
  E.cx++;
}
