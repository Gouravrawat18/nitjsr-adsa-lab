#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

AVLNode* createTree_avl() {
    return NULL;
}

int height_avl(AVLNode* n) {
    return n ? n->height : 0;
}

int max_int(int a, int b) {
    return a > b ? a : b;
}

AVLNode* newNode_avl(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode* rightRotate_avl(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max_int(height_avl(y->left), height_avl(y->right)) + 1;
    x->height = max_int(height_avl(x->left), height_avl(x->right)) + 1;
    return x;
}

AVLNode* leftRotate_avl(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max_int(height_avl(x->left), height_avl(x->right)) + 1;
    y->height = max_int(height_avl(y->left), height_avl(y->right)) + 1;
    return y;
}

int getBalance_avl(AVLNode* n) {
    return n ? height_avl(n->left) - height_avl(n->right) : 0;
}

AVLNode* insertItem_avl(AVLNode* node, int key) {
    if (node == NULL) return newNode_avl(key);
    if (key < node->key) node->left = insertItem_avl(node->left, key);
    else if (key > node->key) node->right = insertItem_avl(node->right, key);
    else return node;
    node->height = 1 + max_int(height_avl(node->left), height_avl(node->right));
    int balance = getBalance_avl(node);
    if (balance > 1 && key < node->left->key) return rightRotate_avl(node);
    if (balance < -1 && key > node->right->key) return leftRotate_avl(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate_avl(node->left);
        return rightRotate_avl(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate_avl(node->right);
        return leftRotate_avl(node);
    }
    return node;
}

AVLNode* minValueNode_avl(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left) current = current->left;
    return current;
}

AVLNode* deleteItem_avl(AVLNode* root, int key) {
    if (root == NULL) return root;
    if (key < root->key) root->left = deleteItem_avl(root->left, key);
    else if (key > root->key) root->right = deleteItem_avl(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else *root = *temp;
            free(temp);
        } else {
            AVLNode* temp = minValueNode_avl(root->right);
            root->key = temp->key;
            root->right = deleteItem_avl(root->right, temp->key);
        }
    }
    if (root == NULL) return root;
    root->height = 1 + max_int(height_avl(root->left), height_avl(root->right));
    int balance = getBalance_avl(root);
    if (balance > 1 && getBalance_avl(root->left) >= 0) return rightRotate_avl(root);
    if (balance > 1 && getBalance_avl(root->left) < 0) {
        root->left = leftRotate_avl(root->left);
        return rightRotate_avl(root);
    }
    if (balance < -1 && getBalance_avl(root->right) <= 0) return leftRotate_avl(root);
    if (balance < -1 && getBalance_avl(root->right) > 0) {
        root->right = rightRotate_avl(root->right);
        return leftRotate_avl(root);
    }
    return root;
}

AVLNode* searchItem_avl(AVLNode* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (key < root->key) return searchItem_avl(root->left, key);
    return searchItem_avl(root->right, key);
}

void deleteTree_avl(AVLNode* root) {
    if (root == NULL) return;
    deleteTree_avl(root->left);
    deleteTree_avl(root->right);
    free(root);
}

void inorder_avl(AVLNode* root) {
    if (root) {
        inorder_avl(root->left);
        printf("%d ", root->key);
        inorder_avl(root->right);
    }
}

int main() {
    AVLNode* root = createTree_avl();
    root = insertItem_avl(root, 10);
    root = insertItem_avl(root, 20);
    root = insertItem_avl(root, 30);
    root = insertItem_avl(root, 40);
    root = insertItem_avl(root, 50);
    root = insertItem_avl(root, 25);
    printf("AVL inorder: ");
    inorder_avl(root);
    printf("\n");
    root = deleteItem_avl(root, 40);
    printf("After delete 40: ");
    inorder_avl(root);
    printf("\n");
    AVLNode* f = searchItem_avl(root, 25);
    if (f) printf("Found %d\n", f->key);
    else printf("Not Found\n");
    deleteTree_avl(root);
    return 0;
}
