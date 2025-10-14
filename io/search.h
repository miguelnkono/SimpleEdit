//
// Created by gost on 14/10/25.
//

#ifndef SEARCH_H
#define SEARCH_H

/**
 * Function to find a match in the entire editor space.
 * Once found the cursor will be repositionated to the beggining of the match.
 */
void editorFind();

/**
 * Function to find a macth in the entire editor space for each key presses by the user.
 * */
void editorFindCallback(char *query, int key);

#endif // SEARCH_H
