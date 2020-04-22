#define PY_SSIZE_T_CLEAN
#include <Python.h>
  
int main(int argc, char *argv[])
{
    int counter; 
    printf("Program Name Is: %s",argv[0]); 
    if(argc==1) 
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name"); 
        printf("\n");
    if(argc>=2) 
    { 
        printf("\nNumber Of Arguments Passed: %d",argc); 
        printf("\n----Following Are The Command Line Arguments Passed----"); 
        for(counter=0;counter<argc;counter++) 
            printf("\nargv[%d]: %s",counter,argv[counter]); 
        printf("\n");
    }
 
    wchar_t *program = Py_DecodeLocale(argv[1], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[1]\n");
        exit(1);
    }
    printf("The program is %s\n", argv[1]);
    printf("At the start of the program!\n");
    Py_SetProgramName(program);  /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
                       "print('Today is', ctime(time()))\n");
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    PyMem_RawFree(program);
    printf("Done with the program!\n");
    return 0;
}
