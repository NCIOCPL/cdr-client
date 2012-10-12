/*
 * $Id$
 *
 * Launches script which copies the CDR client files to the current
 * user's application data area of the file system and puts a shortcut
 * on the desktop.  A single command-line argument is passed to that
 * script identifying the full path of the location of the files
 * to be copied.  This eliminates the necessity to run the script
 * from a command console in which the current working directory has
 * been set to the source directory for the files to be copied.
 * This program is to be installed in the parent directory of the
 * location of those files.
 *
 * Build command (using Microsoft C compiler):
 *    cl InstallCdrClientFiles.c
 */
#include <stdio.h>
#include <windows.h>

int main() {
    char path[MAX_PATH];
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char name[_MAX_FNAME];
    char ext[_MAX_EXT];
    char files[MAX_PATH];
    char script[MAX_PATH * 2];
    DWORD n = GetModuleFileName(NULL, path, sizeof path);
    _splitpath(path, drive, dir, name, ext);
    sprintf(files, "%s%sFiles", drive, dir);
    sprintf(script, "\"%s\\setup.cmd\" %s", files, files);
    system(script);
    return 0;
}
