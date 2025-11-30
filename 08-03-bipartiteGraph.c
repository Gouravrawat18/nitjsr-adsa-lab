#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int v;
    struct Node *next;
} Node;

void add_edge(Node **adj, int u, int v) {
    Node *p = malloc(sizeof(Node));
    p->v = v; p->next = adj[u]; adj[u] = p;
}

int is_bipartite(Node **adj, int n) {
    int *color = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) color[i] = -1;

    int *queue = malloc(n * sizeof(int));
    for (int src = 0; src < n; ++src) {
        if (color[src] != -1) continue;
        color[src] = 0;
        int front = 0, back = 0;
        queue[back++] = src;
        while (front < back) {
            int u = queue[front++];
            for (Node *p = adj[u]; p; p = p->next) {
                int v = p->v;
                if (u == v) { free(color); free(queue); return 0; } // self-loop
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    queue[back++] = v;
                } else if (color[v] == color[u]) {
                    free(color); free(queue);
                    return 0;
                }
            }
        }
    }
    free(color); free(queue);
    return 1;
}

int main(void) {
    int n, e;
    if (scanf("%d %d", &n, &e) != 2) return 0;
    
    Node **adj = calloc(n, sizeof(Node*));
    for (int i = 0; i < e; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < 1 || u > n || v < 1 || v > n) continue;
        add_edge(adj, u-1, v-1);
        add_edge(adj, v-1, u-1);
    }

    if (is_bipartite(adj, n)) printf("Graph is bipartite\n");
    else printf("Graph is NOT bipartite\n");

    
    for (int i = 0; i < n; ++i) {
        Node *p = adj[i];
        while (p) { Node *t = p; p = p->next; free(t); }
    }
    free(adj);
    return 0;
}
