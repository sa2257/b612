#include <stdio.h>
#include <stdbool.h>

unsigned int branch(bool x) {
    if(x) 
        return 4;
    else
        return 5;
}

int main() {
    printf("Output: %d\n", branch(true));
    return 1;
}
