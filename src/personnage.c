#include "personnage.h"
#include <stdlib.h>
#include <stdio.h>

void init_perso(Personnage *perso,Coord coord){
	perso ->coord = coord;
	perso ->vitesse = 0.1;
	perso -> mana = 0;
	perso -> direction = 0;
	perso ->deccoord.x = 0.5;
	perso ->deccoord.y = 0.5;
	perso -> relique = 0;
}




