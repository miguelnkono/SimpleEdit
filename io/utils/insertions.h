//
// Created by gost on 12/10/2025.
// Author: NKONO NDEME Miguel.
//

#ifndef INSERTIONS_H
#define INSERTIONS_H

#include "../../data.h"

/**
 * Function to insert a single character into an erow.
 *
 * @param erow  the erow in which to insert.
 * @param at    the position into where to insert.
 * @param c     the character to insert.
 */
void editorRowInsertCharacter(erow *erow, int at, int c);

/**
 * Function to append a string to the end of a row.
 *
 * @param row which represent the row in which we want to append a string.
 * @param s   which represent the string we want to append.
 * @param len which represent the length of the string we want to append to the end of the string.
 */
void editorRowAppendString(erow *row, const char *s, int len);

#endif // INSERTIONS_H
