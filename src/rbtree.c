#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

// Initialiser un arbre Rouge-Noir
RedBlackTree *initializeRedBlackTree() {
    RedBlackTree *tree = (RedBlackTree *)malloc(sizeof(RedBlackTree));
    tree->nil = (TreeNode *)malloc(sizeof(TreeNode)); // Creer un nœud NIL
    tree->nil->color = BLACK; // Le nœud NIL est toujours noir
    tree->root = tree->nil; // La racine de l'arbre est initialisee à NIL
    return tree;
}

// Creer un nouveau nœud pour l'arbre Rouge-Noir
TreeNode *createTreeNode(RedBlackTree *tree, int value) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->value = value; // Assigner la valeur au nœud
    node->color = RED; // Les nouveaux nœuds sont toujours rouges au depart
    node->left = node->right = node->parent = tree->nil; // Initialiser les pointeurs à NIL
    return node;
}

// Effectuer une rotation à gauche autour d'un nœud
void rbTreeRotateLeft(RedBlackTree *tree, TreeNode *x) {
    TreeNode *y = x->right; // Le nœud droit devient la nouvelle racine
    x->right = y->left; // Deplacer le sous-arbre gauche de y à la droite de x
    if (y->left != tree->nil) {
        y->left->parent = x; // Mettre à jour le parent
    }
    y->parent = x->parent; // Mettre à jour le parent de y
    if (x->parent == tree->nil) {
        tree->root = y; // Si x etait la racine, y devient la nouvelle racine
    } else if (x == x->parent->left) {
        x->parent->left = y; // Relier y au parent de x
    } else {
        x->parent->right = y;
    }
    y->left = x; // Relier x à la gauche de y
    x->parent = y;
}

// Effectuer une rotation à droite autour d'un nœud
void rbTreeRotateRight(RedBlackTree *tree, TreeNode *y) {
    TreeNode *x = y->left; // Le nœud gauche devient la nouvelle racine
    y->left = x->right; // Deplacer le sous-arbre droit de x à la gauche de y
    if (x->right != tree->nil) {
        x->right->parent = y;
    }
    x->parent = y->parent; // Mettre à jour le parent de x
    if (y->parent == tree->nil) {
        tree->root = x; // Si y etait la racine, x devient la nouvelle racine
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y; // Relier y à la droite de x
    y->parent = x;
}

// Inserer une valeur dans l'arbre Rouge-Noir
void insertRedBlackTree(RedBlackTree *tree, int value) {
    TreeNode *newNode = createTreeNode(tree, value); // Creer un nouveau nœud
    TreeNode *parent = tree->nil;
    TreeNode *current = tree->root;

    // Trouver la position correcte pour inserer le nœud
    while (current != tree->nil) {
        parent = current;
        if (newNode->value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent; // Definir le parent du nouveau nœud
    if (parent == tree->nil) {
        tree->root = newNode; // Si l'arbre est vide, le nouveau nœud devient la racine
    } else if (newNode->value < parent->value) {
        parent->left = newNode; // Inserer comme enfant gauche
    } else {
        parent->right = newNode; // Inserer comme enfant droit
    }

    // Reequilibrage après insertion
    while (newNode->parent->color == RED) {
        if (newNode->parent == newNode->parent->parent->left) { // Cas où le parent est un enfant gauche
            TreeNode *uncle = newNode->parent->parent->right; // Determiner l'oncle
            if (uncle->color == RED) { // Cas 1 : L'oncle est rouge
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            } else { // Cas 2 et 3 : L'oncle est noir
                if (newNode == newNode->parent->right) { // Cas 2 : Le nœud est un enfant droit
                    newNode = newNode->parent;
                    rbTreeRotateLeft(tree, newNode);
                }
                newNode->parent->color = BLACK; // Cas 3 : Le nœud est un enfant gauche
                newNode->parent->parent->color = RED;
                rbTreeRotateRight(tree, newNode->parent->parent);
            }
        } else { // Cas où le parent est un enfant droit
            TreeNode *uncle = newNode->parent->parent->left; // Determiner l'oncle
            if (uncle->color == RED) { // Cas 1 : L'oncle est rouge
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            } else { // Cas 2 et 3 : L'oncle est noir
                if (newNode == newNode->parent->left) { // Cas 2 : Le nœud est un enfant gauche
                    newNode = newNode->parent;
                    rbTreeRotateRight(tree, newNode);
                }
                newNode->parent->color = BLACK; // Cas 3 : Le nœud est un enfant droit
                newNode->parent->parent->color = RED;
                rbTreeRotateLeft(tree, newNode->parent->parent);
            }
        }
    }
    tree->root->color = BLACK; // La racine est toujours noire
}

// Rechercher une valeur dans l'arbre Rouge-Noir
TreeNode *searchRedBlackTree(RedBlackTree *tree, int value) {
    TreeNode *current = tree->root;
    while (current != tree->nil && current->value != value) {
        if (value < current->value)
            current = current->left; // Rechercher dans le sous-arbre gauche
        else
            current = current->right; // Rechercher dans le sous-arbre droit
    }
    return current;
}

// Supprimer un nœud de l'arbre Rouge-Noir
void deleteRedBlackTree(RedBlackTree *tree, int value) {
    // Implementer la logique de suppression avec reequilibrage
}

// Afficher la structure de l'arbre Rouge-Noir
void displayRedBlackTreeHelper(TreeNode *node, TreeNode *nil, int indent) {
    if (node != nil) {
        displayRedBlackTreeHelper(node->right, nil, indent + 4); // Afficher le sous-arbre droit
        for (int i = 0; i < indent; i++) {
            printf(" ");
        }
        printf("%d (%s)\n", node->value, node->color == RED ? "RED" : "BLACK"); // Afficher la valeur et la couleur
        displayRedBlackTreeHelper(node->left, nil, indent + 4); // Afficher le sous-arbre gauche
    }
}

// Fonction principale pour afficher l'arbre Rouge-Noir
void displayRedBlackTree(RedBlackTree *tree) {
    if (tree->root == tree->nil) {
        printf("L'arbre Rouge-Noir est vide.\n");
        return;
    }
    printf("Structure de l'arbre Rouge-Noir :\n");
    displayRedBlackTreeHelper(tree->root, tree->nil, 0);
}

// Fonction recursive pour liberer tous les nœuds d'un arbre Rouge-Noir
void freeRedBlackTreeNodes(TreeNode *node, TreeNode *nil) {
    if (node != nil) {
        freeRedBlackTreeNodes(node->left, nil);  // Liberer le sous-arbre gauche
        freeRedBlackTreeNodes(node->right, nil); // Liberer le sous-arbre droit
        free(node); // Liberer le nœud courant
    }
}

// Liberer la memoire allouee pour l'arbre Rouge-Noir
void freeRedBlackTree(RedBlackTree *tree) {
    if (tree) {
        freeRedBlackTreeNodes(tree->root, tree->nil); // Liberer tous les nœuds de l'arbre
        free(tree->nil); // Liberer le nœud NIL
        free(tree); // Liberer la structure de l'arbre
    }
}

