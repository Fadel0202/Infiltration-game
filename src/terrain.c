#include "terrain.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


int init_terrain(Terrain *terrain, Coord taille,Personnage perso){
   srand(time(NULL));
   Board board;
   Gardien * guardiens;
   Relique * reliques;
   Coord espace,coin_hautgauche,coin_basdroit;
   int i,y;
   if (!(reliques = (Relique *)malloc(sizeof(Relique) * 3)))
      return 0;
   if (!(guardiens = (Gardien *)malloc(sizeof(Gardien) * NB_GUARDIENS)))
      return 0;
   if (!(board = (Board)malloc(sizeof(Case) * taille.y)))
      return 0;
   for (i = 0; i < taille.y; i++){
      if (!(board[i] = (Cases)malloc(sizeof(Case) * taille.x)))
         return 0;
   }
   for (i = 0; i < taille.y; i++){
      for (y = 0; y < taille.x; y++){
         if( i == 0 ||i ==taille.y -1)     board[i][y].type = WALL;
         else if( y == 0 ||y ==taille.x -1)     board[i][y].type = WALL;
         else  board[i][y].type = FLOOR;
         board[i][y].personnage = 0;
         board[i][y].mana = 1;
      }
   }
   terrain->terrain = board;
   terrain->taille = taille;
   terrain->guardiens = guardiens;
   terrain->reliques = reliques;
   espace.x = terrain->taille.x -2;
   espace.y = terrain->taille.y -2;
   coin_hautgauche.x = 1;
   coin_hautgauche.y = 1;
   coin_basdroit.x = terrain->taille.x -1;
   coin_basdroit.y = terrain->taille.y -1;
   generation_terrain(terrain,espace,coin_hautgauche,coin_basdroit,9);


   terrain->terrain[1][1].type = START;
   terrain->terrain[1][2].type = START;
   terrain->terrain[2][1].type = START;
   terrain->terrain[2][2].type = START;
   terrain->terrain[perso.coord.y][perso.coord.x].personnage = 1;
   place_guardiens(terrain,NB_GUARDIENS,perso);
   place_reliques(terrain,3);
   return 1;



}


void place_guardiens(Terrain *terrain, int nb_guardiens,Personnage perso) {
    int i,x,y,direction;
    float vitesse;
    for (i = 0; i < nb_guardiens; i++) {
      do{
        x = rand() % (terrain->taille.x - 2) + 1;
        y = rand() % (terrain->taille.y - 2) + 1;
      }while(!(((terrain->terrain[y][x].type == FLOOR) && (distance((Coord){x, y},perso.coord)>15))));
        vitesse = (rand() % 6)/10 + 0.3;
        direction = rand() % 4 +1;
        init_gardien(&(terrain->guardiens[i]), (Coord){x, y}, vitesse, direction);
        terrain->terrain[y][x].type = GUARDIAN;
    }
}

void place_reliques(Terrain *terrain, int nb_reliques) {
    int i,x,y;
    for (i = 0; i < nb_reliques; i++) {
      do{
        x = rand() % (terrain->taille.x - 2) + 1;
        y = rand() % (terrain->taille.y - 2) + 1;
      }while(!(((terrain->terrain[y][x].type == FLOOR))));
        init_relique(&(terrain->reliques[i]), (Coord){x, y});
        terrain->terrain[y][x].type = RELIQUE;
    }
}



double distance(Coord point1, Coord point2) {
    double x_diff = point1.x - point2.x;
    double y_diff = point1.y - point2.y;
    return  sqrt(x_diff*x_diff + y_diff*y_diff);
}


int max_x_y(Coord espace){
   if(espace.x >espace.y) return espace.x;
   return espace.y;
}





