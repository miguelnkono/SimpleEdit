//
// Created by gost on 9/10/25.
//

#ifndef KILO_TERMINAL_H
#define KILO_TERMINAL_H

#include "../data.h"

/**
 * If an error occurred we kill the program.
 *
 * @param msg the message of the error to print to the console.
 */
void die(const char *msg);

/**
 * To manipulate terminal attribute:
 *	1) reads the attributes using the 'tcgetattr()' function and storing those one in a struct. That struct is a termios struct.
 *	2) modify the attributes by hand.
 *	3) reset the attribute back to the terminal using the 'tcsetattr()' function.
 */
void enableRawMode();

/**
 * disable the raw mode when the user exit our program.
 * We do by resetting the terminal to its original state.
 */
void disableRawMode();

/**
 * This function wait until it read a character and return it to be process
 * by the program.
 *
 * read keypresses from the user.
 * STDIN_FILENO represent the standard input.
 * here we are reading one byte from the standard input into the c char variable until there is no more to read.
 * when there is no more to read the read() function will return 0 instead of the number of byte read.
 *
 * @return return the character read from the terminal.
 */
int editorReadKey();

/**
 * This function calculates the size of the terminal using the ioctl() function provide
 * by the operating system.
 *
 * @param rows a reference of the number of rows.
 * @param cols a reference of the number of columns.
 * @return return the size of the terminal.
 */
int getWindowSize(int *rows, int *cols);

/**
 * This function calculate the width and the height of the terminal in case ioctl() function
 * fails to do so.
 *
 * @param rows the number of rows of the terminal.
 * @param cols the number of column of the terminal.
 * @return return whether the function success or not.
 */
int getCursorPosition(int *rows, int *cols);

#endif //KILO_TERMINAL_H