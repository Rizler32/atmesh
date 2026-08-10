#ifdef _WIN32

#include "atmesh-app/file_dialog.h"
#include <windows.h>
#include <commdlg.h>

int open_filechooser(char *out_path, int size, bool save_mode, const char* filter) {
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    out_path[0] = '\0';

    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = out_path;
    ofn.nMaxFile = size;
    ofn.lpstrFilter = filter;
    ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST;

    return save_mode ? GetSaveFileName(&ofn)
                     : GetOpenFileName(&ofn);
}

#endif // _WIN32
