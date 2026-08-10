#include "atmesh-app/events.h"
#include "atmesh-app/file_dialog.h"

#include <atmesh/log.h>

#include <tinyobj_loader_c.h>
#include <stlfile.h>

#ifdef _WIN32
#include <windows.h>
#define PATH_SIZE MAX_PATH
#else
#error "not implemented platform" // TODO
#endif

#define FILE_OPEN_FILTER       \
    "3D Mesh\0*.obj;*.stl\0"   \
    "obj\0*.obj\0"             \
    "stl\0*.stl\0"

#define FILE_SAVE_FILTER       \
    "2D Flattening\0*.dxf\0"   \
    "dxf\0*.dxf\0"
    
void on_file_open() {
    char path[PATH_SIZE];

    if (open_filechooser(path, PATH_SIZE, false, FILE_OPEN_FILTER)) {
        ATMESH_DEBUG("File open: %s", path);
        // TODO load file
    } else {
        ATMESH_DEBUG("Open cancelled");
    }
}

void on_file_save() {
    char path[PATH_SIZE];

    if (open_filechooser(path, PATH_SIZE, true, FILE_SAVE_FILTER)) {
        ATMESH_DEBUG("Save file: %s", path);
        // TODO save file here
    } else {
        ATMESH_DEBUG("Save cancelled");
    }
}
