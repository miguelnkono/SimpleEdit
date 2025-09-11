//
// Created by gost on 9/10/25.
//

#ifndef KILO_DATA_H
#define KILO_DATA_H

#include <termios.h>

/**
 * struct containing the editor configurations.
 */
typedef struct {
	// original terminal state.
	struct termios orig_termios;

	int screenrows;
	int screencols;

	// cursor position.
	int cx, cy;
}editorConfig;
extern editorConfig E;

// the directions keys.
enum  editorKey {
	ARROW_LEFT = 1000,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,

	DEL_KEY,

	HOME_KEY,
	END_KEY,

	PAGE_UP,
	PAGE_DOWN,
};

#endif //KILO_DATA_H
