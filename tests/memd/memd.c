#include <stdio.h>

unsigned int access(unsigned int x, unsigned int y) {
    int Arr[10][10] = {0};
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            Arr[i][j] = i * 10 + j;
        }
    }

    return Arr[x][y];
}

int main() {
    printf("Output: %d\n", access(5, 5));
    return 1;
}
