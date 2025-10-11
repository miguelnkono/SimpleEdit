//
// Created by gost on 9/11/25.
//

#ifndef KILO_STRING_BUF_H
#define KILO_STRING_BUF_H

/**
 * This is our string buffer type.
 * It will support only one operation: append.
 */
typedef struct
{
  char *buf;
  int len;
} abuf;

/**
 * Macro to initialize the buffer.
 */
#define ABUF_INIT  \
  {                \
    ((void *)0), 0 \
  }

/**
 * This function will append a string to the global buffer of string.
 *
 * @param ab the buffer pointer to append.
 * @param s the char sequence to append to the buffer pointer.
 * @param len the length of the char sequence we are appending to the pointer buffer.
 */
void abAppend(abuf *ab, const char *s, int len);

/**
 * This function will free the buffer of characters to release the memory.
 *
 * @param ab the buffer to free the memory.
 */
void abFree(abuf *ab);

#endif // KILO_STRING_BUF_H
