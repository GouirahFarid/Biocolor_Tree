#ifndef AVLTREE_H
#define AVLTREE_H

typedef struct AVLNode {
    int value;
    int height;
    struct AVLNode *left, *right;
} AVLNode;

typedef struct AVLTree {
    AVLNode *root;
} AVLTree;

// Function prototypes
AVLTree *initializeAVLTree();
AVLNode *insertAVLNode(AVLNode *node, int value);
AVLNode *deleteAVLNode(AVLNode *node, int value);
AVLNode *searchAVLNode(AVLNode *node, int value);
void displayAVLTree(AVLNode *node, int level);
void freeAVLTree(AVLNode *node);

#endif
