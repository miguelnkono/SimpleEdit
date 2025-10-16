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

/**
 * Function to check if the current character is a separator character.
 * A separator character in our text editor is a character that is part of one of this character:
 *   - space
 *   - '\0'
 *   - ,.[](){}+-/%~<>;
 **/
int is_separator(int ch);

/**
 * Function to select the type of file we opening so that we can properly highlight it.
 * */
void editorSelectSyntaxHighlight();

#endif // SYNTAX_HIGHLIGHTING_H
