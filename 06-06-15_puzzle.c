#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define SIZE (N*N)

typedef struct Node {
    int mat[SIZE];
    int empty_pos;
    int cost;      // f = g + h
    int level;     // g = depth
    struct Node* parent;
} Node;


int manhattan(int *mat) {
    int dist = 0;
    for (int i = 0; i < SIZE; i++) {
        if (mat[i] != 0) {
            int val = mat[i] - 1;
            dist += abs(i / N - val / N) + abs(i % N - val % N);
        }
    }
    return dist;
}


int isGoal(int *mat) {
    for (int i = 0; i < SIZE - 1; i++)
        if (mat[i] != i + 1) return 0;
    return mat[SIZE-1] == 0;
}


void swap(int *mat, int i, int j) {
    int temp = mat[i];
    mat[i] = mat[j];
    mat[j] = temp;
}

// Generate child node after moving empty tile
Node* newNode(int *mat, int empty_pos, int new_empty_pos, int level, Node* parent) {
    Node* node = (Node*) malloc(sizeof(Node));
    memcpy(node->mat, mat, SIZE * sizeof(int));
    swap(node->mat, empty_pos, new_empty_pos);
    node->empty_pos = new_empty_pos;
    node->level = level;
    node->cost = level + manhattan(node->mat);
    node->parent = parent;
    return node;
}


int row[] = {-1, 1, 0, 0};
int col[] = {0, 0, -1, 1};

// Simple priority queue based on array (inefficient for large search)
typedef struct {
    Node* nodes[10000];
    int size;
} PriorityQueue;

void pqPush(PriorityQueue* pq, Node* node) {
    pq->nodes[pq->size++] = node;
}

Node* pqPop(PriorityQueue* pq) {
    int min_idx = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->nodes[i]->cost < pq->nodes[min_idx]->cost)
            min_idx = i;
    }
    Node* res = pq->nodes[min_idx];
    pq->nodes[min_idx] = pq->nodes[--pq->size];
    return res;
}

void printPath(Node* root) {
    if (root == NULL) return;
    printPath(root->parent);
    for (int i = 0; i < SIZE; i++) {
        if (i % N == 0) printf("\n");
        if (root->mat[i] == 0)
            printf("   ");
        else
            printf("%2d ", root->mat[i]);
    }
    printf("\n");
}

void solve(int *start) {
    int empty_pos = 0;
    for (int i = 0; i < SIZE; i++) {
        if (start[i] == 0) {
            empty_pos = i;
            break;
        }
    }
    PriorityQueue pq = {.size = 0};
    Node* root = newNode(start, empty_pos, empty_pos, 0, NULL);
    pqPush(&pq, root);

    while (pq.size > 0) {
        Node* minNode = pqPop(&pq);

        if (isGoal(minNode->mat)) {
            printf("Solution found at depth %d\n", minNode->level);
            printPath(minNode);
            return;
        }

        int r = minNode->empty_pos / N;
        int c = minNode->empty_pos % N;

        for (int i = 0; i < 4; i++) {
            int newr = r + row[i];
            int newc = c + col[i];
            if (newr >= 0 && newr < N && newc >= 0 && newc < N) {
                int new_empty_pos = newr * N + newc;
                Node* child = newNode(minNode->mat, minNode->empty_pos, new_empty_pos, minNode->level + 1, minNode);
                pqPush(&pq, child);
            }
        }
    }

    printf("No solution found\n");
}

int main() {
    int start[SIZE] = {
        1, 2, 3, 4,
        5, 6, 0, 8,
        9, 10, 7, 11,
        13, 14, 15, 12
    };
    solve(start);
    return 0;
}
