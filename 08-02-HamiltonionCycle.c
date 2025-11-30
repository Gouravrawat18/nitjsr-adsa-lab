#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int path[MAX];
int n;


int isSafe(int v, int pos) {
    
    if (graph[path[pos - 1]][v] == 0)
        return 0;

    
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;

    return 1;
}


int hamCycleUtil(int pos) {
    
    if (pos == n) {
        
        if (graph[path[pos - 1]][path[0]] == 1)
            return 1;
        else
            return 0;
    }

    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;

            if (hamCycleUtil(pos + 1) == 1)
                return 1;

            
            path[pos] = -1;
        }
    }
    return 0;
}


int hamCycle() {
    
    for (int i = 0; i < n; i++)
        path[i] = -1;

    path[0] = 0;

    if (hamCycleUtil(1) == 1) {
        printf("\nHamiltonian Cycle Found:\n");
        for (int i = 0; i < n; i++)
            printf("%d ", path[i]);
        printf("%d\n", path[0]); // Close the cycle
        return 1;
    } else {
        printf("\nNo Hamiltonian Cycle exists.\n");
        return 0;
    }
}

int main() {
    int e, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);


    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter the edges (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;  
    }

    hamCycle();

    return 0;
}
