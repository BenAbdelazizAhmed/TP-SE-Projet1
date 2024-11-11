#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "bataille_navale.h"

// Fonction pour initialiser la grille d'un joueur
void initialiserGrille(Grille *grille) {
    // Remplir toute la grille avec des '~' (eau)
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            grille->grille[i][j] = '~'; // Indicateur d'eau
        }
    }
    initialiserBateaux(grille);
}

// Fonction pour initialiser les bateaux du joueur
void initialiserBateaux(Grille *grille) {
    // Exemple de bateaux (à personnaliser)
    strcpy(grille->bateaux[0].nom, "Destroyer");
    grille->bateaux[0].taille = 3;
    grille->bateaux[1].taille = 4;
    
    // Placer les bateaux sur la grille (logique simplifiée)
    for (int i = 0; i < 3; i++) {
        grille->grille[1][i] = 'D'; // Bateau Destroyer
    }
    for (int i = 4; i < 8; i++) {
        grille->grille[3][i] = 'C'; // Bateau Croiseur
    }
}

// Fonction pour afficher la grille d'un joueur
void afficherGrille(const Grille *grille) {
    printf("\nGrille de jeu:\n");
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            printf("%c ", grille->grille[i][j]);
        }
        printf("\n");
    }
}

// Fonction pour gérer le tir d'un joueur
int tirer(Grille *grille, int x, int y) {
    if (x < 0 || x >= TAILLE_GRILLE || y < 0 || y >= TAILLE_GRILLE) {
        printf("Coordonnée invalide.\n");
        return 0; // Tir hors limites
    }
    
    if (grille->grille[x][y] == '~') {
        printf("Tir raté!\n");
        grille->grille[x][y] = 'O'; // Marquer un tir raté
        return 1;
    } else if (grille->grille[x][y] == 'D' || grille->grille[x][y] == 'C') {
        printf("Tir réussi!\n");
        grille->grille[x][y] = 'X'; // Marquer un tir réussi
        return 1;
    }
    return 0;
}

// Fonction pour vérifier si tous les bateaux d'un joueur sont coulés
int tousLesBateauxCoules(const Grille *grille) {
    for (int i = 0; i < NB_BATEAUX; i++) {
        for (int j = 0; j < grille->bateaux[i].taille; j++) {
            if (grille->grille[grille->bateaux[i].position_x[j]][grille->bateaux[i].position_y[j]] != 'X') {
                return 0; // Un bateau n'est pas encore coulé
            }
        }
    }
    return 1; // Tous les bateaux sont coulés
}

// Fonction principale du joueur dans son thread
void *fonctionJoueur(void *param) {
    Joueur *joueur = (Joueur *)param;
    int x, y;
    
    while (!joueur->gagnant) {
        printf("Joueur %d, entrez les coordonnées du tir (x y) : ", joueur->joueur_id);
        scanf("%d %d", &x, &y);
        pthread_mutex_lock(&joueur->mutex); // Accès exclusif à la grille

        // Effectuer le tir
        if (tirer(&joueur->grille, x, y)) {
            afficherGrille(&joueur->grille);
        }

        // Vérifier si le joueur a gagné
        if (tousLesBateauxCoules(&joueur->grille)) {
            joueur->gagnant = 1;
            printf("Joueur %d a gagné!\n", joueur->joueur_id);
        }

        pthread_mutex_unlock(&joueur->mutex); // Libérer l'accès à la grille
    }
    return NULL;
}

int main() {
    Joueur joueurs[2];
    pthread_mutex_t mutexes[2];
    
    // Initialisation des mutex pour chaque joueur
    for (int i = 0; i < 2; i++) {
        pthread_mutex_init(&mutexes[i], NULL);
        joueurs[i].gagnant = 0;
        joueurs[i].joueur_id = i + 1;
        joueurs[i].mutex = mutexes[i];
        initialiserGrille(&joueurs[i].grille);
    }

    // Création des threads pour les joueurs
    for (int i = 0; i < 2; i++) {
        pthread_create(&joueurs[i].thread, NULL, fonctionJoueur, (void *)&joueurs[i]);
    }

    // Attendre la fin des threads
    for (int i = 0; i < 2; i++) {
        pthread_join(joueurs[i].thread, NULL);
    }

    // Destruction des mutex
    for (int i = 0; i < 2; i++) {
        pthread_mutex_destroy(&mutexes[i]);
    }

    return 0;
}
vcx