void generation_terrain(Terrain *terrain,Coord espace,Coord coin_hautgauche,Coord coin_basdroit,int min_side){
   int vmax_x_y,mur,i,ouverture;
   Coord espace1,espace2,coin_basdroit1,coin_basdroit2,coin_hautgauche1,coin_hautgauche2;
   vmax_x_y = max_x_y(espace);
   if(vmax_x_y < 2 * min_side + 1){
      return;
   }
   if(vmax_x_y < 4 * min_side){
      if(rand() % 2 ==1) return;     
   }
   if(vmax_x_y == espace.x){
      mur = (coin_basdroit.x - coin_hautgauche.x) / 2;
      espace1.x = mur - 1 -coin_basdroit.x;
      espace2.x = mur - ((coin_basdroit.x - coin_hautgauche.x) % 2 ? 1 : 0) -coin_basdroit.x;
      espace1.y = espace.y;
      espace2.y = espace.y;
      if(max_x_y(espace1) < min_side || max_x_y(espace2) < min_side) return;
      for(i=coin_hautgauche.y;i<coin_basdroit.y+1;i++) terrain->terrain[i][mur].type = WALL;
      ouverture = rand() % (coin_basdroit.y -coin_hautgauche.y -3)+coin_hautgauche.y;
      for(i=ouverture;i<ouverture+3;i++) terrain->terrain[i][mur].type = FLOOR;
      coin_hautgauche1.x = coin_hautgauche.x;
      coin_hautgauche1.y = coin_hautgauche.y;
      coin_hautgauche2.x = mur+1;
      coin_hautgauche2.y = coin_hautgauche.y;
      coin_basdroit1.x = mur - 1;
      coin_basdroit1.y = coin_basdroit.y ;
      coin_basdroit2.x = coin_basdroit.x ;
      coin_basdroit2.y = coin_basdroit.y ;
      generation_terrain(terrain,espace1,coin_hautgauche1,coin_basdroit1,min_side);
      generation_terrain(terrain,espace2,coin_hautgauche2,coin_basdroit2,min_side);

   }
   else{
      mur = (coin_basdroit.y - coin_hautgauche.y) / 2;
      espace1.y = mur - 1 -coin_hautgauche.y;
      espace2.y = mur - ((coin_basdroit.y - coin_hautgauche.y) % 2 ? 1 : 0) -coin_hautgauche.y ;
      espace1.x = espace.x;
      espace2.x = espace.x;
      if(max_x_y(espace1) < min_side || max_x_y(espace2) < min_side) return;
      for(i=coin_hautgauche.x;i<coin_basdroit.x+1 ;i++) terrain->terrain[mur][i].type = WALL;
      ouverture = rand() % (coin_basdroit.x -coin_hautgauche.x -3)+coin_hautgauche.x;
      for(i=ouverture;i<ouverture+3;i++) terrain->terrain[mur][i].type = FLOOR;
      coin_hautgauche1.x = coin_hautgauche.x;
      coin_hautgauche1.y = coin_hautgauche.y;
      coin_hautgauche2.x = coin_hautgauche.x;
      coin_hautgauche2.y = mur+1;
      coin_basdroit1.x = coin_basdroit.x ;
      coin_basdroit1.y = mur -1 ;
      coin_basdroit2.x = coin_basdroit.x ; 
      coin_basdroit2.y = coin_basdroit.y ;
      generation_terrain(terrain,espace1,coin_hautgauche1,coin_basdroit1,min_side);
      generation_terrain(terrain,espace2,coin_hautgauche2,coin_basdroit2,min_side);
   }
}


void affiche_terrain_ASCII(Terrain terrain){
   int i, y;
   for (i = 0; i < terrain.taille.y; i++){
      for (y = 0; y < terrain.taille.x; y++){
         if (terrain.terrain[i][y].personnage) {
            printf("P");
            continue;
         }
         switch(terrain.terrain[i][y].type){
            case WALL: printf("#");break;
            case FLOOR: printf(" ");break;
            case GUARDIAN: printf("G");break;
            case RELIQUE: printf("R");break;
            default: printf("E");
         }
      }
      printf("\n");
   }
}


