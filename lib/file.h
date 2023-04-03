#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <malloc.h>
#include "typedef.h"

#define MAX_NUMBER_CONFIG_LINES 256

// ENUMS

// STRUCTS

// PROTOTYPES

// INTERNALS
int Read_Config_File(char *file_path, char **lines);

#endif