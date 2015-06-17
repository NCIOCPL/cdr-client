/*
 * $Id$
 *
 * Launches script which copies the CDR client files to the current
 * user's application data area of the file system and puts a shortcut
 * on the desktop.  A string identifying the full path of the location
 * of the files to be copied is passed on the command line used to
 * launch the script.  This eliminates the necessity to run the script
 * from a command console in which the current working directory has
 * been set to the source directory for the files to be copied.  The
 * script will take care of enclosing the path passed on the command
 * line in quotes, in case the path contains spaces (as it likely will).
 * This is why the path to the script itself is enclosed in quotes
 * on the command line, but the rest of the command line showing the
 * location of the files to be copied, is not enclosed in quotes here.
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
    char source[MAX_PATH];
    char dest[MAX_PATH];
    DWORD n = GetModuleFileName(NULL, path, sizeof path);
    _splitpath(path, drive, dir, name, ext);
    sprintf(source, "%s%sxmetal90.exe", drive, dir);
    printf("%s\n", source);
    //sprintf(files, "%s%sFiles", drive, dir);
    //sprintf(script, "\"%s\\setup.cmd\" %s", files, files);
    //system(script);
    return 0;
}