void player_moove_frame(Terrain *terrain,Personnage *perso,int direction,int speedmode){
   float frame_value,next_value,vitesse;
   if(direction == 0){
      perso->vitesse = 0.1;
      perso ->direction = 0;
      return;
   }

   if(perso ->direction != direction){
      perso->vitesse = 0.1;
      perso ->direction = direction;
   }
   else{
      perso->vitesse = perso->vitesse +0.03;
      if(perso->vitesse > 0.9){
          perso->vitesse = 0.9 ;
      }
   }
   if(speedmode ==1){
      vitesse = 1.2;
   }
   else{
      vitesse = perso->vitesse;
   }
   frame_value = vitesse/60 ;
   if(direction == 1){
      next_value = perso -> deccoord.y -frame_value;
      if(next_value< 0){
         if( !(terrain->terrain[perso->coord.y-1][perso->coord.x].type == WALL || terrain->terrain[perso->coord.y-1][perso->coord.x].type == GUARDIAN) ){
            terrain->terrain[perso->coord.y][perso->coord.x].personnage = 0;
            perso->coord.y = perso->coord.y -1;
            perso -> deccoord.y = 1 + next_value;
            terrain->terrain[perso->coord.y][perso->coord.x].personnage = 1;
         }
         return;
      }
      perso -> deccoord.y = next_value;
      return;
   }
   if(direction == 2){
      next_value = perso -> deccoord.y +frame_value;
      if(next_value > 1){
         if( !(terrain->terrain[perso->coord.y+1][perso->coord.x].type == WALL || terrain->terrain[perso->coord.y+1][perso->coord.x].type == GUARDIAN) ){
            terrain->terrain[perso->coord.y][perso->coord.x].personnage = 0;
            perso->coord.y = perso->coord.y + 1;
            perso -> deccoord.y =  next_value - 1;
            terrain->terrain[perso->coord.y][perso->coord.x].personnage = 1;
         }
         return;
      }
      perso -> deccoord.y = next_value;
      return;
   }
   if(direction == 3){
      next_value = perso -> deccoord.x -frame_value;
      if(next_value < 0){
         if( !(terrain->terrain[perso->coord.y][perso->coord.x-1].type == WALL || terrain->terrain[perso->coord.y][perso->coord.x-1].type == GUARDIAN) ){
            terrain->terrain[perso->coord.y][perso->coord.x].personnage = 0;
            perso->coord.x = perso->coord.x - 1;
            perso -> deccoord.x = 1 + next_value ;
            terrain->terrain[perso->coord.y][perso->coord.x].personnage = 1;
         }
         return;
      }
      perso -> deccoord.x = next_value;
      return;
   }
   if(direction == 4){
      next_value = perso -> deccoord.x +frame_value;
      if(next_value > 1){
         if( !(terrain->terrain[perso->coord.y][perso->coord.x+1].type == WALL || terrain->terrain[perso->coord.y][perso->coord.x+1].type == GUARDIAN) ){
            terrain->terrain[perso->coord.y][perso->coord.x].personnage = 0;
            perso->coord.x = 1 + perso->coord.x ;
            perso -> deccoord.x =  next_value - 1 ;
            terrain->terrain[perso->coord.y][perso->coord.x].personnage = 1;
         }
         return;
      }
      perso -> deccoord.x = next_value;
      return;
   }
}

int detects_players(Terrain terrain,Personnage perso,int range){
   int i;
   for(i=0;i<NB_GUARDIENS;i++){
      if(distance(perso.coord,terrain.guardiens[i].coord)< range){
         if(detect_player(terrain,perso,terrain.guardiens[i])==1){
            return 1;
         }
      }
   }
   return 0;
}

int detect_relics(Terrain *terrain,int range){
   int i,y;
   for(i=0;i<NB_GUARDIENS;i++){
      for(y=0;y<3;y++){
      if(distance(terrain->reliques[y].coord,terrain->guardiens[i].coord)< range && terrain->reliques[y].vide == 1 && terrain->reliques[y].vu == 0 ){
         if(detect_relic(*terrain,terrain->reliques[y],terrain->guardiens[i])==1){
            terrain->reliques[y].vu = 1;
            return 1;
            }
         }
      }
   }
   return 0;
}




float floatmin(float a , float b){
   if( a < b){
      return a;
   }
   return b;
}
float floatmax(float a , float b){
   if( a > b){
      return a;
   }
   return b;
}


int detect_relic(Terrain terrain ,Relique relic,Gardien gardien) {
    float x0 = relic.coord.x +0.5;
    float y0 = relic.coord.y +0.5 ;
    float x1 = gardien.coord.x + gardien.deccoord.x;
    float y1 = gardien.coord.y + gardien.deccoord.y;
    int x_inter, y_inter;
    float p,x,y;

    for ( x = floatmin(x0, x1); x <= floatmax(x0, x1); x++) {
        p = (x - x1) / (x0 - x1);

        if (p >= 0 && p <= 1) {
            y_inter = (int)(y1 + (y0 - y1) * p);
            if (terrain.terrain[y_inter][(int) x].type == WALL) {
                return 0;
            }
        }
    }
    for ( y = floatmin(y0, y1); y <= floatmax(y0, y1); y++) {
        p = (y - y1) / (y0 - y1);
        if (p >= 0 && p <= 1) {
            x_inter = (int)(x1 + (x0 - x1) * p);
            if (terrain.terrain[(int)y][x_inter].type == WALL){
                return 0;
            }
        }
    }
    return 1;
}


