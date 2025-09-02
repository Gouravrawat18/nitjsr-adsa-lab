#include <stdio.h>

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0) return;
    int i = left, j = right;
    while (i <= j) {
        while (i <= j && ((arr[i] >> bit) & 1) == 0) i++;
        while (i <= j && ((arr[j] >> bit) & 1) == 1) j--;
        if (i < j) swap(&arr[i], &arr[j]);
    }
    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, j + 1, right, bit - 1);
}

int getMaxBit(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];
    int bit = 0;
    while (max > 0) { bit++; max >>= 1; }
    return bit - 1;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d non-negative integers: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    int maxBit = getMaxBit(arr, n);
    radixExchangeSort(arr, 0, n - 1, maxBit);
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    return 0;
}
