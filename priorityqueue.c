#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int priority;
    struct Node* next;
};

struct Node* createNode(int data, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

struct Node* insert(struct Node* head, int data, int priority) {
    struct Node* newNode = createNode(data, priority);

    if (!head || priority < head->priority) {
        newNode->next = head;
        head = newNode;
    } else {
        struct Node* temp = head;
        while (temp->next && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    return head;
}

struct Node* deleteHighestPriority(struct Node* head) {
    if (!head) {
        printf("The priority queue is empty.\n");
        return NULL;
    }
    
    struct Node* temp = head;
    head = head->next;
    printf("Deleted element with data %d and priority %d\n", temp->data, temp->priority);
    free(temp);
    return head;
}

void display(struct Node* head) {
    if (!head) {
        printf("The priority queue is empty.\n");
        return;
    }
    struct Node* temp = head;
    printf("Priority Queue:\n");
    while (temp) {
        printf("Data: %d, Priority: %d\n", temp->data, temp->priority);
        temp = temp->next;
    }
}

int main() {
    struct Node* pq = NULL;

    pq = insert(pq, 4, 2);
    pq = insert(pq, 5, 1);
    pq = insert(pq, 6, 3);
    pq = insert(pq, 7, 0);

    display(pq);

    pq = deleteHighestPriority(pq);
    display(pq);

    pq = deleteHighestPriority(pq);
    display(pq);

    return 0;
}
