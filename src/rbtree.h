#ifndef RBTREE_H
#define RBTREE_H

typedef enum { RED, BLACK } Color;

typedef struct TreeNode {
    int value;
    Color color;
    struct TreeNode *left, *right, *parent;
} TreeNode;

typedef struct RedBlackTree {
    TreeNode *root;
    TreeNode *nil; // Sentinel node for null leaves
} RedBlackTree;

// Function prototypes
RedBlackTree *initializeRedBlackTree();
void insertRedBlackTree(RedBlackTree *tree, int value);
void deleteRedBlackTree(RedBlackTree *tree, int value);
TreeNode *searchRedBlackTree(RedBlackTree *tree, int value);
void displayRedBlackTree(RedBlackTree *tree);
void freeRedBlackTree(RedBlackTree *tree);

#endif
