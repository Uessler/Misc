#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge_sort(int array[], int left, int right);
void merge(int array[], int left, int middle, int right);
void shuffle(int array[], int n);

int main(void) {
    int sizes[] = {10, 100, 1000, 10000};
    int count = sizeof(sizes) / sizeof(sizes[0]);
    int i;

    srand((unsigned int)time(NULL));

    printf("MergeSort\n");
    printf("Size\tTime\n");

    for (i = 0; i < count; i++) {
        int n = sizes[i];
        int *array = (int *)malloc(n * sizeof(int));
        clock_t start, end;
        double elapsed_time;

        shuffle(array, n);
        start = clock();
        merge_sort(array, 0, n - 1);
        end = clock();
        elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%d\t%f\n", n, elapsed_time);
        free(array);
    }

    printf("MergeSort O(n log n)\n");
    return 0;
}

void merge_sort(int array[], int left, int right) {
    int middle;

    if (left < right) {
        middle = left + (right - left) / 2;

        merge_sort(array, left, middle);
        merge_sort(array, middle + 1, right);
        merge(array, left, middle, right);
    }
}

void merge(int array[], int left, int middle, int right) {
    int left_size = middle - left + 1;
    int right_size = right - middle;
    int *left_array = (int *)malloc(left_size * sizeof(int));
    int *right_array = (int *)malloc(right_size * sizeof(int));
    int i, j, k;

    for (i = 0; i < left_size; i++) {
        left_array[i] = array[left + i];
    }

    for (j = 0; j < right_size; j++) {
        right_array[j] = array[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < left_size && j < right_size) {
        if (left_array[i] <= right_array[j]) {
            array[k] = left_array[i];
            i++;
        } else {
            array[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < left_size) {
        array[k] = left_array[i];
        i++;
        k++;
    }

    while (j < right_size) {
        array[k] = right_array[j];
        j++;
        k++;
    }

    free(left_array);
    free(right_array);
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
