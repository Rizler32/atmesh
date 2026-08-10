#ifndef ATMESH_APP_FILE_DIALOG_H_
#define ATMESH_APP_FILE_DIALOG_H_

#include <stdbool.h>

int open_filechooser(char *out_path, int size, bool save_mode, const char* filter);

#endif // ATMESH_APP_FILE_DIALOG_H_
