#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adj[MAX];
int visited[MAX];
int stack[MAX];
int stackIndex = 0;
int minCycle = INT_MAX;
int maxCycle = 0;
int isDirected = 1;
int n;

void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;

    if (!isDirected) {
        Node* newNode2 = (Node*)malloc(sizeof(Node));
        newNode2->vertex = u;
        newNode2->next = adj[v];
        adj[v] = newNode2;
    }
}

int inStack(int v) {
    for (int i = 0; i < stackIndex; i++) {
        if (stack[i] == v) return i;
    }
    return -1;
}

void dfs(int u) {
    visited[u] = 1;
    stack[stackIndex++] = u;

    Node* temp = adj[u];
    while (temp) {
        int v = temp->vertex;
        int pos = inStack(v);
        if (pos != -1) {
            int cycleLength = stackIndex - pos;
            if (cycleLength > 1) {
                if (cycleLength < minCycle) minCycle = cycleLength;
                if (cycleLength > maxCycle) maxCycle = cycleLength;
            }
        } else if (!visited[v]) {
            dfs(v);
        }
        temp = temp->next;
    }

    stackIndex--;
    visited[u] = 0;
}

void findCycles() {
    minCycle = INT_MAX;
    maxCycle = 0;

    for (int i = 0; i < n; i++) {
        stackIndex = 0;
        for (int j = 0; j < n; j++) visited[j] = 0;
        dfs(i);
    }

    if (minCycle == INT_MAX) {
        printf("No cycles found.\n");
    } else {
        printf("Smallest Cycle Length: %d\n", minCycle);
        printf("Largest Cycle Length: %d\n", maxCycle);
    }
}

int main() {
    int e;
    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);
    if (n <= 0 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter number of edges: ");
    scanf("%d", &e);
    if (e < 0) {
        printf("Invalid number of edges.\n");
        return 1;
    }

    printf("Is the graph directed? (1 for Yes, 0 for No): ");
    scanf("%d", &isDirected);

    for (int i = 0; i < n; i++) adj[i] = NULL;

    printf("Enter edges (u v) with vertices from 0 to %d:\n", n - 1);
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= n || v < 0 || v >= n) {
            printf("Invalid edge (%d, %d).\n", u, v);
            i--;
            continue;
        }
        addEdge(u, v);
    }

    findCycles();

    return 0;
}
