#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/****************************************************************************
                      DEFINE CONSTANTS AND STRUCTURES
****************************************************************************/
#define MAX_WORLD_SIZE 6
#define MAX_MOVES 100
#define MAX_QUEUE_SIZE 10000

// Direction constants
#define DIR_UP    'u'
#define DIR_DOWN  'd'
#define DIR_LEFT  'l'
#define DIR_RIGHT 'r'

// Tile constants
#define TILE_DIRT   'D'
#define TILE_EMPTY  'E'
#define TILE_WALL   'W'
#define TILE_ROBOT  'X'

// Movement offsets [row, col]
const int MOVES[4][2] = {
    {-1, 0},  // UP
    {1, 0},   // DOWN
    {0, -1},  // LEFT
    {0, 1}    // RIGHT
};

const char MOVE_CHARS[4] = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};

// Structure to represent a state in the search
typedef struct {
    char world[MAX_WORLD_SIZE][MAX_WORLD_SIZE];
    char moves[MAX_MOVES];
    int move_count;
} State_t;

// Queue structure for BFS
typedef struct {
    State_t* states[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue_t;
