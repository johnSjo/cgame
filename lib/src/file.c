#include "file.h"

int Read_Config_File(char *file_path, char **lines)
{
  int i;
  char line[256];
  char far *string;
  int line_count = 0;
  FILE *file_ptr = fopen(file_path, "r");

  if (file_ptr == NULL)
  {
    printf("\nError opening file at: %s", file_path);
    return 1;
  }

  while (fgets(line, sizeof(line), file_ptr))
    line_count++;

  fseek(file_ptr, 0, SEEK_SET);

  for (i = 0; i < line_count; i++)
  {
    string = _fmalloc(sizeof(line));
    fgets(string, sizeof(line), file_ptr);
    lines[i] = string;
  }

  fclose(file_ptr);

  return 0;
}