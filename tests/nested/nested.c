#include "nested.h"

void nested( TYPE* in, TYPE* out1, TYPE* out2 ){
    TYPE temp1, temp2, temp3, temp4, temp5;

    temp1 = *in * 2;
    temp2 = *in * 5;
    temp3 = *in + 3;
    temp4 = *in - 1;
    temp5 = temp3 / temp4;
    *out1 = temp1 + temp2;
    *out2 = temp2 + temp5;
}
