#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <stdlib.h>
#include "Console.h"
#include "Const.h"
#include "Player.h"
#include "Windows.h"
//#include <winmm.lib>

struct Scene {
	int board[HEIGHT][WIDTH];
	int num_pellets;
	int num_powerups;
	// TODO: add additional fields
	struct Player pac;
	Player ghost[NUM_GHOSTS];
	int cycle;
};

void initialize_Scene(struct Scene *s);
void render_Scene(struct Scene *s);
int update_Scene(struct Scene *s);
void load_Board(int board[HEIGHT][WIDTH], int *num_pellets, int *num_powerups);
void draw_Board(int board[HEIGHT][WIDTH]);

#endif // SCENE_H
