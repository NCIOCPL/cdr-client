//----------------------------------------------------------------------
//
// $Id$
//
// Tool used for troubleshooting timestamp problems on the CDR client
// (for example, once a user tried to run the CDR client on a machine
// which used a broken Microsoft file system which was incapable of
// reporting time stamps with a granularity better than 2 seconds).
//
// Usage:
//    list each file for which a modification time stamp is to be
//    shown, on the command line, delimited by space; enclose file
//    names containing spaces in double quotes.  If an argument is
//    preceded by the "-s" flag, that argument is assumed to be a
//    Unix-style timestamp, given as the number of seconds since
//    the beginning of 1970.
//
//    Time stamps are displayed using the standard asctime format:
//
//                Www Mmm dd hh:mm:ss yyyy
//
//----------------------------------------------------------------------

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int main(int ac, char** av)
{
    for (size_t i = 1; i < ac; ++i) {
        if (strcmp(av[i], "-s") == 0) {
            time_t t = (time_t)atol(av[++i]);
            std::cout << t << ": " << ctime(&t);
            continue;
        }
        struct _stat s;
        int rc = _stat(av[i], &s);
        if (rc)
            std::cout << av[i] << ": failure with error code " << rc << '\n';
        else
            std::cout << av[i] << ": " << s.st_mtime <<
                " " << ctime(&s.st_mtime);
    }
    return 0;
}
