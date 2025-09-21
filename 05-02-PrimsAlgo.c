// #include <stdio.h>
// #include <limits.h>

// #define MAX_VERTICES 100

// int minKey(int key[], int mstSet[], int V) {
//     int min = INT_MAX, min_index;
//     for (int v = 0; v < V; v++) {
//         if (mstSet[v] == 0 && key[v] < min) {
//             min = key[v];
//             min_index = v;
//         }
//     }
//     return min_index;
// }

// void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int V) {
//     int parent[V], key[V];
//     int mstSet[V];
    
//     for (int i = 0; i < V; i++) {
//         key[i] = INT_MAX;
//         mstSet[i] = 0;
//     }
    
//     key[0] = 0;
//     parent[0] = -1;
    
//     for (int count = 0; count < V - 1; count++) {
//         int u = minKey(key, mstSet, V);
//         mstSet[u] = 1;
        
//         for (int v = 0; v < V; v++) {
//             if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
//                 parent[v] = u;
//                 key[v] = graph[u][v];
//             }
//         }
//     }
    
//     printf("Edges in the Minimum Spanning Tree:\n");
//     for (int i = 1; i < V; i++) {
//         printf("%d - %d: %d\n", parent[i], i, graph[i][parent[i]]);
//     }
// }

// int main() {
//     int V, i, j;
//     printf("Enter the number of vertices: ");
//     scanf("%d", &V);
    
//     int graph[MAX_VERTICES][MAX_VERTICES];
    
//     printf("Enter the adjacency matrix (enter 0 if no edge exists between two vertices):\n");
//     for (i = 0; i < V; i++) {
//         for (j = 0; j < V; j++) {
//             scanf("%d", &graph[i][j]);
//         }
//     }
    
//     primMST(graph, V);
    
//     return 0;
// }


#include <stdio.h>
#include <limits.h>

#define V 9

int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v], min_index = v;
        }
    }
    return min_index;
}

void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    int mstSet[V];
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("Edges in the MST:\n");
    for (int i = 1; i < V; i++) {
        printf("Edge: %d - %d, Weight: %d\n", parent[i], i, graph[i][parent[i]]);
    }
}

int main() {
    int graph[V][V];
    printf("Enter the adjacency matrix (9x9), use 0 for no edge:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    primMST(graph);

    return 0;
}
