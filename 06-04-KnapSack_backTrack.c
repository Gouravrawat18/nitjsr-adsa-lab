#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsackBacktrack(int W, int wt[], int val[], int n, int i) {
    if (i == n || W == 0)
        return 0;
    if (wt[i] > W)
        return knapsackBacktrack(W, wt, val, n, i + 1);
    else {
        int include = val[i] + knapsackBacktrack(W - wt[i], wt, val, n, i + 1);
        int exclude = knapsackBacktrack(W, wt, val, n, i + 1);
        return max(include, exclude);
    }
}

int main() {
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);
    printf("Maximum value: %d\n", knapsackBacktrack(W, wt, val, n, 0));
    return 0;
}
