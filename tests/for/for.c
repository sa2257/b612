#include <stdio.h>

unsigned int forl(unsigned int x) {
    int out = 0;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            out++;
        }
    }
    return out;
}

int main() {
    printf("Output: %d\n", forl(5));
    return 1;
}
