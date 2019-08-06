#include "Player.h"

// TODO MS1: Add player functions
void initializePlayer(struct Player *man, int x, int y, int dx, int dy, int color, char c, int score){
	man->x = x;
	man->y = y;
	man->dx = dx;
	man->dy = dy;
	man->icon = c;
	man->color = color;
	man->score = score;
	man->powerTime = 0;
	man->eatable = false;
}

void drawPlayer(struct Player *man){
	cons_change_color(man->color, BLACK);
	cons_move_cursor(man->y, man->x);
	cons_printw("%c", man->icon);
}

void ghostAI(Player *ghost, int world[HEIGHT][WIDTH]){
	int choiceTurn;
	bool canGo=false;
	//bool isNear=false;
	while(!canGo){
		choiceTurn = (rand() % 100) + 1;
		if(choiceTurn<=10){
			choiceTurn = (rand() % 100) + 1;
			if(choiceTurn==1){
				ghost->dx = -ghost->dx;
				ghost->dy = -ghost->dy;
			}
			else{
				choiceTurn = (rand() % 4) + 1;
				if(choiceTurn==1){
					ghost->dx = 0;
					ghost->dy = -1;
				}
				else if(choiceTurn==3){
					ghost->dx = 0;
					ghost->dy = 1;
				}
				else if(choiceTurn==4){
					ghost->dx = -1;
					ghost->dy = 0;
				}
				else if(choiceTurn==2){
					ghost->dx = 1;
					ghost->dy = 0;
				}
			}
			
		}
		if(world[(ghost->y+ghost->dy)][(ghost->x+ghost->dx)]!=WALL){
			canGo=true;
		}
	}
	canGo=false;
	
}

void playerAI(struct Player *man, int world[HEIGHT][WIDTH]){
	int key = 0;
	key = cons_get_keypress();
	
	if(key==UP_ARROW){
		man->dx = 0;
		man->dy = -1;
	}
	else if(key==DOWN_ARROW){
		man->dx = 0;
		man->dy = 1;
	}
	else if(key==LEFT_ARROW){
		man->dx = -1;
		man->dy = 0;
	}
	else if(key==RIGHT_ARROW){
		man->dx = 1;
		man->dy = 0;
	}
	else{
		man->dx = 0;
		man->dy = 0;
	}
	checkPlayerMove(man, world);
}

void checkPlayerMove(struct Player *man, int world[HEIGHT][WIDTH]){
	if(world[(man->y+man->dy)][(man->x+man->dx)]==WALL){
		man->dx = 0;
		man->dy = 0;
	}
	else if(((man->y+man->dy)==TUNNEL_Y)&&(man->x+man->dx==0)){
		man->x=WIDTH-1;
	}
	else if(((man->y+man->dy)==TUNNEL_Y)&&(man->x+man->dx==WIDTH-1)){
		man->x=0;
	}
}

void updatePlayer(struct Player *man){
	man->x = man->x+man->dx;
	man->y = man->y+man->dy;
}