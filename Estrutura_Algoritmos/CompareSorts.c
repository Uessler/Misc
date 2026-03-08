//Nota do autor:
//Este algoritmo (CompareSort.c) foi gerado por i.a (GPT-5.4)
//e não se propoe a ser avalidado como um trabalho academico,
//apenas teste de comparação entre os outros algoritmos apersentados.
//Compara a media de 100 execuções de cada algoritmo.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int array[], int n);
void quick_sort(int array[], int left, int right);
int partition(int array[], int left, int right);
void merge_sort(int array[], int left, int right);
void merge(int array[], int left, int middle, int right);
void shuffle(int array[], int n);
void copy_array(int source[], int target[], int n);

int main(void) {
    int sizes[] = {10, 100, 1000, 10000};
    int count = sizeof(sizes) / sizeof(sizes[0]);
    int rolls = 100;
    int i, j;

    srand((unsigned int)time(NULL));

    printf("+-------+------------+------------+------------+\n");
    printf("| Size  | Bubble     | Quick      | Merge      |\n");
    printf("+-------+------------+------------+------------+\n");

    for (i = 0; i < count; i++) {
        int n = sizes[i];
        double bubble_total = 0;
        double quick_total = 0;
        double merge_total = 0;

        for (j = 0; j < rolls; j++) {
            int *base = malloc(n * sizeof(int));
            int *bubble_array = malloc(n * sizeof(int));
            int *quick_array = malloc(n * sizeof(int));
            int *merge_array = malloc(n * sizeof(int));
            clock_t start, end;

            shuffle(base, n);
            copy_array(base, bubble_array, n);
            copy_array(base, quick_array, n);
            copy_array(base, merge_array, n);

            start = clock();
            bubble_sort(bubble_array, n);
            end = clock();
            bubble_total += (double)(end - start) / CLOCKS_PER_SEC;

            start = clock();
            quick_sort(quick_array, 0, n - 1);
            end = clock();
            quick_total += (double)(end - start) / CLOCKS_PER_SEC;

            start = clock();
            merge_sort(merge_array, 0, n - 1);
            end = clock();
            merge_total += (double)(end - start) / CLOCKS_PER_SEC;

            free(base);
            free(bubble_array);
            free(quick_array);
            free(merge_array);
        }

        printf("| %-5d | %-10f | %-10f | %-10f |\n",
            n,
            bubble_total / rolls,
            quick_total / rolls,
            merge_total / rolls);
    }

    printf("+-------+------------+------------+------------+\n");

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
    int *left_array = malloc(left_size * sizeof(int));
    int *right_array = malloc(right_size * sizeof(int));
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

void copy_array(int source[], int target[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        target[i] = source[i];
    }
}
