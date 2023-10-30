#ifndef __GRAPHIQUE__
#define __GRAPHIQUE__
#include "terrain.h"
#include <MLV/MLV_all.h>


void affiche_terrain_MLV(Terrain terrain ,MLV_Image *wall,MLV_Image *floor,MLV_Image *guardian,MLV_Image *relic,MLV_Image *hero,MLV_Image *floor2,MLV_Image *start,int mode,int size);
void reset_affiche_MLV(int width,int height);
void affiche_personnage_stats_MLV(Personnage personnage);

#endif