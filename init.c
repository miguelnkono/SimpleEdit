//
// Created by gost on 9/10/25.
//

#include "init.h"

#include "data.h"
#include "terminal/terminal.h"

void initEditor()
{
  E.cx = 0;
  E.cy = 0;
  E.rx = 0;
  E.dirty = 0;
  E.numrows = 0;
  E.rowoff = 0;
  E.coloff = 0;
  E.row = ((void *)0); // this is the same thing as the NULL value. :)
  E.filename = ((void *)0);
  E.statussmg[0] = '\0';
  E.statussmg_time = 0;

  // get the window size (width and height) and leave one row off for the status bar.
  if (getWindowSize(&E.screenrows, &E.screencols) == -1)
  {
    die("GetWindowSize failed");
  }
  E.screenrows -= 2;
}
