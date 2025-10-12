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

#endif // INSERTIONS_H
