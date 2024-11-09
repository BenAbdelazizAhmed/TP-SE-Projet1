#ifndef BATAILLE_NAVALE_H
#define BATAILLE_NAVALE_H

#include <pthread.h>

#define TAILLE_GRILLE 10
#define NB_BATEAUX 5

// Structure représentant un bateau
typedef struct {
    char nom[20];
    int taille;
    int position_x[10]; // Positions en X des parties du bateau
    int position_y[10]; // Positions en Y des parties du bateau
    int parties_coulees;
} Bateau;

// Structure représentant une grille de jeu
typedef struct {
    char grille[TAILLE_GRILLE][TAILLE_GRILLE];
    Bateau bateaux[NB_BATEAUX];
} Grille;

// Structure représentant un joueur
typedef struct {
    Grille grille;
    pthread_t thread;      // Thread pour le joueur
    int joueur_id;         // ID du joueur
    int gagnant;           // 0 si pas gagné, 1 si gagné
    pthread_mutex_t mutex; // Mutex pour la grille du joueur
} Joueur;

// Déclarations des fonctions
void *fonction_joueur(void *param);
void initialiser_grille(Grille *grille);
void afficher_grille(const Grille *grille);
int tirer(Grille *grille, int x, int y);
int tous_bateaux_coules(const Grille *grille);
void initialiser_bateaux(Grille *grille);

#endif
