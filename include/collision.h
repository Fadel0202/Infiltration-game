#ifndef __COLLISION__
#define __COLLISION__

#include "terrain.h"


Coord Intersection(Coord perso, Coord gardien,int a);

int verif_case_traverse(Coord perso, Coord gardien,Terrain *t,int case_x,int case_y);
#endif
