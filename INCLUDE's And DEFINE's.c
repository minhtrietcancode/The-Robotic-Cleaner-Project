#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
/****************************************************************************
                      DEFINE CONSTANTS AND STRUCTURES
****************************************************************************/
// the elements in the world
#define CLEANER 'X'
#define WALL 'W'
#define EMPTY 'E'
#define DIRT 'D'

// the allowed directions of move in the world
#define LEFT 'l'
#define RIGHT 'r'
#define UP 'u'
#define DOWN 'd'

// Constants for invalid index
#define INVALID_INDEX -1

// Index constants for row and column offsets for task 2
#define ROW_INDEX 0
#define COL_INDEX 1

// Index constants for the direction offset of each moves in task 2
#define LEFT_INDEX 0
#define RIGHT_INDEX 1
#define UP_INDEX 2
#define DOWN_INDEX 3

// Define the DIRECTION_OFFSETS array for task 2
const int DIRECTION_OFFSETS[4][2] = {
    {0, -1}, // LEFT  (same row, column decreases)
    {0, 1},  // RIGHT (same row, column increases)
    {-1, 0}, // UP    (row decreases, same column)
    {1, 0}   // DOWN  (row increases, same column)
};

// Define direction priorities for task 3
#define PRIORITY_UP    0
#define PRIORITY_RIGHT 1
#define PRIORITY_DOWN  2
#define PRIORITY_LEFT  3
#define PRIORITY_INVALID 4

// Define search direction steps for task 3
#define FORWARD_STEP   1
#define BACKWARD_STEP -1

// Search result codes for task 3
#define NOT_FOUND -1

// define struct for task 3 
typedef struct {
    char direction;      // Movement character to return ('u', 'r', 'd', 'l')
    int priority;        // Priority level (0=highest to 3=lowest)
    int *pos_to_update;  // Position value to update during search
    int fixed_pos;       // Position that stays constant during search
    int start;           // Starting position for the search
    int end;             // Ending position for the search
    int step;            // Direction to step (-1 for up/left, 1 for down/right)
} DirtSearch_t;

// define a node structure to use linked list for task 4
typedef struct node {
    char direction;
    struct node* next;
} node_t;
