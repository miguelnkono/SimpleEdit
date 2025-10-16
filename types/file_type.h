//
// Created by GOST on 15/10/25.
//

#ifndef FILE_TYPE_H
#define FILE_TYPE_H

#include "../data.h"
#include "../defines.h"

// file information about the C language.
const char *C_HL_extensions[] = {".c", ".h", ".cpp", NULL};

// the file syntax highlighting global array
const struct editorSyntax HLDB[] = {
    {.filetype = "c",
     .filematch = C_HL_extensions,
     .flags = HL_HIGHLIGHT_NUMBER},
};

#define HLDB_ENTRIES (sizeof(HLDB) / sizeof(HLDB[0]))

#endif // FILE_TYPE_H
