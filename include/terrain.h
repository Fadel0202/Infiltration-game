#ifndef __TERRAIN__
#define __TERRAIN__



#include "gardien.h"
#include "relique.h"
#include "coordonnee.h"
#include "personnage.h"

#define NB_GUARDIENS 5

typedef enum {
  WALL, GUARDIAN ,FLOOR ,RELIQUE ,START
} Casetype;

typedef struct{
  Casetype type;
  int mana;
  int personnage;
  union{
    Gardien gardien;
    Relique relique;
  };
}Case ,* Cases,**Board;

typedef struct terrain{
  Board terrain ;
  Coord taille;
  Gardien * guardiens;
  Relique * reliques;
}Terrain;

int init_terrain(Terrain *terrain, Coord taille,Personnage perso);
void affiche_terrain_ASCII(Terrain terrain);
int max_x_y(Coord espace);
double distance(Coord point1, Coord point2);
void place_guardiens(Terrain *terrain, int nb_guardiens,Personnage perso);
void place_reliques(Terrain *terrain, int nb_reliques);
void generation_terrain(Terrain *terrain,Coord espace,Coord coin_hautgauche,Coord coin_basdroit,int min_side);
void player_moove_frame(Terrain *terrain,Personnage *perso,int direction,int speedmode);
int detect_player(Terrain terrain,Personnage perso,Gardien gardien);
int detects_players(Terrain terrain,Personnage perso,int range);
void guardians_moove_frame(Terrain *terrain,int mode);
void guardian_moove_frame(Terrain *terrain,Gardien * gard,int mode);
int check_walls_in_direction(Terrain *terrain, Gardien *gard, int direction,int mode);
int indexRelique(Terrain terrain,Coord coord);
void get_case(Terrain *terrain,Personnage *perso);
int isFinished(Terrain terrain,Personnage perso);
int detect_relics(Terrain *terrain,int range);
int detect_relic(Terrain terrain ,Relique relic,Gardien gardien);
#endif