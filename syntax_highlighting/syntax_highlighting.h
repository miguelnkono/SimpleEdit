//
// Created by Gost on 14/10/25
//

#ifndef SYNTAX_HIGHLIGHTING_H
#define SYNTAX_HIGHLIGHTING_H

#include "../data.h"

/**
 * Function to highlight each character of a row.
 * */
void editorUpdateSyntax(erow *row);

/**
 * Function to map the value in hl std::array of a row to actual ANSI color code.
 * */
int editorSyntaxToColor(int hl);

#endif // SYNTAX_HIGHLIGHTING_H
