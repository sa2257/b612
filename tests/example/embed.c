#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdbool.h>

int call_simulator(char *module, char *function, int *inputs, int *outputs, bool *ready, bool *check, int ticks, int size) {
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pRet, *pValue;
    PyObject *pLin, *pLout, *pLrdy, *pLchk;
    PyObject *pVin, *pVout, *pVrdy, *pVchk;
    int i;

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
            pArgs = PyTuple_New(6);

			PyObject *l_in  = PyList_New(size);
			PyObject *l_out = PyList_New(size);
			PyObject *l_rdy = PyList_New(size);
			PyObject *l_chk = PyList_New(size);
			/* l_* are list objecks */

            for(i=0; i < size; i++){
			    pVin  = PyLong_FromLong(inputs[i]);
			    pVout = PyLong_FromLong(outputs[i]);
			    pVrdy = PyLong_FromLong(ready[i]);
			    pVchk = PyLong_FromLong(check[i]);
                if (!pVin || !pVout || !pVrdy || !pVchk) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
			    PyList_SetItem(l_in , i, pVin );
			    PyList_SetItem(l_out, i, pVout);
			    PyList_SetItem(l_rdy, i, pVrdy);
			    PyList_SetItem(l_chk, i, pVchk);
			}
            /* pV*s take each value of lists and make Py Lists */
			
			pLin  = Py_BuildValue("(O)", l_in );
            PyTuple_SetItem(pArgs, 0, pLin );
			pLout = Py_BuildValue("(O)", l_out);
            PyTuple_SetItem(pArgs, 1, pLout);
			pLrdy = Py_BuildValue("(O)", l_rdy);
            PyTuple_SetItem(pArgs, 2, pLrdy);
			pLchk = Py_BuildValue("(O)", l_chk);
            PyTuple_SetItem(pArgs, 3, pLchk);
            pValue = PyLong_FromLong(ticks);
            if (!pValue) {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                fprintf(stderr, "Cannot convert argument\n");
                return 1;
            }
            PyTuple_SetItem(pArgs, 4, pValue);
            pValue = PyLong_FromLong(size);
            if (!pValue) {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                fprintf(stderr, "Cannot convert argument\n");
                return 1;
            }
            PyTuple_SetItem(pArgs, 5, pValue);
            /* pArgs is the argument list */

			pRet = PyObject_CallObject(pFunc, pArgs);
            /* pRet is the return value from function call */

            Py_DECREF(pArgs);
            if (pRet != NULL) {
                for(i=0; i < size; i++){
                    pValue = PyList_GetItem(pRet, i);
                    outputs[i] = PyLong_AsLong(pValue);
                    Py_DECREF(pValue);
                }
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

    printf("Result is: ");
    for(i=0; i < size; i++){
        printf("%d, ", outputs[i]);
    }
    printf("\n");
    return 0;
}

void rtlib(int size) {
    char *module = "sim_lib";
    char *function = "simulate";
    int ticks = 5;
    int inputs[2] = {4, 6};
    int outputs[2] = {6, 14};
    bool ready[2] = {true, true};
    bool check[2] = {true, true};
    call_simulator(module, function, inputs, outputs, ready, check, ticks, size);
}
