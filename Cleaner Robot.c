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

/****************************************************************************
                           FUNCTION PROTOTYPES 
****************************************************************************/
/* FUNCTIONS FOR TASK 1 */
void get_position(char** world, int row_num, int col_num, 
                  int* row_pos, int* col_pos);
int distance_to_wall(char** world, int row_num, int col_num);

/* FUNCTIONS FOR TASK 2 */
void get_new_position(int current_row, int current_col, char direction, 
                      int* new_row, int* new_col);
void make_move(char** world, int row_num, int col_num, char direction);

/* FUNCTIONS FOR TASK 3 */
int find_dirt_position(char **world, DirtSearch_t search, 
                       int row_num, int col_num);
int get_priority(char direction);
char* path_to_next(char** world, int row_num, int col_num);

/* FUNCTIONS FOR TASK 4 */
node_t* new_node(char input_direction);
node_t* add_at_foot(node_t* head, char input_direction);
node_t* get_and_delete_at_foot(node_t* head);
char reverse_direction(char input_direction);
node_t* add_reverse_at_foot(node_t* head, char input_direction);
char* clean_path(char** world, int row_num, int col_num);

/* HELPER FUNCTIONS FOR TESTING OUTPUT */
void print_world(char** world, int row_num, int col_num); 
void run_test_case(char temp_world[3][3], int row_num, int col_num);

/****************************************************************************
                    MAIN FUNCTION FOR TESTING OUTPUT 
****************************************************************************/
int main() {
    // Test Case 3
    printf("Test Case 3:\n");
    char temp_world3[3][3] = {
        {'E', 'D', 'E'},
        {'X', 'D', 'D'},
        {'E', 'E', 'E'}
    };
    run_test_case(temp_world3, 3, 3);

    // Test Case 4
    printf("Test Case 4:\n");
    char temp_world4[3][3] = {
        {'E', 'D', 'E'},
        {'X', 'D', 'E'},
        {'E', 'D', 'E'}
    };
    run_test_case(temp_world4, 3, 3);

    // Test Case 5
    printf("Test Case 5:\n");
    char temp_world5[3][3] = {
        {'E', 'D', 'D'},
        {'D', 'E', 'E'},
        {'D', 'E', 'X'}
    };
    run_test_case(temp_world5, 3, 3);

    return 0;
}

/****************************************************************************
                          FUNCTIONS FOR TASK 1
****************************************************************************/
/* Helper functions for EVERY TASK that will help us identify the position of
   the cleaner denoted by 'X' by its row and column number in the world
*/
void get_position(char** world, int row_num, int col_num, 
                  int* row_pos, int* col_pos) {
    *row_pos = INVALID_INDEX; // Initialize as invalid
    *col_pos = INVALID_INDEX;
    for (int row = 0; row < row_num; row++) {
        for (int col = 0; col < col_num; col++) {
            if (world[row][col] == CLEANER) {
                *row_pos = row;
                *col_pos = col;
                return; // Exit once found
            }
        }
    }
}

/* main function for task 1 to help us identify the distance from the cleaner 
   (denoted by 'X') to the nearest wall (denoted by 'W') in the world
*/
int distance_to_wall(char** world, int row_num, int col_num) {
    // Firstly get the position of the cleaner 'X' first
    int current_cleaner_row, current_cleaner_col;
    get_position(world, row_num, col_num, 
                 &current_cleaner_row, &current_cleaner_col);

    /* Check if the cleaner was found */
    if (current_cleaner_row == INVALID_INDEX || 
        current_cleaner_col == INVALID_INDEX) {
        return 0; // No cleaner found
    }

    /* Loop through all cells to find walls and calculate their distances */
    int smallest_distance = INT_MAX;
    int wall_count = 0;

    for (int row = 0; row < row_num; row++) {
        for (int col = 0; col < col_num; col++) {
            if (world[row][col] == WALL) {
                // increment wall_count once a wall has been found
                wall_count++;
                // calculate the distance from the current wall to cleaner
                int row_distance = abs(current_cleaner_row - row);
                int col_distance = abs(current_cleaner_col - col);
                int current_distance = row_distance + col_distance;
                // therefore compare it to the current smallest_distance
                if (current_distance < smallest_distance) {
                    smallest_distance = current_distance;
                }
            }
        }
    }

    /* Return 0 if no walls are found, otherwise return the smallest distance */
    if (wall_count == 0) {
        return 0;
    }
    return smallest_distance;
}

