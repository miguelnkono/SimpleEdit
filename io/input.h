//
// Created by gost on 9/10/25.
//

#ifndef KILO_INPUT_H
#define KILO_INPUT_H

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

#endif //KILO_INPUT_H