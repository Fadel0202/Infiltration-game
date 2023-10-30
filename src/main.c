#define _POSIX_C_SOURCE 199309L
#include "time.h"
#include "table.h"
#include "graphique.h"
#include "terrain.h"
#include <MLV/MLV_all.h>

#define LENGTHT 60
#define WIDTHT 45
#define HEIGHTG 800
#define WIDTHG 1000


struct timespec end_time, newtime,begin_time,gametime;

int main(int argc, char const *argv[])
{
	int game_running=1;
	int end,score,score2,mode,range,flag_space,flag_speed,mana_use;
	Coord coord,coordperso;
	Terrain terrain;
	Personnage personnage;
	char table[TABLE_LENGTH][TABLE_MAX_STRING_LENGTH];
	int scores[TABLE_LENGTH];
	char table2[TABLE_LENGTH][TABLE_MAX_STRING_LENGTH];
	int scores2[TABLE_LENGTH];
	int table_lengh = 0;
	int frame = 0;
	int direction,lastdirection;
	long frametime,extratime;
	coord.y = LENGTHT;
	coord.x = WIDTHT;
	coordperso.x = 1;
	coordperso.y = 1;
	mana_use = 0;


	int width=WIDTHG,height=HEIGHTG;


	MLV_create_window("Infiltration","Infiltration",width,height);
   	MLV_change_window_size( width, height );
   	int x,y;
    int mlv_taille_image = 15;
    MLV_Keyboard_button touche;
    MLV_Keyboard_modifier mod;
    MLV_Button_state state;
    MLV_Image *wall,*floor,*guardian,*relique,*hero,*start,*floor2;

    wall = MLV_load_image("doc/wall1.png");
    floor = MLV_load_image("doc/floor1.png");
    guardian = MLV_load_image("doc/guardian1.png");
    relique = MLV_load_image("doc/relique1.png");
    hero = MLV_load_image("doc/hero1.png");
    floor2 = MLV_load_image("doc/floor2.png");
    start = MLV_load_image("doc/start1.png");
	MLV_resize_image_with_proportions(wall,mlv_taille_image,mlv_taille_image);
	MLV_resize_image_with_proportions(floor,mlv_taille_image,mlv_taille_image);
	MLV_resize_image_with_proportions(guardian,mlv_taille_image,mlv_taille_image);
	MLV_resize_image_with_proportions(relique,mlv_taille_image,mlv_taille_image);
	MLV_resize_image_with_proportions(hero,mlv_taille_image,mlv_taille_image);
	MLV_resize_image_with_proportions(floor2,mlv_taille_image,mlv_taille_image);
	MLV_resize_image_with_proportions(start,mlv_taille_image,mlv_taille_image);


	init_perso(&personnage,coordperso);
	init_terrain(&terrain,coord,personnage);
	mode = 0;
	range = 4;
	/**
	affiche_terrain_ASCII(terrain);
	**/
	affiche_terrain_MLV(terrain, wall,floor,guardian,relique,hero,floor2,start,mode ,mlv_taille_image);
	MLV_actualise_window();
	load_table_from_file(table,scores,&table_lengh,"bin/table.bin");
	load_table_from_file(table2,scores2,&table_lengh,"bin/table2.bin");
	 clock_gettime(CLOCK_REALTIME,&begin_time);
	
	/* Main loop over the frames */
	while(game_running){
		/* get the time at the start of the frame in nanosec */
		direction = 0;
		flag_space = 0;
		flag_speed = 0;
		clock_gettime(CLOCK_REALTIME,&end_time);
		reset_affiche_MLV(WIDTHT,HEIGHTG);
		affiche_terrain_MLV(terrain, wall,floor,guardian,relique,hero,floor2,start ,mode,mlv_taille_image);
		affiche_personnage_stats_MLV(personnage);
		MLV_actualise_window();
    
        MLV_get_event( &touche, &mod, NULL, NULL,NULL, &x,&y,NULL,&state );
	    if((touche == MLV_KEYBOARD_q &&  state == MLV_PRESSED) || (touche == MLV_KEYBOARD_z && state == MLV_PRESSED)
                || (touche == MLV_KEYBOARD_s && state == MLV_PRESSED) || (touche == MLV_KEYBOARD_d && state == MLV_PRESSED ) || touche == MLV_left_shift_key_was_pressed(mod) || (touche ==  MLV_KEYBOARD_SPACE && state == MLV_PRESSED) ){
		        switch (touche) {
	                 case MLV_KEYBOARD_z: direction = 3;break;
	                 case MLV_KEYBOARD_q: direction = 1;break;
	                 case MLV_KEYBOARD_s: direction = 4;break;
	                 case MLV_KEYBOARD_d: direction = 2;break;
	                 case MLV_KEYBOARD_LSHIFT: flag_speed = 1 ;direction = lastdirection;break;
	                 case MLV_KEYBOARD_SPACE: flag_space = 1 ;direction = lastdirection;break;

	                 default : printf("ceci n est pas censer arrivé \n" ); 
	              }
	              lastdirection = direction;
		    }
        
        	/* dealing with mechanics */
		if(flag_space == 1){
			if(personnage.mana <1){
				flag_space = 0;
			}
			else{
				personnage.mana = personnage.mana - 1;
				mana_use = mana_use + 1;
			}
		}
		if(flag_speed == 1){
			if(personnage.mana <2){
				flag_speed = 0;
			}
			else{
				personnage.mana = personnage.mana - 2;
				mana_use = mana_use + 2;
			}
		}
        if(mode == 1){
        	range = 6;
        } 
       	 if(mode == 0){
        	range = 4;
        }
        player_moove_frame(&terrain,&personnage,direction,flag_speed);
        guardians_moove_frame(&terrain,mode);
        get_case(&terrain,&personnage);

        if(flag_space == 0){
		    if(detects_players(terrain,personnage,range)){
		        	game_running = 0;
		        	end = 0;
		    }
	    }
        if(isFinished(terrain,personnage)){
        	game_running = 0;
        	end = 1;
        }
        if(detect_relics(&terrain,range)){
        	mode = 1;
        	frame = 30 *60;
        }
	    clock_gettime(CLOCK_REALTIME,&newtime);
	    /*Compute  the time spend for the current frame*/
	    frametime = newtime.tv_sec - end_time.tv_sec;
	    frametime += (newtime.tv_sec - end_time.tv_sec) / 1.0E9;

		/*Force the program to wait at least 1/60*/
		extratime = 1 / 60 - frametime;
		if(extratime > 0){
			MLV_wait_milliseconds((int)extratime *1000);
		}

		if (frame >= 0){
			frame = frame - 1;
			if (frame <= 0){
				mode = 0;
				frame = 0;
			}
		}
		
	}
	MLV_free_window();
	if(end == 1){
		clock_gettime(CLOCK_REALTIME,&gametime);
		score = (int) (gametime.tv_sec - begin_time.tv_sec);
		score2 = mana_use ;
		add_to_table(table2,scores2,&table_lengh,"player",score2);
		add_to_table(table,scores,&table_lengh,"player",score);
		print_table(table,scores,table_lengh);
		printf("------------------------- \n" );
		print_table(table2,scores2,table_lengh);
		save_table_to_file(table,scores,"bin/table.bin");
		save_table_to_file(table2,scores2,"bin/table2.bin");
	}
	else{
		printf("game over \n" );
	}
	return 0;
}