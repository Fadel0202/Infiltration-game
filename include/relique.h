#ifndef __RELIQUE__
#define __RELIQUE__

#include "coordonnee.h"

typedef struct relique{
  Coord coord;
  int vide;
  int vu;
}Relique;

void init_relique(Relique *relic,Coord coord);

#endif