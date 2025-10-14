//
// Created by gost on 9/10/25.
//

#ifndef KILO_INPUT_H
#define KILO_INPUT_H

// #include "operations.h"

/**
 * wait for a key press and then handle it to a corresponding functionality in the program.
 */
void editorProcessKeypress();

/**
 * This function will alter the coordinates of the cursor on the screen.
 *
 * @param key the character type to move the cursor.
 */
void editorMoveCursor(int key);

/**
 * This function is load when the text editor start.
 * This will load the file content in the editor.
 *
 * @param filename which is the name of the file to read from.
 */
void editorOpen(const char *filename);

/**
 * Function to transform all the rows of characters into a single big string.
 */
char *editorRowsToString(int *buflen);

/**
 * Function to save the content into a file.
 */
void editorSave();

/**
 * Function to ask the user to enter the name of the file.
 *
 * @param  prompt  the prompt to display to the user.
 */
char *editorPrompt(const char *prompt);

#endif // KILO_INPUT_H
