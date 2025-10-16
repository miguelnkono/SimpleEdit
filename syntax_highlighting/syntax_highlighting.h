//
// Created by Gost on 14/10/25
//

#ifndef SYNTAX_HIGHLIGHTING_H
#define SYNTAX_HIGHLIGHTING_H

#include "../data.h"

/**
 * Function to highlight each character of a row.
 * @param row which is the row of text in the editor.
 * */
void editorUpdateSyntax(erow *row);

/**
 * Function to map the value in hl array of a row to actual ANSI color code.
 * @param hl which is the color.
 * */
int editorSyntaxToColor(int hl);

/**
 * Function to check if the current character is a separator character.
 * A separator character in our text editor is a character that is part of one of this character:
 *   - space
 *   - '\0'
 *   - ,.[](){}+-/%~<>;
 *
 * @param ch which is the character to check agains.
 * @return [int] will return 1 indicating that the character is a separator otherwise it will return an other digit.
 **/
int is_separator(int ch);

/**
 * Function to select the type of file we opening so that we can properly highlight it.
 * */
void editorSelectSyntaxHighlight();

#endif // SYNTAX_HIGHLIGHTING_H
