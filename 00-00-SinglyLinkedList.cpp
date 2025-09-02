#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = NULL;

void insert(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
    cout << "Inserted: " << value << endl;
}


void search(int value) {
    Node* temp = head;
    int pos = 1;
    while (temp != NULL) {
        if (temp->data == value) {
            cout << "Value " << value << " found at position " << pos << endl;
            return;
        }
        temp = temp->next;
        pos++;
    }
    cout << "Value " << value << " not found!\n";
}


void deleteNode(int value) {
    Node* temp = head;
    Node* prev = NULL;

    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Value not found!\n";
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    delete temp;
    cout << "Deleted: " << value << endl;
}


void display() {
    Node* temp = head;
    cout << "Linked List: ";
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

int main() {
    int choice, value;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                insert(value);
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                search(value);
                break;
            case 3:
                cout << "Enter value to delete: ";
                cin >> value;
                deleteNode(value);
                break;
            case 4:
                display();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}