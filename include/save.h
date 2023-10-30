#ifndef __TABLE__
#define __TABLE__


#include <stdio.h>
#include <string.h>

#define TABLE_LENGTH 10
#define MAX_STRING_LENGTH 100


int init_terrain(Terrain *terrain, Coord taille);
void affiche_terrain_ASCII(Terrain terrain);
int max_x_y(Coord espace);
void generation_terrain(Terrain *terrain,Coord espace,Coord coin_hautgauche,Coord coin_basdroit,int min_side);


#endif