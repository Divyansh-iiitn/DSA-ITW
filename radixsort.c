#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Node* insertEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    if (!head) {
        return newNode;
    }
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

int getMax(struct Node* head) {
    int max = head->data;
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data > max) {
            max = temp->data;
        }
        temp = temp->next;
    }
    return max;
}

struct Node* countingSort(struct Node* head, int exp) {
    struct Node* output = NULL;
    int count[10] = {0};
    
    struct Node* temp = head;
    while (temp != NULL) {
        int index = (temp->data / exp) % 10;
        count[index]++;
        temp = temp->next;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    struct Node* outputArray[count[9]];
    temp = head;
    while (temp != NULL) {
        int index = (temp->data / exp) % 10;
        outputArray[count[index] - 1] = temp;
        count[index]--;
        temp = temp->next;
    }

    for (int i = 0; i < count[9]; i++) {
        outputArray[i]->next = (i < count[9] - 1) ? outputArray[i + 1] : NULL;
    }

    return outputArray[0];
}

struct Node* radixSort(struct Node* head) {
    int max = getMax(head);

    for (int exp = 1; max / exp > 0; exp *= 10) {
        head = countingSort(head, exp);
    }

    return head;
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;

    head = insertEnd(head, 17);
    head = insertEnd(head, 45);
    head = insertEnd(head, 75);
    head = insertEnd(head, 90);
    head = insertEnd(head, 82);
    head = insertEnd(head, 24);
    head = insertEnd(head, 2);
    head = insertEnd(head, 66);

    printf("Original List: ");
    printList(head);

    head = radixSort(head);

    printf("Sorted List: ");
    printList(head);

    return 0;
}