int detect_player(Terrain terrain,Personnage perso,Gardien gardien) {
    float x0 = perso.coord.x + perso.deccoord.x;
    float y0 = perso.coord.y + perso.deccoord.y;
    float x1 = gardien.coord.x + gardien.deccoord.x;
    float y1 = gardien.coord.y + gardien.deccoord.y;
    int x_inter, y_inter;
    float p,x,y;

    for ( x = floatmin(x0, x1); x <= floatmax(x0, x1); x++) {
        p = (x - x1) / (x0 - x1);

        if (p >= 0 && p <= 1) {
            y_inter = (int)(y1 + (y0 - y1) * p);
            if (terrain.terrain[y_inter][(int) x].type == WALL) {
                return 0;
            }
        }
    }
    for ( y = floatmin(y0, y1); y <= floatmax(y0, y1); y++) {
        p = (y - y1) / (y0 - y1);
        if (p >= 0 && p <= 1) {
            x_inter = (int)(x1 + (x0 - x1) * p);
            if (terrain.terrain[(int)y][x_inter].type == WALL){
                return 0;
            }
        }
    }
    return 1;
}

int indexRelique(Terrain terrain,Coord coord){
   int i;
   for(i=0;i<3;i++){
      if(terrain.reliques[i].coord.x == coord.x && terrain.reliques[i].coord.y == coord.y){
         return i;
      }
   }
   return -1;
}

int isFinished(Terrain terrain,Personnage perso){
   if(terrain.terrain[perso.coord.y][perso.coord.x].type == START && perso.relique >= 3 ){
      return 1;
   }
   return 0;
}

void get_case(Terrain *terrain,Personnage *perso){
   int i;
   if(terrain->terrain[perso->coord.y][perso->coord.x].type == FLOOR){
      perso->mana = perso->mana + terrain->terrain[perso->coord.y][perso->coord.x].mana;
      terrain->terrain[perso->coord.y][perso->coord.x].mana = 0;
   }
   if(terrain->terrain[perso->coord.y][perso->coord.x].type == RELIQUE){
      i = indexRelique(*terrain,perso->coord);
      if(i!=-1){
         if(terrain->reliques[i].vide == 0){
            perso->relique = perso->relique + 1;
            terrain->reliques[i].vide = 1;
         }
         
      }
   }
}

