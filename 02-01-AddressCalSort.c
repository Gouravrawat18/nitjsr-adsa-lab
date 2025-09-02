#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void addressCalculationSort(int arr[], int n) {
    int *bucket[MAX];
    int count[MAX] = {0};
    for (int i = 0; i < MAX; i++) bucket[i] = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int addr = arr[i] % MAX;
        bucket[addr][count[addr]++] = arr[i];
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < count[i] - 1; j++)
            for (int k = 0; k < count[i] - j - 1; k++)
                if (bucket[i][k] > bucket[i][k + 1]) {
                    int t = bucket[i][k];
                    bucket[i][k] = bucket[i][k + 1];
                    bucket[i][k + 1] = t;
                }
    }
    int idx = 0;
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < count[i]; j++)
            arr[idx++] = bucket[i][j];
    for (int i = 0; i < MAX; i++) free(bucket[i]);
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    addressCalculationSort(arr, n);
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    return 0;
}
