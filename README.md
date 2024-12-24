# VACUUMINATOR NAVIGATION SYSTEM
## Project Background
Originally a Python university assignment for autonomous robot navigation, reimplemented in C to enhance:
- Dynamic memory management
- Pointer manipulation
- Linked list data structures
- Algorithm optimization in a lower-level language

## Core Components

### TASK 1. DISTANCE TO WALL
```
int distance_to_wall(char** world, int rows, int cols);
```
- Calculate the distance from the robot (denoted by 'X') to the nearest
  wall (denoted by 'W') in the world
- Remember that the robot can just move in four directions
  (one of LEFT, RIGHT, UP, DOWN)
  
### TASK 2. MOVEMENT HANDLER
```
char** make_move(char** world, int rows, int cols, char direction);
```
Executes robot movement with collision detection:
- Handles directions: 'u'(up), 'd'(down), 'l'(left), 'r'(right)
- Validates against boundaries and walls
- Returns updated world state
- Maintains original state if move is invalid

### TASK 3. DIRT DETECTION
```
char* path_to_next(char** world, int rows, int cols);
```
Generate the path from the current position of robot (denoted by 'X')
to the most prioritized dirt (denoted by 'X'). The priority is based on these 
two criterias: 
- Firstly, the dirt that further away from the robot is less prioritized
- Secondly, if there are multiple dirts with same distance to the robot,
  then choose the one with highest direction priority. The priority direction is
  based on this order: UP > RIGHT > DOWN > LEFT (remember that this is the direction
  from THE ROBOT to THE DIRT)
- Finally, remember that the robot will just scan in the four direction (UP, RIGHT, DOWN, LEFT)
  and if the robot cannot scan any of dirt in these 4 directions, then the function should
  return nothing

### TASK 4. CLEANING PATH GENERATOR
```
char* clean_path(char** world, int rows, int cols);
```
Generate the full path for the robot to clean the dirts and coming back to the starting position
based on this process
- Use the function of task 3 to find the path to the next dirt
- In case after cleaning one dirt, we cannot find any available dirt in 4 directions, then backtracking
  the path the robot used to travel until it is in the position that any dirt is available
- Then repeat this process until the robot successfully coming back to the starting position
- Return the full path that the robot has to travel 
Note these things
- In some cases, after travelling the whole path, the robot might not clean all of the dirts in
  the map as the purpose of this task is to guide student to implement a kind of backtracking solutions
- And the path that the robot travel might not be the shortest, if you guys want to see something optimal
  then read my optimal_cleaner_bot for more fun and interesting  

## Technical Implementation

### Data Structures
- **Linked Lists**: Path storage and backtracking
- **Dynamic Arrays**: World grid representation
- **Custom Memory Management**: Manual allocation/deallocation

### World Representation
- `X`: Vacuuminator position
- `W`: Wall
- `D`: Dirt
- `E`: Empty space

## How to Use

### Setup
```bash
gcc -o vacuuminator main.c vacuum_functions.c -Wall
```

### Testing Functions
1. Create test world using `create_world()`
2. Initialize with test cases ('X', 'W', 'D', 'E')
3. Call desired function with parameters
4. Free memory with `free_world()` and `free()`

Memory leak detection:
```bash
valgrind --leak-check=full ./vacuuminator
```

## Memory Management
Important memory handling:
```
free_world(world, rows);
free(path);
```

## Development Notes
Implementation emphasizes:
- Code efficiency
- Memory optimization
- Data structure design
- Algorithm performance
