//
// Created by gost on 14/10/2025
//

#ifndef DELETIONS_H
#define DELETIONS_H

#include "../../data.h"

/**
 * Function to delete a single character in a row of characters.
 *
 * @param row the row of characters.
 * @param at  the position where to delete.
 */
void editorRowDelChar(erow *row, int at);

/**
 * Function to delete an entire row.
 *
 * @param at the position of the row we want to delete.
 */
void editorDelRow(int at);

/**
 * Function to free the memory owned by the row deleted.
 *
 * @param row the row we want to free the space.
 */
void editorFreeRow(erow *row);

#endif // DELECTIONS_H
