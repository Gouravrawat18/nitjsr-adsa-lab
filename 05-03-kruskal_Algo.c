#include <stdio.h>
#include <stdlib.h>

#define V 9
#define E 14

typedef struct {
    int u, v, weight;
} Edge;

Edge edges[E];

int parent[V], rank[V];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void Union(int x, int y) {
    int xroot = find(x);
    int yroot = find(y);
    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void kruskal() {
    Edge result[V - 1];
    int e = 0, i = 0;
    for (int v = 0; v < V; v++) {
        parent[v] = v;
        rank[v] = 0;
    }

    qsort(edges, E, sizeof(edges[0]), compare);

    while (e < V - 1 && i < E) {
        Edge next_edge = edges[i++];
        int x = find(next_edge.u);
        int y = find(next_edge.v);

        if (x != y) {
            result[e++] = next_edge;
            Union(x, y);
        }
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    for (int j = 0; j < e; j++) {
        printf("Edge: %d - %d, Weight: %d\n", result[j].u, result[j].v, result[j].weight);
    }
}

int main() {
    printf("Enter %d edges (format: u v weight) where vertices are 0 to %d:\n", E, V-1);
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
        if (edges[i].u < 0 || edges[i].u >= V || edges[i].v < 0 || edges[i].v >= V) {
            printf("Invalid vertex entered. Please enter vertices between 0 and %d.\n", V-1);
            i--;
        }
    }

    kruskal();

    return 0;
}
