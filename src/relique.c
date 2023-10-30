#include "relique.h"
#include <stdlib.h>
#include <stdio.h>


void init_relique(Relique *relic,Coord coord){
	relic ->coord.x = coord.x;
	relic ->coord.y = coord.y;
	relic -> vu = 0;
	relic -> vide = 0;
}