/****************************************************************************
                          FUNCTIONS FOR TASK 2
****************************************************************************/
/* helper function for task 2 to identify which will be the new position of 
   the cleaner 'X' if change is made, the new position will be represented by 
   the new row and column number
*/
void get_new_position(int current_row, int current_col, char direction, 
                      int* new_row, int* new_col) {
    int direction_index;
    switch (direction) {
        case LEFT:
            direction_index = LEFT_INDEX;
            break;
        case RIGHT:
            direction_index = RIGHT_INDEX;
            break;
        case UP:
            direction_index = UP_INDEX;
            break;
        case DOWN:
            direction_index = DOWN_INDEX;
            break;
        default:
            *new_row = current_row;
            *new_col = current_col;
            return;
    }
    *new_row = current_row + DIRECTION_OFFSETS[direction_index][ROW_INDEX];
    *new_col = current_col + DIRECTION_OFFSETS[direction_index][COL_INDEX];
}

/* - main function for task 2 to make change to the world by moving the cleaner 
     based on the input direction (one of left, right, up, down)
   - keep the world remained if the direction is blocked by wall or the cleaner  
     is in edge cases that cannot move based on that direction 
*/
void make_move(char** world, int row_num, int col_num, char direction) {
    /* firstly get the position of cleaner X */
    int current_cleaner_row, current_cleaner_col;
    get_position(world, row_num, col_num, 
                 &current_cleaner_row, &current_cleaner_col);
    
    /* therefore find the new position of X if move is conducted */
    int new_cleaner_row, new_cleaner_col;
    get_new_position(current_cleaner_row, current_cleaner_col, direction, 
                     &new_cleaner_row, &new_cleaner_col);

    /* Check boundary conditions FIRST */
    if (new_cleaner_row < 0 || new_cleaner_row >= row_num ||
        new_cleaner_col < 0 || new_cleaner_col >= col_num) {
        return;  // Exit if out of bounds
    }

    /* Only check for wall if we know the position is valid */
    if (world[new_cleaner_row][new_cleaner_col] == WALL) {
        return;
    }
    
    /* otherwise update the world so that the space the cleaner used to be there
       will be EMPTY and the cleaner will come to the new position based on the 
       required direction */
    world[current_cleaner_row][current_cleaner_col] = EMPTY;
    world[new_cleaner_row][new_cleaner_col] = CLEANER;
}

/****************************************************************************
                          FUNCTIONS FOR TASK 3
****************************************************************************/
/* helper function for task 3 to search for the dirt in a particular direction 
   (one of left, right, up, down) and therefore return the position of the dirt 
   if is was found and not be blocked by any wall, otherwise return -1
*/
int find_dirt_position(char **world, DirtSearch_t search, 
                       int row_num, int col_num) {
    // Iterate through positions based on search parameters
    for (int pos = search.start; 
         (search.step > 0) ? (pos < search.end) : (pos >= search.end); 
         pos += search.step) {
        
        // Handle horizontal search (left or right)
        if (search.direction == LEFT || search.direction == RIGHT) {
            // Skip if position is out of bounds
            if (pos < 0 || pos >= col_num) {
                continue;
            }
            // Stop searching if wall encountered
            if (world[search.fixed_pos][pos] == WALL) {
                break;
            }
            // Return position if dirt found
            if (world[search.fixed_pos][pos] == DIRT) {
                return pos;
            }
        } 
        // Handle vertical search (up or down)
        else {
            // Skip if position is out of bounds
            if (pos < 0 || pos >= row_num) {
                continue;
            }
            // Stop searching if wall encountered
            if (world[pos][search.fixed_pos] == WALL) {
                break;
            }
            // Return position if dirt found
            if (world[pos][search.fixed_pos] == DIRT) {
                return pos;
            }
        }
    }
    // Return -1 if no dirt found
    return NOT_FOUND;
}

