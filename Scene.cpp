#include "Scene.h"
#include "Windows.h"
//#include "creature_roar2.wav"
//#include <winmm.lib>
void initialize_Scene(struct Scene *s)
{
	// Load in board from text file
	load_Board(s->board, &s->num_pellets, &s->num_powerups);
	int tempdx;
	for(int i=0; i<NUM_GHOSTS; i++){
		tempdx = (rand() % 3) - 1;
		initializePlayer(&s->ghost[i], GHOST_HOME_X+i, GHOST_HOME_Y, tempdx, 0, GHOST_COLOR, GHOST_CHAR, 0);
	}
	initializePlayer(&s->pac, PLAYER_HOME_X, PLAYER_HOME_Y, 0, 0, PLAYER_COLOR, PLAYER_CHAR, 0);
	s->cycle=0;
	//sound
	//orig: PlaySound("C:/users/Skynet Access/desktop/ProgramData/C++/CS101_Assign05/creature_roar2", NULL, SND_ASYNC);
	//sndPlaySound("C:/users/Skynet Access/desktop/ProgramData/C++/CS101_Assign05/creature_roar2",  SND_MEMORY);
}

void render_Scene(struct Scene *s)
{
	// Draw board
	draw_Board(s->board);
	drawPlayer(&s->pac);
	for(int i=0; i<NUM_GHOSTS; i++){
		drawPlayer(&s->ghost[i]);
	}
	//print score
	cons_change_color(YELLOW+INTENSE, BLACK);
	cons_move_cursor(0, WIDTH+5);
	cons_printw("Score: %i", s->pac.score);
}

// Routine to update scene
int update_Scene(struct Scene *s){
	//variables
	bool death=false;
	//int colFlash=0;
	
	//move the player if able
	playerAI(&s->pac, s->board);
	updatePlayer(&s->pac);
	for(int i=0; i<NUM_GHOSTS; i++){
		if((s->pac.powerTime==0 || s->ghost[i].eatable==false) && (s->ghost[i].x==s->pac.x && s->ghost[i].y==s->pac.y)){
			death = true;
		}
		//eat
		else if(s->pac.powerTime!=0 && (s->ghost[i].x==s->pac.x && s->ghost[i].y==s->pac.y)){
			s->pac.score += 500;
			s->ghost[i].x=GHOST_HOME_X;
			s->ghost[i].y=GHOST_HOME_Y;
			s->ghost[i].eatable=false;
			s->ghost[i].color=GHOST_COLOR;
		}
	}
	
	
	//does player eat pellet
	if(s->board[s->pac.y][s->pac.x]==PELLET){
		s->board[s->pac.y][s->pac.x]=EMPTY;
		s->num_pellets--;
		s->pac.score += PELLET_VAL;
	}
	else if(s->board[s->pac.y][s->pac.x]==POWER_UP){
		s->board[s->pac.y][s->pac.x]=EMPTY;
		s->num_powerups--;
		s->pac.score += POWER_VAL;
		s->pac.powerTime=300;
		for(int i=0; i<NUM_GHOSTS; i++){
			s->ghost[i].eatable=true;
		}
	}
	
	//move ghosts
	//Why the living F*** they wont slow down is beyond me at this point.
	if(s->cycle%GHOST_DELAY==0){
		for(int i=0; i<NUM_GHOSTS; i++){
			ghostAI(&s->ghost[i], s->board);
			updatePlayer(&s->ghost[i]);
			if((s->pac.powerTime==0 || s->ghost[i].eatable==false) && (s->ghost[i].x==s->pac.x && s->ghost[i].y==s->pac.y)){
				death = true;
				//colFlash=0;
			}
			//eat
			else if(s->pac.powerTime!=0 && (s->ghost[i].x==s->pac.x && s->ghost[i].y==s->pac.y)){
				s->pac.score += 500;
				s->ghost[i].x=GHOST_HOME_X;
				s->ghost[i].y=GHOST_HOME_Y;
				s->ghost[i].eatable=false;
				s->ghost[i].color=GHOST_COLOR;
			}
			//make flash
			else if(s->pac.powerTime!=0 && s->ghost[i].eatable){
				if(s->cycle%2==0){
					s->ghost[i].color=WHITE+INTENSE;
					if(s->cycle%2==0 && s->pac.powerTime<75){
						s->ghost[i].color=RED+INTENSE;
					}
				}
				else{
					s->ghost[i].color=BLUE+INTENSE;
				}
				//colFlash++;
			}
			else{
				s->ghost[i].eatable=false;
				s->ghost[i].color=GHOST_COLOR;
			}
		}		
	}
	
	//update power time
	if(s->pac.powerTime>0){
		s->pac.powerTime--;
		if(s->pac.powerTime%3==0){
			s->pac.color=BLUE+INTENSE;
		}
		else if(s->pac.powerTime%2==0 && s->pac.powerTime<75){
				s->pac.color=RED+INTENSE;
			}
		else{
			s->pac.color=GREEN+INTENSE;
		}
	}
	else{
		s->pac.color=YELLOW+INTENSE;
	}
	
	//update cycles
	s->cycle++;
	
//crap?
	// TODO: for now, just see if a key was pressed,
	// and if so, return true (game is done)
	//int key = cons_get_keypress();
	if ((s->num_pellets + s->num_powerups) == 0){
		return 1;
	}
	else if (death){
		return 1;
	}
	return 0;
}

// Routine to draw game board - DO NOT MODIFY!
void draw_Board(int board[HEIGHT][WIDTH])
{
	int i,j;
	int loc;

	cons_change_color(WHITE,BLACK);
	// Loop over game grid and draw appropriate character
	for(i=0; i<HEIGHT; i++)
	{
		for(j=0; j<WIDTH; j++)
		{
			// Move to current location
			cons_move_cursor(i,j);
			loc = board[i][j];
			cons_change_color(BLACK,BLACK);
			// Draw wall
			if(loc == WALL)
			{
				cons_change_color(BLUE,BLUE);
				cons_printw("%c",WALL_CHAR);
			}
			// Draw pellet
			else if(loc == PELLET)
			{
				cons_change_color(WHITE,BLACK);
				cons_printw("%c",PELLET_CHAR);
			}
			// Draw powerup
			else if(loc == POWER_UP)
			{
				cons_change_color(BLACK,WHITE);
				cons_printw("%c",POWER_CHAR);
			}
		}
	}
}

// Routine to load board from text file - DO NOT MODIFY!
void load_Board(int board[HEIGHT][WIDTH], int *num_pellets, int *num_powerups)
{
	FILE* in;
	char ch;
	int i,j;
	
	*num_pellets = 0;
	*num_powerups = 0;
	
	in = fopen("board.txt","r");
	if(!in)
	{
		printf("Unable to open file.");
		exit(0);
	}

	for(i=0; i<HEIGHT; i++)
	{
		for(j=0; j<WIDTH; j++)
		{
			fscanf(in,"%c",&ch);
			if(ch=='+')
			{
				board[i][j] = WALL;
			}
			else if(ch=='.')
			{
				board[i][j] = PELLET;
				(*num_pellets)++;
			}
			else if(ch=='O')
			{
				board[i][j] = POWER_UP;
				(*num_powerups)++;
			}
			else
			{
				board[i][j] = EMPTY;
			}
		}
		fscanf(in,"%c",&ch);
		fscanf(in,"%c",&ch);
	}

	fclose(in);

	return;
}
