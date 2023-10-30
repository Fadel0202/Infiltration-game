#ifndef __PERSONNAGE__
#define __PERSONNAGE__


#include "coordonnee.h"

typedef struct personnage{
  Coord coord;
  DecCoord deccoord;
  int mana;
  float vitesse;
  int direction;
  int relique;
}Personnage ;

void init_perso(Personnage *perso,Coord coord);

#endif
