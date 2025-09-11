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

#endif //KILO_INPUT_H