/* helper function for task 3 to identify the priority of each directions
   direction with highest returned value is the most prioritized direction
*/
int get_priority(char direction) {
    switch(direction) {
        case UP:    return PRIORITY_UP;
        case RIGHT: return PRIORITY_RIGHT;
        case DOWN:  return PRIORITY_DOWN;
        case LEFT:  return PRIORITY_LEFT;
        default:    return PRIORITY_INVALID;
    }
}

/* - main function for task 3 to determine the path for the cleaner 
    (denoted by 'X') to access the nearest dirt (denoted by 'D') that is not 
     blocked by any wall
   - if there are multiple dirts with the same distance to the cleaner, then 
     choose the dirt with the most prioritized direction to the cleaner and 
     return the path of the cleaner to that dirt 
*/
char* path_to_next(char** world, int row_num, int col_num) {
    // Get current position of the cleaner
    int cleaner_row, cleaner_col;
    get_position(world, row_num, col_num, &cleaner_row, &cleaner_col);
    
    // Define search parameters for all four directions
    DirtSearch_t searches[] = {
        // Up search
        {UP,    PRIORITY_UP,    NULL, cleaner_col, 
         cleaner_row - 1, NOT_FOUND, BACKWARD_STEP}, 
        // Right search
        {RIGHT, PRIORITY_RIGHT, NULL, cleaner_row, 
         cleaner_col + 1, col_num,   FORWARD_STEP},  
        // Down search
        {DOWN,  PRIORITY_DOWN,  NULL, cleaner_col, 
         cleaner_row + 1, row_num,   FORWARD_STEP},  
        // Left search
        {LEFT,  PRIORITY_LEFT,  NULL, cleaner_row, 
         cleaner_col - 1, NOT_FOUND, BACKWARD_STEP}  
    };
    
    // Initialize variables for finding closest dirt
    int min_distance = row_num + col_num;
    char final_direction = '\0';
    int selected_distance = 0;

    // Search in all four directions for nearest dirt
    for (int i = 0; i < 4; i++) {
        int dirt_pos = find_dirt_position(world, searches[i], row_num, col_num);
        if (dirt_pos != -1) {
            // Calculate distance to dirt
            int dist;
            if (searches[i].direction == LEFT || searches[i].direction == RIGHT) {
                dist = abs(dirt_pos - cleaner_col);
            } else {
                dist = abs(dirt_pos - cleaner_row);
            }
            
            // Update if this dirt is closer or has higher priority at same distance
            if (dist < min_distance || 
                (dist == min_distance && 
                 searches[i].priority < get_priority(final_direction))) {
                min_distance = dist;
                final_direction = searches[i].direction;
                selected_distance = dist;
            }
        }
    }

    // Return empty string if no dirt found
    if (final_direction == '\0') {
        char* result = (char*)malloc(sizeof(char));
        result[0] = '\0';
        return result;
    }

    // Create string of movements to reach the dirt
    char* result = (char*)malloc(selected_distance + 1);
    memset(result, final_direction, selected_distance);
    result[selected_distance] = '\0';
    
    return result;
}

/****************************************************************************
                          FUNCTIONS FOR TASK 4
****************************************************************************/
/* helper function to create a new node for the input direction for the linked
   list
*/
node_t* new_node(char input_direction) {
    node_t* new = (node_t*)malloc(sizeof(node_t));
    new->direction = input_direction;
    new->next = NULL;
    return new;
}

/* helper function to add a new node for the input direction at the end of the 
   linked list
*/
node_t* add_at_foot(node_t* head, char input_direction) {
    // if the list is empty
    if (head == NULL) {
        node_t* foot = new_node(input_direction);
        return foot;
    }
    
    // setup a pointer to traverse along the linked list until it hits the last node
    node_t* ptr = head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    
    // linked the last element of the current list with the new node for the input direction 
    node_t* foot = new_node(input_direction);
    ptr->next = foot;
    return head;
}

/* helper function to delete the last node out of a list and return the pointer
   to that last node 
*/
node_t* get_and_delete_at_foot(node_t* head) {
    // if the list is empty
    if (head == NULL) {
        return NULL;
    }
    
    // if the list just has one element 
    if (head->next == NULL) {
        node_t* ptr = head;
        head = NULL;
        return ptr;
    }
    
    node_t* ptr = head;
    while (ptr->next->next != NULL) {
        ptr = ptr->next;
    }
    node_t* foot = ptr->next;
    ptr->next = NULL;
    return foot;
}

