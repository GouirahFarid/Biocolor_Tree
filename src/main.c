#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rbtree.h"
#include "avltree.h"

// Drfinir le chemin du fichier CSV pour les resultats
#define RESULTS_CSV_FILE "./output/resultats_insertion.csv"

// Creer le repertoire de sortie s'il n'existe pas
void createOutputDirectory() {
    #ifdef _WIN32
        system("mkdir output >nul 2>nul"); // Commande pour Windows
    #else
        system("mkdir -p output"); // Commande pour Linux/macOS
    #endif
}

// Mesurer les performances d'insertion et ecrire les resultats dans un fichier CSV
void measureInsertionPerformance(RedBlackTree *rbTree, AVLTree *avlTree) {
    createOutputDirectory(); // Creer le repertoire de sortie
    int sizes[] = {10, 100, 500, 1000, 1500,};
    FILE *file = fopen(RESULTS_CSV_FILE, "w");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier pour l'ecriture.\n");
        return;
    }

    // ecrire l'en-tête du fichier CSV
    fprintf(file, "Nombre d'elements;Temps AVL (s);Temps Rouge-Noir (s)\n");

    // Boucle pour mesurer les performances pour differentes tailles
    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int n = sizes[i];
        srand(time(NULL)); // Initialiser le generateur de nombres aleatoires

        // Generer des valeurs aleatoires
        int *values = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            values[j] = rand() % 100000;
        }

        clock_t start, end;

        // Mesurer le temps d'insertion pour l'arbre AVL
        start = clock();
        for (int j = 0; j < n; j++) {
            avlTree->root = insertAVLNode(avlTree->root, values[j]);
        }
        end = clock();
        double avlTime = (double)(end - start) / CLOCKS_PER_SEC;

        // Mesurer le temps d'insertion pour l'arbre Rouge-Noir
        start = clock();
        for (int j = 0; j < n; j++) {
            insertRedBlackTree(rbTree, values[j]);
        }
        end = clock();
        double rbTime = (double)(end - start) / CLOCKS_PER_SEC;

        // ecrire les resultats dans le fichier CSV
        fprintf(file, "%d;%.5f;%.5f\n", n, avlTime, rbTime);

        free(values); // Liberer la memoire
    }

    fclose(file);
    printf("Les resultats ont ete enregistres dans le fichier CSV : %s\n", RESULTS_CSV_FILE);
}

// Inserer une valeur dans l'arbre (AVL ou Rouge-Noir)
void insererDansArbre(RedBlackTree *rbTree, AVLTree *avlTree, int isAVL) {
    int valeur;
    printf("Entrez la valeur à inserer : ");
    scanf("%d", &valeur);
    if (isAVL) {
        avlTree->root = insertAVLNode(avlTree->root, valeur);
        printf("Valeur %d inseree dans l'arbre AVL.\n", valeur);
    } else {
        insertRedBlackTree(rbTree, valeur);
        printf("Valeur %d inseree dans l'arbre Rouge-Noir.\n", valeur);
    }
}

// Rechercher une valeur dans l'arbre (AVL ou Rouge-Noir)
void rechercherDansArbre(RedBlackTree *rbTree, AVLTree *avlTree, int isAVL) {
    int valeur;
    printf("Entrez la valeur à rechercher : ");
    scanf("%d", &valeur);
    if (isAVL) {
        AVLNode *resultat = searchAVLNode(avlTree->root, valeur);
        printf("Valeur %d %s dans l'arbre AVL.\n", valeur, resultat ? "trouvee" : "non trouvee");
    } else {
        TreeNode *resultat = searchRedBlackTree(rbTree, valeur);
        printf("Valeur %d %s dans l'arbre Rouge-Noir.\n", valeur, resultat ? "trouvee" : "non trouvee");
    }
}

// Supprimer une valeur dans l'arbre (AVL ou Rouge-Noir)
void supprimerDansArbre(RedBlackTree *rbTree, AVLTree *avlTree, int isAVL) {
    int valeur;
    printf("Entrez la valeur à supprimer : ");
    scanf("%d", &valeur);
    if (isAVL) {
        avlTree->root = deleteAVLNode(avlTree->root, valeur);
        printf("Valeur %d supprimee de l'arbre AVL.\n", valeur);
    } else {
        deleteRedBlackTree(rbTree, valeur);
        printf("Valeur %d supprimee de l'arbre Rouge-Noir.\n", valeur);
    }
}

// Afficher la structure de l'arbre (AVL ou Rouge-Noir)
void afficherArbre(RedBlackTree *rbTree, AVLTree *avlTree, int isAVL) {
    if (isAVL) {
        printf("Structure de l'arbre AVL :\n");
        displayAVLTree(avlTree->root, 0);
    } else {
        printf("Structure de l'arbre Rouge-Noir :\n");
        displayRedBlackTree(rbTree);
    }
}

// Afficher le menu principal
void afficherMenu() {
    printf("========== MENU ==========\n");
    printf("1. Inserer dans l'arbre AVL\n");
    printf("2. Inserer dans l'arbre Rouge-Noir\n");
    printf("3. Rechercher dans l'arbre AVL\n");
    printf("4. Rechercher dans l'arbre Rouge-Noir\n");
    printf("5. Supprimer de l'arbre AVL\n");
    printf("6. Supprimer de l'arbre Rouge-Noir\n");
    printf("7. Afficher l'arbre AVL\n");
    printf("8. Afficher l'arbre Rouge-Noir\n");
    printf("9. Mesurer et comparer les performances d'insertion\n");
    printf("10. Quitter\n");
    printf("==========================\n");
}

// Fonction principale
int main() {
    createOutputDirectory(); // Creer le repertoire de sortie
    RedBlackTree *rbTree = initializeRedBlackTree(); // Initialiser l'arbre Rouge-Noir
    AVLTree *avlTree = initializeAVLTree(); // Initialiser l'arbre AVL

    int choix;

    do {
        afficherMenu(); // Afficher le menu
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                insererDansArbre(rbTree, avlTree, 1);
                break;
            case 2:
                insererDansArbre(rbTree, avlTree, 0);
                break;
            case 3:
                rechercherDansArbre(rbTree, avlTree, 1);
                break;
            case 4:
                rechercherDansArbre(rbTree, avlTree, 0);
                break;
            case 5:
                supprimerDansArbre(rbTree, avlTree, 1);
                break;
            case 6:
                supprimerDansArbre(rbTree, avlTree, 0);
                break;
            case 7:
                afficherArbre(rbTree, avlTree, 1);
                break;
            case 8:
                afficherArbre(rbTree, avlTree, 0);
                break;
            case 9:
                measureInsertionPerformance(rbTree, avlTree);
                break;
            case 10:
                printf("Quitter...\n");
                freeRedBlackTree(rbTree);
                freeAVLTree(avlTree->root);
                free(avlTree);
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 10);

    return 0;
}
