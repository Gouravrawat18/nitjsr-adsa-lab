#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int key;
    Color color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
} RBNode;

RBNode* NIL;

RBNode* createTree_rb() {
    NIL = (RBNode*)malloc(sizeof(RBNode));
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NULL;
    NIL->key = 0;
    return NIL;
}

RBNode* newNode_rb(int key) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->key = key;
    node->color = RED;
    node->left = node->right = node->parent = NIL;
    return node;
}

void leftRotate_rb(RBNode** root, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate_rb(RBNode** root, RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;
    if (x->right != NIL) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NIL) *root = x;
    else if (y == y->parent->right) y->parent->right = x;
    else y->parent->left = x;
    x->right = y;
    y->parent = x;
}

void insertFixup_rb(RBNode** root, RBNode* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate_rb(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate_rb(root, z->parent->parent);
            }
        } else {
            RBNode* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate_rb(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate_rb(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void insertItem_rb(RBNode** root, int key) {
    RBNode* z = newNode_rb(key);
    RBNode* y = NIL;
    RBNode* x = *root;
    while (x != NIL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == NIL) *root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    z->left = z->right = NIL;
    z->color = RED;
    insertFixup_rb(root, z);
}

RBNode* searchItem_rb(RBNode* root, int key) {
    if (root == NIL || key == root->key) return root;
    if (key < root->key) return searchItem_rb(root->left, key);
    return searchItem_rb(root->right, key);
}

RBNode* treeMinimum_rb(RBNode* node) {
    while (node->left != NIL) node = node->left;
    return node;
}

void transplant_rb(RBNode** root, RBNode* u, RBNode* v) {
    if (u->parent == NIL) *root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

void deleteFixup_rb(RBNode** root, RBNode* x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBNode* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate_rb(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate_rb(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate_rb(root, x->parent);
                x = *root;
            }
        } else {
            RBNode* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate_rb(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate_rb(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate_rb(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

void deleteItem_rb(RBNode** root, int key) {
    RBNode* z = searchItem_rb(*root, key);
    if (z == NIL) return;
    RBNode* y = z;
    Color y_original_color = y->color;
    RBNode* x;
    if (z->left == NIL) {
        x = z->right;
        transplant_rb(root, z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant_rb(root, z, z->left);
    } else {
        y = treeMinimum_rb(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            transplant_rb(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant_rb(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (y_original_color == BLACK) deleteFixup_rb(root, x);
}

void inorder_rb(RBNode* root) {
    if (root != NIL) {
        inorder_rb(root->left);
        printf("%d ", root->key);
        inorder_rb(root->right);
    }
}

void deleteTree_rb(RBNode* root) {
    if (root == NIL) return;
    deleteTree_rb(root->left);
    deleteTree_rb(root->right);
    if (root != NIL) free(root);
}

int main() {
    RBNode* root = createTree_rb();
    insertItem_rb(&root, 10);
    insertItem_rb(&root, 20);
    insertItem_rb(&root, 30);
    insertItem_rb(&root, 15);
    insertItem_rb(&root, 25);
    printf("RB inorder: ");
    inorder_rb(root);
    printf("\n");
    deleteItem_rb(&root, 20);
    printf("After delete 20: ");
    inorder_rb(root);
    printf("\n");
    RBNode* f = searchItem_rb(root, 25);
    if (f != NIL) printf("Found %d\n", f->key);
    else printf("Not Found\n");
    deleteTree_rb(root);
    free(NIL);
    return 0;
}
