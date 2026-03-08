#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int array[], int n);
void shuffle(int array[], int n);

int main(void) {
    int sizes[] = {10, 100, 1000, 10000};
    int count = sizeof(sizes) / sizeof(sizes[0]);
    int i;

    srand((unsigned int)time(NULL));

    printf("BubbleSort\n");
    printf("Size\tTime\n");

    for (i = 0; i < count; i++) {
        int n = sizes[i];
        int *array = (int *)malloc(n * sizeof(int));
        clock_t start, end;
        double elapsed_time;

        shuffle(array, n);
        start = clock();
        bubble_sort(array, n);
        end = clock();
        elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%d\t%f\n", n, elapsed_time);
        free(array);
    }

    printf("BubbleSort O(n^2)\n");
    return 0;
}

void bubble_sort(int array[], int n) {
    int i, j, temp, swapped;

    for (i = 0; i < n - 1; i++) {
        swapped = 0;

        for (j = 0; j < n - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

void shuffle(int array[], int n) {
    int i, j, temp;

    for (i = 0; i < n; i++) {
        array[i] = i + 1;
    }

    for (i = n - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
