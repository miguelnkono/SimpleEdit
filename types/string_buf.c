//
// Created by gost on 9/11/25.
//

#include "string_buf.h"

#include <stdlib.h>
#include <string.h>

void abAppend(abuf *ab, const char *s, const int len)
{
  char *new_buf = realloc(ab->buf, ab->len + len);
  if (new_buf == NULL)
    return;

  memcpy(&new_buf[ab->len], s, len);
  ab->buf = new_buf;
  ab->len += len;
}

void abFree(abuf *ab)
{
  free(ab->buf);
}
