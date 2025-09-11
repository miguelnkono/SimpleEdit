//
// Created by gost on 9/10/25.
//

#ifndef KILO_OUTPUT_H
#define KILO_OUTPUT_H

#include "../data.h"
#include "../types/string_buf.h"

/**
 * this function clear the entire screen.
 */
void editorRefreshScreen();

/**
 * Draw tildes at the beginning of each rows in the text editor.
 */
void editorDrawRows(abuf *ab);

#endif //KILO_OUTPUT_H