/* helper function to return the reversed direction of the input direction
*/
char reverse_direction(char input_direction) {
    switch(input_direction) {
        case LEFT: return RIGHT;
        case RIGHT: return LEFT;
        case UP: return DOWN;
        case DOWN: return UP;
        default: return '\0';
    }
}

/* helper function to add the node of the reversed direction of the input 
   direction to a linked list
*/
node_t* add_reverse_at_foot(node_t* head, char input_direction) {
    return add_at_foot(head, reverse_direction(input_direction));
}

/* main function to determines and executes the complete cleaning path for 
   the cleaner, including backtracking when necessary to reach all dirt in the 
   world.
   
   The function:
   1. Moves to the nearest dirt using path_to_next()
   2. Keeps track of movements for backtracking
   3. Backtracks when no direct path to dirt is available
   4. Records all movements in the final output string
 */
char* clean_path(char** world, int row_num, int col_num) {
    // Initialize linked lists for tracking movements
    node_t* track = NULL;        // Stores moves for backtracking
    node_t* output_head = NULL;  // Stores all moves for final output
    
    while (1) {
        // Get directions to nearest dirt
        char* next_directions = path_to_next(world, row_num, col_num);
        
        if (next_directions[0] != '\0') { 
            // If there are directions to move toward dirt
            for (int i = 0; next_directions[i] != '\0'; i++) {
                // Execute each move in the path
                make_move(world, row_num, col_num, next_directions[i]);
                // Add move to output sequence
                output_head = add_at_foot(output_head, next_directions[i]);
                // Add reverse move to tracking list for potential backtracking
                track = add_reverse_at_foot(track, next_directions[i]);
            }
        } else if (track != NULL) { 
            // If no direct path to dirt but backtracking is possible
            // Get last move from tracking list
            node_t* last_move = get_and_delete_at_foot(track);
            if (last_move == NULL || last_move->direction == '\0') {
                break; // No more moves to backtrack
            }
            // Execute backtracking move
            make_move(world, row_num, col_num, last_move->direction);
            // Add backtracking move to output sequence
            output_head = add_at_foot(output_head, last_move->direction);
            free(last_move);
        } else {
            break; // No more dirt and no more moves to backtrack
        }
        // Free the allocated directions string
        free(next_directions);
    }

    // Convert the linked list of moves to a string
    // First, count the length of the list
    int length = 0;
    node_t* temp = output_head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    
    // Allocate memory for the result string
    char* result = (char*)malloc((length + 1) * sizeof(char));
    
    // Copy directions from linked list to string
    temp = output_head;
    for (int i = 0; i < length; i++) {
        result[i] = temp->direction;
        // Free each node as we go
        node_t* to_free = temp;
        temp = temp->next;
        free(to_free);
    }
    result[length] = '\0';  // Null-terminate the string
    
    return result;
}

/****************************************************************************
                HELPER FUNCTIONS FOR TESTING THE OUTPUT 
****************************************************************************/
void print_world(char** world, int row_num, int col_num) {
    for (int row = 0; row < row_num; row++) {
        for (int col = 0; col < col_num; col++) {
            printf("%c ", world[row][col]);
        }
        printf("\n");
    }
}

void run_test_case(char temp_world[3][3], int row_num, int col_num) {
    char** world = (char**)malloc(row_num * sizeof(char*));
    for (int i = 0; i < row_num; i++) {
        world[i] = (char*)malloc(col_num * sizeof(char));
    }
    
    for (int row = 0; row < row_num; row++) {
        for (int col = 0; col < col_num; col++) {
            world[row][col] = temp_world[row][col];
        }
    }

    printf("Initial World:\n");
    print_world(world, row_num, col_num);
    char* path = clean_path(world, row_num, col_num);
    printf("Path to clean all dirt: %s\n\n", path);
    free(path);

    // Free allocated memory
    for (int i = 0; i < row_num; i++) {
        free(world[i]);
    }
    free(world);
}

/****************************************************************************
                                THE END 
****************************************************************************/
