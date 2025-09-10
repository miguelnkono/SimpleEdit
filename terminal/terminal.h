//
// Created by gost on 9/10/25.
//

#ifndef KILO_TERMINAL_H
#define KILO_TERMINAL_H

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

#endif //KILO_TERMINAL_H