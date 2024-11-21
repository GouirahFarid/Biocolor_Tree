#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

// Fonction utilitaire : Obtenir la hauteur d'un nœud
int height(AVLNode *node) {
    return node ? node->height : 0; // Si le nœud est NULL, retourner 0
}

// Fonction utilitaire : Obtenir le facteur d'equilibre d'un nœud
int getBalance(AVLNode *node) {
    return node ? height(node->left) - height(node->right) : 0;
    // Calculer le facteur d'equilibre : hauteur gauche - hauteur droite
}

// Fonction utilitaire : Creer un nouveau nœud AVL
AVLNode *createAVLNode(int value) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->value = value;            // Assigner la valeur au nœud
    node->height = 1;               // La hauteur initiale du nœud est 1
    node->left = node->right = NULL; // Initialiser les enfants à NULL
    return node;
}

// Initialiser un arbre AVL vide
AVLTree *initializeAVLTree() {
    AVLTree *tree = (AVLTree *)malloc(sizeof(AVLTree));
    tree->root = NULL; // La racine est initialisee à NULL
    return tree;
}

// Rotation à droite
AVLNode *rotateRight(AVLNode *y) {
    AVLNode *x = y->left;   // Le sous-arbre gauche devient la nouvelle racine
    AVLNode *T2 = x->right; // Sauvegarder le sous-arbre droit de x

    x->right = y; // Reorganiser les pointeurs
    y->left = T2;

    // Mettre à jour les hauteurs
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x; // Retourner le nouveau nœud racine
}

// Rotation à gauche
AVLNode *rotateLeft(AVLNode *x) {
    AVLNode *y = x->right; // Le sous-arbre droit devient la nouvelle racine
    AVLNode *T2 = y->left; // Sauvegarder le sous-arbre gauche de y

    y->left = x; // Reorganiser les pointeurs
    x->right = T2;

    // Mettre à jour les hauteurs
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y; // Retourner le nouveau nœud racine
}

// Inserer une valeur dans l'arbre AVL
AVLNode *insertAVLNode(AVLNode *node, int value) {
    if (!node) // Si le nœud est NULL, creer un nouveau nœud
        return createAVLNode(value);

    if (value < node->value) // Inserer dans le sous-arbre gauche
        node->left = insertAVLNode(node->left, value);
    else if (value > node->value) // Inserer dans le sous-arbre droit
        node->right = insertAVLNode(node->right, value);
    else // Si la valeur existe dejà, ne rien faire
        return node;

    // Mettre à jour la hauteur du nœud
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // Calculer le facteur d'equilibre
    int balance = getBalance(node);

    // Rotation à droite (Left-Left)
    if (balance > 1 && value < node->left->value)
        return rotateRight(node);

    // Rotation à gauche (Right-Right)
    if (balance < -1 && value > node->right->value)
        return rotateLeft(node);

    // Rotation gauche-droite (Left-Right)
    if (balance > 1 && value > node->left->value) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Rotation droite-gauche (Right-Left)
    if (balance < -1 && value < node->right->value) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node; // Retourner le nœud mis à jour
}

// Rechercher une valeur dans l'arbre AVL
AVLNode *searchAVLNode(AVLNode *node, int value) {
    if (!node || node->value == value) // Si le nœud est NULL ou si la valeur est trouvee
        return node;

    if (value < node->value) // Rechercher dans le sous-arbre gauche
        return searchAVLNode(node->left, value);
    else // Rechercher dans le sous-arbre droit
        return searchAVLNode(node->right, value);
}

// Fonction utilitaire : Obtenir le nœud avec la plus petite valeur
AVLNode *minValueNode(AVLNode *node) {
    AVLNode *current = node;

    while (current->left != NULL) // Parcourir le sous-arbre gauche
        current = current->left;

    return current; // Retourner le nœud avec la plus petite valeur
}

// Supprimer un nœud de l'arbre AVL
AVLNode *deleteAVLNode(AVLNode *node, int value) {
    if (!node)
        return node;

    if (value < node->value) // Supprimer dans le sous-arbre gauche
        node->left = deleteAVLNode(node->left, value);
    else if (value > node->value) // Supprimer dans le sous-arbre droit
        node->right = deleteAVLNode(node->right, value);
    else { // Si le nœud à supprimer est trouve
        if (!node->left || !node->right) { // Cas avec un ou zero enfant
            AVLNode *temp = node->left ? node->left : node->right;

            if (!temp) { // Aucun enfant
                temp = node;
                node = NULL;
            } else // Un seul enfant
                *node = *temp;

            free(temp); // Liberer le nœud temporaire
        } else { // Cas avec deux enfants
            AVLNode *temp = minValueNode(node->right); // Obtenir le successeur
            node->value = temp->value; // Copier la valeur
            node->right = deleteAVLNode(node->right, temp->value); // Supprimer le successeur
        }
    }

    if (!node)
        return node;

    // Mettre à jour la hauteur
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // Calculer le facteur d'equilibre
    int balance = getBalance(node);

    // Rotation à droite (Left-Left)
    if (balance > 1 && getBalance(node->left) >= 0)
        return rotateRight(node);

    // Rotation gauche-droite (Left-Right)
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Rotation à gauche (Right-Right)
    if (balance < -1 && getBalance(node->right) <= 0)
        return rotateLeft(node);

    // Rotation droite-gauche (Right-Left)
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node; // Retourner le nœud mis à jour
}

// Afficher la structure de l'arbre AVL
void displayAVLTreeHelper(AVLNode *node, int indent) {
    if (node) {
        displayAVLTreeHelper(node->right, indent + 4); // Afficher le sous-arbre droit

        for (int i = 0; i < indent; i++) { // Ajouter une indentation
            printf(" ");
        }
        printf("%d\n", node->value); // Afficher la valeur du nœud

        displayAVLTreeHelper(node->left, indent + 4); // Afficher le sous-arbre gauche
    }
}

// Afficher l'arbre AVL
void displayAVLTree(AVLNode *node, int level) {
    if (!node) {
        printf("L'arbre AVL est vide.\n"); // Si l'arbre est vide
        return;
    }
    printf("Structure de l'arbre AVL :\n");
    displayAVLTreeHelper(node, 0); // Appeler la fonction utilitaire
}

// Liberer la memoire allouee pour l'arbre AVL
void freeAVLTree(AVLNode *node) {
    if (node) {
        freeAVLTree(node->left); // Liberer le sous-arbre gauche
        freeAVLTree(node->right); // Liberer le sous-arbre droit
        free(node); // Liberer le nœud courant
    }
}
