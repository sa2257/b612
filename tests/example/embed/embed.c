#define PY_SSIZE_T_CLEAN
//#ifdef __APPLE__
//     #include <Python/Python.h>
//     #if MAC_OS_X_VERSION_MAX_ALLOWED < 101300
//         #include <Python/Python.h>
//     #else
//         #include <Python2.7/Python.h>
//     #endif
// #else
//     #include <python2.7/Python.h>
// #endif
#include <Python.h>

int main(int argc, char *argv[])
{
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program);  /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
                       "print('Today is', ctime(time()))\n");
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    PyMem_RawFree(program);
    return 0;
}
