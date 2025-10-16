//
// Created by gost on 9/10/25.
//

#ifndef KILO_DEFINES_H
#define KILO_DEFINES_H

#define EDITOR_VERSION "0.0.1"
#define EDITOR_TAB_STOP 4  // usually it is 8.
#define EDITOR_QUIT_TIME 3 // the number of times the user should press the ctrl-q to quit the editor in case of unsaved file.

#define HL_HIGHLIGHT_NUMBER (1 << 0)

/**
 * It generates the control character corresponding to a given key character.
 * @param K the character in the alphabet table
 */
#define CTRL_KEY(K) ((K)&0x1f)

/**
 * Escape sequence.
 */
#define ESCAPE_SEQUENCE '\x1b'
#define ESCAPE_SEQUENCE_SIZE 1

/**
 * Cursor defines.
 */
#define CURSOR_BOTTOM_RIGHT "\x1b[999C\x1b[999B"
#define CURSOR_BOTTOM_RIGHT_SIZE 12
#define CURSOR_BOTTOM "\x1b[999B"
#define CURSOR_RIGHT "\x1b[999C"
#define CURSOR_BEGIN "\x1b[1;1H"
#define CURSOR_BEGIN_SIZE 6
#define CURSOR_POSITION "\x1b[6n"
#define CURSOR_POSITION_SIZE 4
#define CURSOR_HIDE "\x1b[?25l"
#define CURSOR_HIDE_SIZE 6
#define CURSOR_SHOW "\x1b[?25h"
#define CURSOR_SHOW_SIZE 6
#define CURSOR_SET_POSITION "\x1b[%d;%dH"

/**
 * Clear the screen.
 */
#define SCREEN_CLEAR "\x1b[2J"
#define SCREEN_CLEAR_SIZE 4
#define SCREEN_CLEAR_LINE "\x1b[K"
#define SCREEN_CLEAR_LINE_SIZE 3
#define SCREEN_NEW_LINE "\r\n"
#define SCREEN_NEW_LINE_SIZE 2
#define SCREEN_TILDE "~"
#define SCREEN_TILDE_SIZE 1
#define SCREEN_NEW_LINE_TILDE "~\r\n"
#define SCREEN_NEW_LINE_TILDE_SIZE 3

/**
 * Inverted colors.
 */
#define COLOR_INVERTED_COLOR "\x1b[7m"
#define COLOR_INVERTED_COLOR_SIZE 4
#define COLOR_NORMAL "\x1b[m"
#define COLOR_NORMAL_SIZE 3
#define COLOR_BOLD "\x1b[1m"
#define COLOR_BOLD_SIZE 4
#define COLOR_UNDERSCORE "\x1b[4m"
#define COLOR_UNDERSCORE_SIZE 4
#define COLOR_RED_COLOR "\x1b[31m"
#define COLOR_RED_COLOR_SIZE 5
#define COLOR_NORMAL_COLOR "\x1b[39m"
#define COLOR_NORMAL_COLOR_SIZE 5

#endif // KILO_DEFINES_H
