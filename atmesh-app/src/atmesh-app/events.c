#include "events.h"
#include "atmesh-app/file_dialog.h"
#include <atmesh/log.h>

#ifdef _WIN32
#include <windows.h>
#define PATH_SIZE MAX_PATH
#else
#error "not implemented platform"
#endif

void on_file_open() {
    char path[PATH_SIZE];

    if (open_filechooser(path, PATH_SIZE, false)) {
        ATMESH_DEBUG("File open: %s", path);
        // TODO load file here
    } else {
        ATMESH_DEBUG("Open cancelled");
    }
}

void on_file_save() {
    char path[PATH_SIZE];

    if (open_filechooser(path, PATH_SIZE, true)) {
        ATMESH_DEBUG("Save file: %s", path);
        // TODO save file here
    } else {
        ATMESH_DEBUG("Save cancelled");
    }
}
