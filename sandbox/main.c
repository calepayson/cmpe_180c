#include <stdio.h>
#include <stdlib.h>

int rand_range(int min, int max);

int main() {
    int num = 1;

    while (num != 0) {
        num = rand_range(1, 10);
        printf("Num = %i\n", num);
    }

    return 0;
}

int rand_range(int min, int max) { return min + rand() % (max - min + 1); }
