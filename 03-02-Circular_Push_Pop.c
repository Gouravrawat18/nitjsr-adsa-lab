#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

int arrQueue[SIZE];
int frontA = -1, rearA = -1;

struct Node {
    int data;
    struct Node* next;
};
struct Node* frontL = NULL;
struct Node* rearL = NULL;

void pushArray(int value) {
    if ((frontA == 0 && rearA == SIZE - 1) || (rearA == (frontA - 1) % (SIZE - 1))) {
        printf("Queue Overflow\n");
        return;
    }
    if (frontA == -1) {
        frontA = rearA = 0;
        arrQueue[rearA] = value;
    } else if (rearA == SIZE - 1 && frontA != 0) {
        rearA = 0;
        arrQueue[rearA] = value;
    } else {
        arrQueue[++rearA] = value;
    }
}

void popArray() {
    if (frontA == -1) {
        printf("Queue Underflow\n");
        return;
    }
    printf("Popped: %d\n", arrQueue[frontA]);
    if (frontA == rearA) {
        frontA = rearA = -1;
    } else if (frontA == SIZE - 1) {
        frontA = 0;
    } else {
        frontA++;
    }
}

void displayArray() {
    if (frontA == -1) {
        printf("Queue is Empty\n");
        return;
    }
    printf("Queue: ");
    if (rearA >= frontA) {
        for (int i = frontA; i <= rearA; i++)
            printf("%d ", arrQueue[i]);
    } else {
        for (int i = frontA; i < SIZE; i++)
            printf("%d ", arrQueue[i]);
        for (int i = 0; i <= rearA; i++)
            printf("%d ", arrQueue[i]);
    }
    printf("\n");
}

void pushList(int value) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = value;
    if (frontL == NULL) {
        frontL = rearL = temp;
        rearL->next = frontL;
    } else {
        rearL->next = temp;
        rearL = temp;
        rearL->next = frontL;
    }
}

void popList() {
    if (frontL == NULL) {
        printf("Queue Underflow\n");
        return;
    }
    if (frontL == rearL) {
        printf("Popped: %d\n", frontL->data);
        free(frontL);
        frontL = rearL = NULL;
    } else {
        struct Node* temp = frontL;
        printf("Popped: %d\n", temp->data);
        frontL = frontL->next;
        rearL->next = frontL;
        free(temp);
    }
}

void displayList() {
    if (frontL == NULL) {
        printf("Queue is Empty\n");
        return;
    }
    struct Node* temp = frontL;
    printf("Queue: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != frontL);
    printf("\n");
}

int main() {
    int mainChoice, subChoice, val;
    while (1) {
        printf("\n1. Circular Queue using Array\n2. Circular Queue using Linked List\n3. Exit\n");
        scanf("%d", &mainChoice);
        switch (mainChoice) {
            case 1:
                while (1) {
                    printf("\n--- Array Circular Queue ---\n1. Push\n2. Pop\n3. Display\n4. Back\n");
                    scanf("%d", &subChoice);
                    if (subChoice == 1) {
                        printf("Enter value: ");
                        scanf("%d", &val);
                        pushArray(val);
                    } else if (subChoice == 2) {
                        popArray();
                    } else if (subChoice == 3) {
                        displayArray();
                    } else if (subChoice == 4) break;
                    else printf("Invalid Choice\n");
                }
                break;
            case 2:
                while (1) {
                    printf("\n--- Linked List Circular Queue ---\n1. Push\n2. Pop\n3. Display\n4. Back\n");
                    scanf("%d", &subChoice);
                    if (subChoice == 1) {
                        printf("Enter value: ");
                        scanf("%d", &val);
                        pushList(val);
                    } else if (subChoice == 2) {
                        popList();
                    } else if (subChoice == 3) {
                        displayList();
                    } else if (subChoice == 4) break;
                    else printf("Invalid Choice\n");
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid Choice\n");
        }
    }
    return 0;
}
