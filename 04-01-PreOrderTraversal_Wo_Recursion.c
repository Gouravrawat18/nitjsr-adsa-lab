#include<stdio.h>
#include<stdlib.h>

struct Node{
   
    int data;
    struct Node* Left;
    struct Node* Right;
};

struct Node* createNode(int data){

    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->Left = newNode->Right = NULL;

    return newNode;   
}
void preOrder(struct Node* root){
    if(root == NULL) return;

    struct Node* stack[100];
    int top =-1;

    stack[++top]=root;

    while (top>=0)
    {
       
        struct Node* node=stack[top--];
        printf("%d", node->data);

        if (node->Right)
        {
             stack[++top]=node->Right;
        }
        if (node->Left)
        {
             stack[++top]=node->Left;
        }
        
    }
}

    int main()
    {
        struct Node* root = createNode(1);
        root->Left = createNode(2);
        root->Right= createNode(3);
        root->Left->Left=createNode(4);
        root->Left->Right =createNode(5);
        root->Right->Left = createNode(6);
        root->Right->Right= createNode(7);

        printf("PreOrder Traversal is : \n");
        preOrder (root);
        return 0;
    }
    
    


