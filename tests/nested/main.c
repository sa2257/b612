#include <stdio.h>
#include <stdbool.h>
#include "nested.h"

int main() {
    double a, b, c;
    a = 8.0;
    nested(&a, &b, &c);
    printf("Output: %f, %f\n", b, c);
    return 1;
}
