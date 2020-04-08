#include "diamond.h"

void diamond( TYPE* in1, TYPE* in2, TYPE* out ){
    TYPE temp1, temp2, temp3, temp4, temp5;

    temp1 = *in1 + *in2;
    temp2 = *in1 - *in2;
    temp3 = temp1 / 5;
    temp4 = temp3 + 1;
    temp5 = temp4 * temp2;
    *out  = temp5;
}
