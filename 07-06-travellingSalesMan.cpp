#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define INF 999999

int tsp(int **graph, int n, int pos, int visited, int **dp) {
    if (visited == (1 << n) - 1)
        return graph[pos][0];
    if (dp[pos][visited] != -1)
        return dp[pos][visited];
    int ans = INF;
    for (int city = 0; city < n; city++) {
        if ((visited & (1 << city)) == 0)
            ans = (ans < graph[pos][city] + tsp(graph, n, city, visited | (1 << city), dp))
                      ? ans
                      : graph[pos][city] + tsp(graph, n, city, visited | (1 << city), dp);
    }
    return dp[pos][visited] = ans;
}

int **generateGraph(int n) {
    int **graph = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        graph[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            graph[i][j] = (i == j) ? 0 : (rand() % 90 + 10);
    }
    return graph;
}

int **createDP(int n) {
    int size = 1 << n;
    int **dp = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dp[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) dp[i][j] = -1;
    }
    return dp;
}

void freeMemory(int **arr, int n) {
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
}

int main() {
    srand(time(NULL));
    int sizes[] = {10, 20, 40, 60, 100};
    printf("Problem Size\tExecution Time (seconds)\n");

    for (int s = 0; s < 5; s++) {
        int n = sizes[s];
        int **graph = generateGraph(n);
        int **dp = createDP(n);
        clock_t start = clock();
        if (n <= 12)
            tsp(graph, n, 0, 1, dp);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d\t\t%.6f\n", n, time_taken);
        freeMemory(graph, n);
        freeMemory(dp, n);
    }
    return 0;
}
