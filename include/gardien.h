#ifndef __GARDIEN__
#define __GARDIEN__


#include "coordonnee.h"

typedef struct gardien{
  Coord coord;
  DecCoord deccoord;
  int mode;
  float vitesse;
  int direction;
}Gardien;

void init_gardien(Gardien *gard,Coord coord,float vitesse,int direction);

#endif
