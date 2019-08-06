#ifndef CONST_H
#define CONST_H

// Define WHITE
#define WHITE INTENSE+GRAY

// Board extents
#define WIDTH 28
#define HEIGHT 22

// Board location markers
#define EMPTY 0
#define WALL 1
#define PELLET 2
#define POWER_UP 3

// Board display characters
#define WALL_CHAR 95
#define PELLET_CHAR 46
#define POWER_CHAR 79

// Player/Ghost characters
#define PLAYER_CHAR 60
#define PLAYER_COLOR YELLOW
#define GHOST_CHAR 35
#define GHOST_COLOR RED
#define NUM_GHOSTS 4

// Particular board positions
#define GHOST_HOME_X 12
#define GHOST_HOME_Y 8
#define PLAYER_HOME_X 14
#define PLAYER_HOME_Y 16
#define TUNNEL_Y 10

// Point values
#define PELLET_VAL 10
#define POWER_VAL 100
#define CAP_VAL 200

// Ghost speed delay
#define GHOST_DELAY 3

#endif // CONST_H
