#define PY_SSIZE_T_CLEAN
#include <Python.h>

int call_simulator(char *module, char *function, int argN, int *inputs) {
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i; long result;

    Py_Initialize();
    /* These two lines allow looking up for modules in the current directory */
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");

    pName = PyUnicode_DecodeFSDefault(module);
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, function);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(argN);
            for (i = 0; i < argN; ++i) {
                pValue = PyLong_FromLong(inputs[i]);
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                result = PyLong_AsLong(pValue);
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", function);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", module);
        return 1;
    }

    if (Py_FinalizeEx() < 0) {
        return 120;
    }

    printf("Result from C is %ld\n", result);
    return 0;
}

void rtlib(int argN) {
    char *module = "multiply";
    char *function = "multiply";
    //int argN = 2;
    int inputs[2] = {4, 6};
    call_simulator(module, function, argN, inputs);
}

