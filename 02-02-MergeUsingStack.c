#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int low;
    int high;
} Range;


typedef struct {
    Range arr[MAX];
    int top;
} Stack;


void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, Range r) {
    if (s->top < MAX - 1) {
        s->arr[++s->top] = r;
    }
}

Range pop(Stack *s) {
    return s->arr[s->top--];
}


void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[low + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L);
    free(R);
}

void mergeSortIterative(int arr[], int n) {
    Stack s;
    initStack(&s);

    push(&s, (Range){0, n - 1});

    Stack processed;
    initStack(&processed);

    while (!isEmpty(&s)) {
        Range current = pop(&s);

        if (current.low < current.high) {
            int mid = (current.low + current.high) / 2;

            push(&processed, current);

            push(&s, (Range){mid + 1, current.high});
            push(&s, (Range){current.low, mid});
        }
    }

    while (!isEmpty(&processed)) {
        Range cur = pop(&processed);
        int mid = (cur.low + cur.high) / 2;
        merge(arr, cur.low, mid, cur.high);
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    mergeSortIterative(arr, n);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
