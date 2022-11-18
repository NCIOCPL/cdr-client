/**
 * Register 64-bit CDR DLL.
 *
 * This program can be run by an unpriviledged user, because the DLL
 * enables per-user registration, overriding the default of per-machine
 * registration. The --unregister (alias -u) option unregisters the DLL.
 *
 * Must be built as a 64-bit app.
 *
 * Usage: regcdrdll [--unregister|-u] [--verbose|-v] [DLLPATH]
 */

#include <iostream>
#include <string.h>
#include <windows.h>

#define USAGE "Usage: regcdrdll [--unregister|-u] [--verbose|-v] [DLLPATH]\n"

int main(int ac, char** av) {
    const char* path = "Cdr\\Cdr.dll";
    const char* func = "DllRegisterServer";
    bool verbose = false;
    for (int i = 1; i < ac; ++i) {
        if (!strcmp(av[i], "-h") || !strcmp(av[i], "--help")) {
            std::cout << USAGE;
            return EXIT_SUCCESS;
        }
        else if (!strcmp(av[i], "-u") || !strcmp(av[i], "--unregister"))
            func = "DllUnregisterServer";
        else if (!strcmp(av[i], "-v") || !strcmp(av[i], "--verbose"))
            verbose = true;
        else
            path = av[i];
    }
    if (verbose) std::cout << "Calling LoadLibrary() for " << path << "\n";
    HMODULE dll = LoadLibrary(path);
    if (verbose) std::cout << "Back from LoadLibrary()\n";
    if (!dll) {
        std::cerr << "Error loading " << path << ": " << GetLastError() << "\n";
        return EXIT_FAILURE;
    }
    if (verbose) std::cout << "Invoking " << func << "()\n";
    typedef HRESULT (_stdcall *DLLPROC)();
    DLLPROC proc = reinterpret_cast<DLLPROC>(GetProcAddress(dll, func));
    HRESULT hr = (*proc)();
    if (!SUCCEEDED(hr))
        std::cerr << func << " error: " << GetLastError() << "\n";
    else if (verbose) std::cout << func << " for " << path << " succeeded\n";
    FreeLibrary(dll);
    if (verbose) std::cout << path << " freed\n";
    return SUCCEEDED(hr) ? EXIT_SUCCESS : EXIT_FAILURE;
}
