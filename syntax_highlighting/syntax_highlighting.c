#include "syntax_highlighting.h"

#include "../data.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void editorUpdateSyntax(erow *row)
{
  row->hl = (unsigned char *)realloc(row->hl, row->rsize);
  memset(row->hl, HL_NORMAL, row->rsize);

  int i;
  for (i = 0; i < row->rsize; i++)
  {
    if (isdigit(row->render[i]))
    {
      row->hl[i] = HL_NUMBER;
    }
  }
}

int editorSyntaxToColor(int hl)
{
  switch (hl)
  {
  case HL_NUMBER:
    return 31; // red color code.
  case HL_MATCH:
    return 34; // blue color code.
  default:
    return 37; // normal color code.
  }
}
