#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct RBTreeNode {
    char key;
    Color color;
    struct RBTreeNode *left, *right, *parent;
} RBTreeNode;

RBTreeNode* createNode(char key) {
    RBTreeNode* newNode = (RBTreeNode*)malloc(sizeof(RBTreeNode));
    newNode->key = key;
    newNode->color = RED;  // New nodes are always red
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Function for left rotation
void leftRotate(RBTreeNode** root, RBTreeNode* x) {
    RBTreeNode* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Function for right rotation
void rightRotate(RBTreeNode** root, RBTreeNode* y) {
    RBTreeNode* x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        *root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

// Function to fix violations after insertion
void fixViolations(RBTreeNode** root, RBTreeNode* z) {
    while (z != *root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBTreeNode* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                // Case 1: Uncle is red, recolor and move up the tree
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // Case 2: Uncle is black, need rotations
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            RBTreeNode* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                // Case 1: Uncle is red, recolor and move up the tree
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // Case 2: Uncle is black, need rotations
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK; // Root must always be black
}

// Function to insert a new node into the tree
void insert(RBTreeNode** root, char key) {
    RBTreeNode* z = createNode(key);
    RBTreeNode* y = NULL;
    RBTreeNode* x = *root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == NULL) {
        *root = z; // Tree was empty
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    fixViolations(root, z);
}

// In-order traversal to print the tree
void inorderTraversal(RBTreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%c ", root->key);
        inorderTraversal(root->right);
    }
}

// Main function for testing insertion of keys
int main() {
    RBTreeNode* root = NULL;

    // Keys to be inserted into the RB-tree
    char keys[] = {'F', 'S', 'Q', 'K', 'C', 'L', 'H', 'T', 'V', 'W', 'M', 'R', 'N', 'P', 'A', 'B', 'X', 'Y', 'D', 'Z', 'E'};
    int n = sizeof(keys) / sizeof(keys[0]);

    // Insert keys into the RB-tree
    for (int i = 0; i < n; i++) {
        insert(&root, keys[i]);
    }

    // Print the In-order traversal of the RB-tree
    printf("In-order traversal of the Red-Black Tree:\n");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
