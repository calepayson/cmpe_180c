#include <stdio.h>
#include <stdlib.h>

const int ARR_SIZE = 5;

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < ARR_SIZE; i++) {
        printf("%i, ", arr[i]);
    }

    printf("\n");

    return 0;
}
