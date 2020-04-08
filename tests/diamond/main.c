#include <stdio.h>
#include <stdbool.h>
#include "diamond.h"

int main() {
    double a, b, c;
    a = 8.0;
    b = 6.0;
    diamond(&a, &b, &c);
    printf("Output: %f\n", c);
    return 1;
}
