#include "data.h"
#include "init.h"
#include "io/input.h"
#include "io/output.h"
#include "terminal/terminal.h"

editorConfig E = {0};

int main(int argc, char **argv)
{
  enableRawMode();
  initEditor();
  if (argc >= 2)
  {
    editorOpen(argv[1]);
  }

  while (1)
  {
    editorRefreshScreen();
    editorProcessKeypress();
  }
  return 0;
}
