# Bomberman

Projet universitaire, codé en C, réalisé à l'aide des librairies MLV et SDL.

## Comment compiler

### Prérequis

Il vous faudra installer la [librairie MLV](http://www-igm.univ-mlv.fr/~boussica/mlv/).

### Compiler le projet

Utilisez `make` depuis le dossier racine afin de compiler et lancer le jeu.


### Options spécifiques du makefile

* `make rebuild` Recompile tous les fichiers objets et l'executable,
* `make clean` Supprime tous les fichiers objets et l'executable,
* `make run` Lance seulement le jeu, ne compile pas les changements,
* `make debug` Lance le jeu en mode debug.

## Comment jouer

### Menu

Utilisez les flèches directionelles et RETURN pour naviguer dans le menu, ESCAPE pour quitter le jeu.

### Jeu

Vous pouvez interrompre une partie à tout moment en appuyant sur ESCAPE, elle pourra être reprise depuis le menu.
Le but du jeu est de terminer la partie avec le plus de points.
Chaque caisse détruite rapporte 5 points, un bonus fait perdre 10 points mais peut s'avérer rentable pour gagner plus de points par la suite. Tuer un adversaire rapport 40 points et mourir en fait perdre 50. Le jeu s'arrête lorsqu'il ne reste plus qu'un joueur.

### Controles

#### Joueur 1

Flèches directionnelles pour se déplacer et SHIFT pour poser une bombe.

#### Joueur 2

Z, Q, S, D pour se déplacer et E pour poser une bombe.

#### Joueur 3

O, K, L, M pour se déplacer et P pour poser une bombe.

#### Joueur 4

G, V, B, N pour se déplacer et H pour poser une bombe.

### Editeur

Vous pouvez créer vos propres niveaux dans l'éditeur, CTRL+S pour le sauvegarder, ESCAPE pour retourner au menu.
