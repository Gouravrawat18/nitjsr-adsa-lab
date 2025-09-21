#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int time = 0;
int graph[MAX][MAX];
int visited[MAX];
int discovery[MAX];
int finish[MAX];
int n;

void dfs_visit(int u) {
    visited[u] = 1;
    discovery[u] = ++time;

    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                printf("Tree Edge: %d -> %d\n", u, v);
                dfs_visit(v);
            } else if (discovery[v] < discovery[u] && finish[v] == 0) {
                printf("Back Edge: %d -> %d\n", u, v);
            } else if (discovery[u] < discovery[v]) {
                printf("Forward Edge: %d -> %d\n", u, v);
            } else {
                printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
    }

    finish[u] = ++time;
}

void dfs() {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        discovery[i] = 0;
        finish[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs_visit(i);
        }
    }
}

int main() {
    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);
    if (n > MAX || n <= 0) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    dfs();

    return 0;
}
