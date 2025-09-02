#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void insertionSort(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(float arr[], int n) {
    float bucket[MAX][n];
    int count[MAX] = {0};
    for (int i = 0; i < n; i++) {
        int idx = arr[i] * MAX;
        bucket[idx][count[idx]++] = arr[i];
    }
    for (int i = 0; i < MAX; i++)
        if (count[i] > 0) insertionSort(bucket[i], count[i]);
    int k = 0;
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < count[i]; j++)
            arr[k++] = bucket[i][j];
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    float arr[n];
    printf("Enter %d elements (between 0 and 1): ", n);
    for (int i = 0; i < n; i++) scanf("%f", &arr[i]);
    bucketSort(arr, n);
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) printf("%f ", arr[i]);
    return 0;
}