void guardians_moove_frame(Terrain *terrain,int mode){
   int i;
      for(i=0;i<NB_GUARDIENS;i++){
         guardian_moove_frame(terrain,&(terrain->guardiens[i]),mode);
   }
}





                                                                                                         
void guardian_moove_frame(Terrain *terrain,Gardien * gard,int mode){
   int direction,chance;
   float frame_value ,vitesse,next_value;
      chance = rand() % 1000;
      if(chance == 1){
         vitesse = (rand() % 6)/10 + 0.3;
         direction = rand() % 4 +1;
         gard -> vitesse = vitesse;
         gard ->direction =direction;
         return;
      }
      if  (mode == 0) {
         frame_value = (gard->vitesse)/60 ;
      }
      else {
         frame_value = 1.0/60 ;
      }
      direction = gard->direction;
      if(direction == 1){
         next_value = gard -> deccoord.y -frame_value;
         if(next_value< 0){
            if( !( check_walls_in_direction(terrain,gard,direction,mode) || terrain->terrain[gard->coord.y-1][gard->coord.x].personnage == 1) ){
               terrain->terrain[gard->coord.y][gard->coord.x].type = FLOOR;
               gard->coord.y = gard->coord.y -1;
               gard -> deccoord.y = 1 + next_value;
               terrain->terrain[gard->coord.y][gard->coord.x].type = GUARDIAN;
               return;
            }
            vitesse = (rand() % 6)/10 + 0.3;
            direction = rand() % 4 +1;
            gard -> vitesse = vitesse;
            gard ->direction =direction;
            return;
         }
         gard -> deccoord.y = next_value;
         return;
   }
  if(direction == 2){
         next_value = gard -> deccoord.y +frame_value;
         if(next_value> 1){
            if( !(check_walls_in_direction(terrain,gard,direction,mode) || terrain->terrain[gard->coord.y+1][gard->coord.x].personnage == 1) ){
               terrain->terrain[gard->coord.y][gard->coord.x].type = FLOOR;
               gard->coord.y = gard->coord.y +1;
               gard -> deccoord.y =  next_value - 1;
               terrain->terrain[gard->coord.y][gard->coord.x].type = GUARDIAN;
               return;
            }
            vitesse = (rand() % 6)/10 + 0.3;
            direction = rand() % 4 +1;
            gard -> vitesse = vitesse;
            gard ->direction =direction;
            return;
         }
         gard -> deccoord.y = next_value;
         return;
   }
   if(direction == 3){
         next_value = gard -> deccoord.x -frame_value;
         if(next_value< 0){
            if( !(check_walls_in_direction(terrain,gard,direction,mode)|| terrain->terrain[gard->coord.y][gard->coord.x-1].personnage == 1) ){
               terrain->terrain[gard->coord.y][gard->coord.x].type = FLOOR;
               gard->coord.x = gard->coord.x -1;
               gard -> deccoord.x = 1 + next_value;
               terrain->terrain[gard->coord.y][gard->coord.x].type = GUARDIAN;
               return;
            }
            vitesse = (rand() % 6)/10 + 0.3;
            direction = rand() % 4 +1;
            gard -> vitesse = vitesse;
            gard ->direction =direction;
            return;
         }
         gard -> deccoord.x = next_value;
         return;
   }
   if(direction == 4){
         next_value = gard -> deccoord.x +frame_value;
         if(next_value> 1){
            if( !(check_walls_in_direction(terrain,gard,direction,mode)|| terrain->terrain[gard->coord.y][gard->coord.x+1].personnage == 1) ){
               terrain->terrain[gard->coord.y][gard->coord.x].type = FLOOR;
               gard->coord.x = gard->coord.x +1;
               gard -> deccoord.x =   next_value - 1;
               terrain->terrain[gard->coord.y][gard->coord.x].type = GUARDIAN;
               return;
            }
            vitesse = (rand() % 6)/10 + 0.3;
            direction = rand() % 4 +1;
            gard -> vitesse = vitesse;
            gard ->direction =direction;
            return;
         }
         gard -> deccoord.x = next_value;
         return;
   }
}

int check_walls_in_direction(Terrain *terrain, Gardien *gard, int direction,int mode) {
    int check_distance_1, check_distance_2;
    if(mode == 1){
       if(direction == 1) {
           check_distance_1 = terrain->terrain[gard->coord.y - 1][gard->coord.x].type;
           if(check_distance_1 == WALL) return 1;
           check_distance_2 = terrain->terrain[gard->coord.y - 2][gard->coord.x].type;
       } else if (direction == 2) {
           check_distance_1 = terrain->terrain[gard->coord.y + 1][gard->coord.x].type;
           if(check_distance_1 == WALL) return 1;
           check_distance_2 = terrain->terrain[gard->coord.y + 2][gard->coord.x].type;
       } else if (direction == 3) {
           check_distance_1 = terrain->terrain[gard->coord.y][gard->coord.x - 1].type;
           if(check_distance_1 == WALL) return 1;
           check_distance_2 = terrain->terrain[gard->coord.y][gard->coord.x - 2].type;
       } else if (direction == 4) {
           check_distance_1 = terrain->terrain[gard->coord.y][gard->coord.x + 1].type;
           if(check_distance_1 == WALL) return 1;
           check_distance_2 = terrain->terrain[gard->coord.y][gard->coord.x + 2].type;
       } 
       if (check_distance_1 == RELIQUE ||check_distance_1 == START || check_distance_2 == WALL || check_distance_2 == RELIQUE || check_distance_2 == START) {
           return 1;
       }
       return 0;
    }
    else{
      if(direction == 1) {
           check_distance_1 = terrain->terrain[gard->coord.y - 1][gard->coord.x].type;
       } else if (direction == 2) {
           check_distance_1 = terrain->terrain[gard->coord.y + 1][gard->coord.x].type;
       } else if (direction == 3) {
           check_distance_1 = terrain->terrain[gard->coord.y][gard->coord.x - 1].type;
       } else if (direction == 4) {
           check_distance_1 = terrain->terrain[gard->coord.y][gard->coord.x + 1].type;
       } 
       if (check_distance_1 == WALL ||check_distance_1 == RELIQUE ||check_distance_1 == START ) {
           return 1;
       }
       return 0;
    }
}




