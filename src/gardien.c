#include "gardien.h"
#include <stdlib.h>
#include <stdio.h>


void init_gardien(Gardien *gard,Coord coord,float vitesse,int direction){
	gard ->coord.x = coord.x;
	gard ->coord.y = coord.y;
	gard ->vitesse = vitesse;
	gard -> mode = 0;
	gard ->direction = direction;
	gard ->deccoord.x = 0.5;
	gard ->deccoord.y = 0.5;
}