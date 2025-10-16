#include "syntax_highlighting.h"

#include "../data.h"
#include "../defines.h"
#include "../types/file_type.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void editorUpdateSyntax(erow *row)
{
  row->hl = (unsigned char *)realloc(row->hl, row->rsize);
  memset(row->hl, HL_NORMAL, row->rsize);

  // if there is no syntax highlighting set for the current file.
  if (E.syntax == ((struct editorSyntax *)0))
    return;

  int prev_sep = 1;

  int i = 0;
  while (i < row->rsize)
  {
    char c = row->render[i];
    unsigned char prev_hl = (i > 0) ? row->hl[i - 1] : HL_NORMAL;

    if (E.syntax->flags & HL_HIGHLIGHT_NUMBER)
    {
      if (
          (isdigit(c) &&
           (prev_sep || prev_hl == HL_NUMBER)) ||
          (c == '.' && prev_hl == HL_NUMBER))
      {
        // if the current character is a number.
        row->hl[i] = HL_NUMBER;
        i++;          // consume the character.
        prev_sep = 0; // we are in the middle of an highlighting.
        continue;
      }
    }

    prev_sep = is_separator(c);
    i++;
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

int is_separator(int ch)
{
  return isspace(ch) || ch == '\0' || strchr(",.()+-/*=~%<>[];", ch) != ((const char *)0);
}

void editorSelectSyntaxHighlight()
{
  E.syntax = ((struct editorSyntax *)0);
  if (E.filename == ((const char *)0))
    return;

  // get the extension of the file.
  const char *ext = strrchr(E.filename, '.');

  // get the file type
  for (unsigned int j = 0; j < HLDB_ENTRIES; j++)
  {
    const struct editorSyntax *s = &HLDB[j];
    unsigned int i = 0;
    while (s->filematch[i])
    {
      // take only the extensions and left out the NULL keyword.
      int is_ext = (s->filematch[i][0] == '.');
      if ((is_ext && ext && strcmp(ext, s->filematch[i])) ||
          (!is_ext && strstr(E.filename, s->filematch[i])))
      {
        E.syntax = s;

        int filerow;
        for (filerow = 0; filerow < E.numrows; filerow++)
        {
          editorUpdateSyntax(&E.row[filerow]);
        }

        return;
      }

      i++;
    }
  }
}
