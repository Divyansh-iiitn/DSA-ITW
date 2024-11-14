#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 3  

typedef struct BTreeNode {
    int keys[MAX_KEYS];            
    struct BTreeNode* children[MAX_KEYS + 1]; 
    int n;
    int leaf;
} BTreeNode;

BTreeNode* createNode(int leaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->n = 0;
    newNode->leaf = leaf;
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

int findPredecessor(BTreeNode* node, int key) {
    int i = 0;

    while (i < node->n && node->keys[i] < key) {
        i++;
    }

    if (i < node->n && node->keys[i] == key) {
        if (node->children[i] != NULL) {
            BTreeNode* leftChild = node->children[i];
            while (!leftChild->leaf) {
                leftChild = leftChild->children[leftChild->n];
            }
            return leftChild->keys[leftChild->n - 1];
        }
    }

    return -1; 
}

void inOrderTraversal(BTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->leaf) {
                inOrderTraversal(root->children[i]);
            }
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf) {
            inOrderTraversal(root->children[i]);
        }
    }
}

int main() {
    BTreeNode* root = createNode(0); 
    root->keys[0] = 10;
    root->n = 1;

    BTreeNode* child1 = createNode(1); 
    child1->keys[0] = 5;
    child1->n = 1;

    BTreeNode* child2 = createNode(1); 
    child2->keys[0] = 15;
    child2->n = 1;

    root->children[0] = child1;
    root->children[1] = child2;

    printf("In-order traversal of B-tree:\n");
    inOrderTraversal(root);
    printf("\n");

    int key = 10;
    int predecessor = findPredecessor(root, key);
    if (predecessor != -1) {
        printf("Predecessor of key %d is: %d\n", key, predecessor);
    } else {
        printf("Predecessor not found for key %d\n", key);
    }

    return 0;
}
