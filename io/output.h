//
// Created by gost on 9/10/25.
//

#ifndef KILO_OUTPUT_H
#define KILO_OUTPUT_H

// #include "../data.h"
#include "../types/string_buf.h"

/**
 * this function clear the entire screen.
 */
void editorRefreshScreen();

/**
 * Draw tildes at the beginning of each rows in the text editor.
 */
void editorDrawRows(abuf *ab);

/**
 * Function to make the window scroll when the cursor goes beyond the visible window.
 */
void editorScroll();

/**
 * Function to display the status bar of the editor.
 */
void editorDrawStatusBar(abuf *ab);

/**
 * Function to set the message that will be display below the status bar.
 */
void editorSetStatusMessage(const char *fmt, ...);

#endif // KILO_OUTPUT_H
