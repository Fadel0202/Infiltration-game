#include "collision.h"
#include <stdlib.h>
#include <stdio.h>


Coord Intersection(Coord perso, Coord gardien,int a){
  Coord Alpha ;
  Alpha.x = 0;
  Alpha.y = 0;
  int pa,ya;

  pa = ((a - perso.x) / (gardien.x - perso.x));
  if( pa < 0 && pa > 1 ){
    return Alpha;
  }
  else{
  ya = (pa * gardien.y) + ((1-pa)*perso.y);
  Alpha.x = a;
  Alpha.y= ya;
  return Alpha;
  }
}

int verif_case_traverse(Coord perso, Coord gardien, Terrain *t, int case_x,int case_y){
    if ((t->terrain)[case_x][case_y].type == WALL) {
      return 0;
    }
    else if ((case_x >= perso.x && case_x <= gardien.x) && (case_y >= perso.y && case_y <= gardien.y)) {
      return 1;
    }
    return 0;
}
