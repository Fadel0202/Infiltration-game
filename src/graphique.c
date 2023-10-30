#include "graphique.h"
#include <MLV/MLV_all.h>


void affiche_terrain_MLV(Terrain terrain ,MLV_Image *wall,MLV_Image *floor,MLV_Image *guardian,MLV_Image *relic,MLV_Image *hero,MLV_Image *floor2,MLV_Image *start,int mode,int size){
   int i, y;
   for (i = 0; i < terrain.taille.y; i++){
      for (y = 0; y < terrain.taille.x; y++){
         if (terrain.terrain[i][y].personnage) {
            MLV_draw_image(hero,size*i,size*y);
            continue;
         }
         switch(terrain.terrain[i][y].type){
               case WALL:  MLV_draw_image(wall,size*i,size*y);break;
               case FLOOR: if(terrain.terrain[i][y].mana == 0) {MLV_draw_image(floor2,size*i,size*y);}else{MLV_draw_image(floor,size*i,size*y);};break;
               case GUARDIAN: MLV_draw_image(guardian,size*i,size*y) ;break;
               case RELIQUE: MLV_draw_image(relic,size*i,size*y);break;
               case START: MLV_draw_image(start,size*i,size*y);break;
               default: MLV_draw_filled_rectangle(size*i,size*y,15,15,MLV_COLOR_RED);break;
            }
      }
   }
   for (i = 0; i < 5; i++)
   {  
      if(mode == 0){
         MLV_draw_circle((terrain.guardiens[i].coord.y+0.5)*size,(terrain.guardiens[i].coord.x+0.5)*size,60,MLV_COLOR_RED);
      }
      else{
         MLV_draw_circle((terrain.guardiens[i].coord.y+0.5)*size,(terrain.guardiens[i].coord.x+0.5)*size,90,MLV_COLOR_RED);
      }
      
   }
}

void reset_affiche_MLV(int width,int height){
   MLV_clear_window(MLV_COLOR_BLACK);
   MLV_draw_filled_rectangle(0,0,width,height,MLV_COLOR_BLACK);
}

void affiche_personnage_stats_MLV(Personnage personnage){
    MLV_draw_text( 900, 300, "mana : %d", MLV_COLOR_GREEN ,personnage.mana);
    MLV_draw_text( 900, 280, "relique : %d /3", MLV_COLOR_GREEN ,personnage.relique);
   
}