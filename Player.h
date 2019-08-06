#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include "Const.h"
#include "Console.h"

// TODO MS1: Add player structure
struct Player {
	int x, y, dx, dy, color, score, powerTime;
	bool eatable;
	char icon;
};

// TODO MS1: Add player function prototypes
void initializePlayer(struct Player *man, int x, int y, int dx, int dy, int color, char c, int score);
void drawPlayer(struct Player *man);
void playerAI(struct Player *man, int world[HEIGHT][WIDTH]);
void ghostAI(Player *ghost, int world[HEIGHT][WIDTH]);
void checkPlayerMove(struct Player *man, int world[][28]);
void updatePlayer(struct Player *man);
#endif // PLAYER_H
