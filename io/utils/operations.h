#ifndef KILO_OPERATIONS_H
#define KILO_OPERATIONS_H

#include <stdlib.h>

#include "../../data.h"

/**
 * This function appends a row to the editor at the end of the current text.
 * @param s The string to append.
 * @param size The size of the string.
 */
void editorAppendRow(const char *s, size_t size);

/**
 * This function updates a row's rendered version.
 * @param row The row to update.
 */
void editorUpdateRow(erow *row);

#endif // KILO_OPERATIONS_H
