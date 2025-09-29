#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100

struct Edge {
    int u, v, weight;
};

void BellmanFord(struct Edge edges[], int V, int E, int src) {
    int dist[V];
    
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    for (int i = 1; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t", i);
        if (dist[i] == INT_MAX) {
            printf("INF\n");
        } else {
            printf("%d\n", dist[i]);
        }
    }
}

int main() {
    int V, E, u, v, weight;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    struct Edge edges[E];

    for (int i = 0; i < E; i++) {
        printf("Enter edge %d (u v weight): ", i+1);
        scanf("%d %d %d", &u, &v, &weight);
        edges[i].u = u;
        edges[i].v = v;
        edges[i].weight = weight;
    }

    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);

    BellmanFord(edges, V, E, source);

    return 0;
}
