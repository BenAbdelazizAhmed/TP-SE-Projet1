# Jeu de Bataille Navale Multi-Joueurs

## Description
Ce programme implémente un jeu de bataille navale en mode console où deux joueurs peuvent jouer simultanément grâce à l'utilisation de threads. Chaque joueur place ses bateaux sur une grille et essaie de toucher les bateaux de l'autre joueur.

## Compilation et exécution
1. Clonez le projet.
2. Compilez avec `gcc -o bataille_navale bataille_navale.c -pthread`.
3. Exécutez le jeu avec `./bataille_navale`.

## Règles du jeu
- Chaque joueur place ses bateaux sur une grille.
- À chaque tour, les joueurs essaient de toucher les bateaux de l'autre joueur.
- Le jeu se termine lorsqu'un joueur coule tous les bateaux de l'autre.

## Structure du code
- `bataille_navale.c` : code principal du jeu.
- `bataille_navale.h` : définitions des structures et des fonctions.
