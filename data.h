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
}editorConfig;
extern editorConfig E;

#endif //KILO_DATA_H
