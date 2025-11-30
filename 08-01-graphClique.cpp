#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX 20

int graph[MAX][MAX];
int n, e, m;

bool isClique(int vertices[], int size) {
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (graph[vertices[i]][vertices[j]] == 0)
                return false;
    return true;
}

bool findClique(int start, int vertices[], int size) {
    if (size == m)
        return isClique(vertices, size);

    for (int i = start; i < n; i++) {
        vertices[size] = i;
        if (findClique(i + 1, vertices, size + 1))
            return true;
    }
    return false;
}

int main() {
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);
    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    printf("Enter clique size (m): ");
    scanf("%d", &m);

    int vertices[MAX];
    clock_t start = clock();
    bool exists = findClique(0, vertices, 0);
    clock_t end = clock();

    if (exists)
        printf("Graph contains a clique of size %d.\n", m);
    else
        printf("Graph does NOT contain a clique of size %d.\n", m);

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution Time: %.6f seconds\n", time_taken);

    return 0;
}
