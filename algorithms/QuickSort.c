#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quick_sort(int array[], int left, int right);
int partition(int array[], int left, int right);
void shuffle(int array[], int n);

int main(void) {
    int sizes[] = {10, 100, 1000, 10000};
    int count = sizeof(sizes) / sizeof(sizes[0]);
    int i;

    srand((unsigned int)time(NULL));

    printf("QuickSort\n");
    printf("Size\tTime\n");

    for (i = 0; i < count; i++) {
        int n = sizes[i];
        int *array = (int *)malloc(n * sizeof(int));
        clock_t start, end;
        double elapsed_time;

        shuffle(array, n);
        start = clock();
        quick_sort(array, 0, n - 1);
        end = clock();
        elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%d\t%f\n", n, elapsed_time);
        free(array);
    }

    printf("QuickSort O(n log n)\n");
    return 0;
}

void quick_sort(int array[], int left, int right) {
    int pivot_index;

    if (left < right) {
        pivot_index = partition(array, left, right);
        quick_sort(array, left, pivot_index - 1);
        quick_sort(array, pivot_index + 1, right);
    }
}

int partition(int array[], int left, int right) {
    int pivot = array[right];
    int i = left - 1;
    int j;
    int temp;

    for (j = left; j < right; j++) {
        if (array[j] < pivot) {
            i++;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    temp = array[i + 1];
    array[i + 1] = array[right];
    array[right] = temp;

    return i + 1;
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
