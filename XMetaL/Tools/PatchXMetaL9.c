/*
 * $Id$
 *
 * Installs and registers a patched version of XMetaL 9.0.
 *
 * Build command (using Microsoft C compiler):
 *    cl PatchXmetaL9.c
 */
#include <stdio.h>
#include <windows.h>

/**
 * Determine whether the caller's path represents a file.
 */
static BOOL file_exists(const char* path) {
    DWORD attrib = GetFileAttributes(path);
    if (attrib == INVALID_FILE_ATTRIBUTES)
        return FALSE;
    if (attrib & FILE_ATTRIBUTE_DIRECTORY)
        return FALSE;
    return TRUE;
}

/**
 * Find a path for backing up the existing xmetal90.exe that doesn't already
 * exist.
 */
static BOOL get_backup_path(char backup_path[], const char* prog86) {
    int counter = 1;
    while (counter <= 100) {
        sprintf(backup_path, "%s\\XMetaL 9.0\\Author\\xmetal90.exe-%d", prog86,
                counter);
        if (!file_exists(backup_path))
            return TRUE;
        ++counter;
    }
    printf("patch program has been run too many times\n");
    return FALSE;
}

int main() {
    char path[MAX_PATH];
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char name[_MAX_FNAME];
    char ext[_MAX_EXT];
    char source[MAX_PATH];
    char dest[MAX_PATH];
    char prog86[MAX_PATH];
    char reg_server[MAX_PATH + 25];
    DWORD n = GetModuleFileName(NULL, path, sizeof path);
    int rc = 0;
    _splitpath(path, drive, dir, name, ext);
    n = GetEnvironmentVariable("ProgramFiles(x86)", prog86, sizeof prog86);
    if (!n) {
        printf("ProgramFiles(x86) environment variable not set\n");
        rc = 1;
    }
    if (!rc) {
        sprintf(source, "%s\\XMetaL 9.0\\Author\\xmetal90.exe", prog86);
        if (file_exists(source)) {
            if (!get_backup_path(dest, prog86))
                rc = 1;
            else if (!MoveFile(source, dest)) {
                printf("unable to rename xmetal90.exe to %s\n", dest);
                rc = 1;
            }
        }
    }
    if (!rc) {
        strcpy(dest, source);
        sprintf(source, "%s%sxmetal90.exe", drive, dir);
        if (!CopyFile(source, dest, FALSE)) {
            printf("Unable to install patched XMetaL 9 to %s\n", dest);
            rc = 1;
        }
    }
    if (!rc) {
        sprintf(reg_server, "\"%s\" /RegServer", dest);
        /*printf("calling %s\n", reg_server);*/
        rc = system(reg_server);
        if (rc)
            printf("failure registering %s (error code %d)\n", dest, rc);
    }
    if (!rc)
        printf("patch successfully installed at:\n %s\n", dest);
    printf("press return to continue...");
    getchar();
    return rc;
}
