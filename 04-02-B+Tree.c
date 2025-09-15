#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BPlusNode {
    int *keys;
    int t;
    struct BPlusNode **children;
    int n;
    bool leaf;
    struct BPlusNode *next;
} BPlusNode;

BPlusNode* createNode_bpt(int t, bool leaf) {
    BPlusNode* node = (BPlusNode*)malloc(sizeof(BPlusNode));
    node->t = t;
    node->leaf = leaf;
    node->keys = (int*)malloc(sizeof(int)*(2*t-1));
    node->children = (BPlusNode**)malloc(sizeof(BPlusNode*)*(2*t));
    node->n = 0;
    node->next = NULL;
    return node;
}

BPlusNode* createTree_bpt(int t) {
    return createNode_bpt(t, true);
}

BPlusNode* searchItem_bpt(BPlusNode* root, int k) {
    BPlusNode* cur = root;
    while (!cur->leaf) {
        int i = 0;
        while (i < cur->n && k >= cur->keys[i]) i++;
        cur = cur->children[i];
    }
    int i = 0;
    while (i < cur->n && cur->keys[i] < k) i++;
    if (i < cur->n && cur->keys[i] == k) return cur;
    return NULL;
}

void splitChild_bpt(BPlusNode* x, int i, BPlusNode* y) {
    int t = y->t;
    BPlusNode* z = createNode_bpt(t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t-1; j++) z->keys[j] = y->keys[j+t];
    if (!y->leaf) for (int j = 0; j < t; j++) z->children[j] = y->children[j+t];
    y->n = t - 1;
    for (int j = x->n; j >= i+1; j--) x->children[j+1] = x->children[j];
    x->children[i+1] = z;
    for (int j = x->n-1; j >= i; j--) x->keys[j+1] = x->keys[j];
    x->keys[i] = y->keys[t-1];
    x->n = x->n + 1;
    if (y->leaf) {
        z->next = y->next;
        y->next = z;
    }
}

void insertNonFull_bpt(BPlusNode* x, int k) {
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
        if (x->children[i]->n == 2*x->t - 1) {
            splitChild_bpt(x, i, x->children[i]);
            if (x->keys[i] < k) i++;
        }
        insertNonFull_bpt(x->children[i], k);
    }
}

BPlusNode* insertItem_bpt(BPlusNode* root, int k) {
    if (!root) return NULL;
    if (searchItem_bpt(root, k)) return root;
    if (root->n == 2*root->t - 1) {
        BPlusNode* s = createNode_bpt(root->t, false);
        s->children[0] = root;
        splitChild_bpt(s, 0, root);
        int i = 0;
        if (s->keys[0] < k) i++;
        insertNonFull_bpt(s->children[i], k);
        return s;
    } else {
        insertNonFull_bpt(root, k);
        return root;
    }
}

void traverse_bpt(BPlusNode* root) {
    BPlusNode* cur = root;
    while (!cur->leaf) cur = cur->children[0];
    while (cur) {
        for (int i = 0; i < cur->n; i++) printf("%d ", cur->keys[i]);
        cur = cur->next;
    }
    printf("\n");
}

bool deleteItem_bpt_leafonly(BPlusNode* root, int k) {
    BPlusNode* cur = root;
    while (!cur->leaf) {
        int i = 0;
        while (i < cur->n && k >= cur->keys[i]) i++;
        cur = cur->children[i];
    }
    int i = 0;
    while (i < cur->n && cur->keys[i] < k) i++;
    if (i < cur->n && cur->keys[i] == k) {
        for (int j = i; j < cur->n-1; j++) cur->keys[j] = cur->keys[j+1];
        cur->n--;
        return true;
    }
    return false;
}

void deleteTree_bpt(BPlusNode* root) {
    if (!root) return;
    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++) deleteTree_bpt(root->children[i]);
    }
    free(root->keys);
    free(root->children);
    free(root);
}

int main() {
    int t = 3;
    BPlusNode* root = createTree_bpt(t);
    int arr[] = {5, 15, 25, 35, 45, 55, 65, 75};
    for (int i = 0; i < 8; i++) root = insertItem_bpt(root, arr[i]);
    printf("B+ traverse: ");
    traverse_bpt(root);
    deleteItem_bpt_leafonly(root, 25);
    printf("After deleting 25 (leaf-only): ");
    traverse_bpt(root);
    BPlusNode* f = searchItem_bpt(root, 55);
    if (f) printf("Found 55\n");
    else printf("Not found\n");
    deleteTree_bpt(root);
    return 0;
}
