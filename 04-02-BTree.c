#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BTreeNode {
    int *keys;
    int t;
    struct BTreeNode **C;
    int n;
    bool leaf;
} BTreeNode;

BTreeNode* createNode_btree(int t, bool leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->t = t;
    node->leaf = leaf;
    node->keys = (int*)malloc(sizeof(int)*(2*t-1));
    node->C = (BTreeNode**)malloc(sizeof(BTreeNode*)*(2*t));
    node->n = 0;
    return node;
}

BTreeNode* createTree_btree(int t) {
    return createNode_btree(t, true);
}

BTreeNode* searchItem_btree(BTreeNode* x, int k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]) i++;
    if (i < x->n && x->keys[i] == k) return x;
    if (x->leaf) return NULL;
    return searchItem_btree(x->C[i], k);
}

void splitChild_btree(BTreeNode* x, int i, BTreeNode* y) {
    int t = y->t;
    BTreeNode* z = createNode_btree(t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t-1; j++) z->keys[j] = y->keys[j+t];
    if (!y->leaf) for (int j = 0; j < t; j++) z->C[j] = y->C[j+t];
    y->n = t - 1;
    for (int j = x->n; j >= i+1; j--) x->C[j+1] = x->C[j];
    x->C[i+1] = z;
    for (int j = x->n-1; j >= i; j--) x->keys[j+1] = x->keys[j];
    x->keys[i] = y->keys[t-1];
    x->n = x->n + 1;
}

void insertNonFull_btree(BTreeNode* x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
        x->n = x->n + 1;
    } else {
        while (i >= 0 && x->keys[i] > k) i--;
        i++;
        if (x->C[i]->n == 2*x->t - 1) {
            splitChild_btree(x, i, x->C[i]);
            if (x->keys[i] < k) i++;
        }
        insertNonFull_btree(x->C[i], k);
    }
}

BTreeNode* insertItem_btree(BTreeNode* root, int k) {
    if (!root) return NULL;
    if (searchItem_btree(root, k)) return root;
    if (root->n == 2*root->t - 1) {
        BTreeNode* s = createNode_btree(root->t, false);
        s->C[0] = root;
        splitChild_btree(s, 0, root);
        int i = 0;
        if (s->keys[0] < k) i++;
        insertNonFull_btree(s->C[i], k);
        return s;
    } else {
        insertNonFull_btree(root, k);
        return root;
    }
}

void deleteTree_btree(BTreeNode* root) {
    if (!root) return;
    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++) deleteTree_btree(root->C[i]);
    }
    free(root->keys);
    free(root->C);
    free(root);
}

void traverse_btree(BTreeNode* root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf) traverse_btree(root->C[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf) traverse_btree(root->C[i]);
}

bool deleteItem_btree_leafonly(BTreeNode* root, int k) {
    BTreeNode* node = root;
    while (true) {
        int i = 0;
        while (i < node->n && k > node->keys[i]) i++;
        if (i < node->n && node->keys[i] == k) {
            if (node->leaf) {
                for (int j = i; j < node->n-1; j++) node->keys[j] = node->keys[j+1];
                node->n--;
                return true;
            } else return false;
        }
        if (node->leaf) return false;
        node = node->C[i];
    }
    return false;
}

int main() {
    int t = 3;
    BTreeNode* root = createTree_btree(t);
    int arr[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int i = 0; i < 8; i++) root = insertItem_btree(root, arr[i]);
    printf("B-Tree traverse: ");
    traverse_btree(root);
    printf("\n");
    deleteItem_btree_leafonly(root, 6);
    printf("After deleting 6 (leaf-only delete): ");
    traverse_btree(root);
    printf("\n");
    BTreeNode* f = searchItem_btree(root, 17);
    if (f) printf("Found 17\n");
    else printf("Not found\n");
    deleteTree_btree(root);
    return 0;
}
