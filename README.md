# VACUUMINATOR NAVIGATION SYSTEM
## Project Background
Originally a Python assignment for robot navigation, reimplemented in C for improved memory management, pointer manipulation, linked list data structures, and algorithm optimization. I have provided both the Python solution and the C solution for this project. Remember that the description in the file `Task Description.md` is for Python assignment, not for C assignment.

There are two solutions: one in Python (`Project_1.py`) from when I just started learning to code and one in C (`Project_1.c`), when i has more experience with coding. Therefore, it can be easily witnessed the difference between these two version's performances.

## Documentation
For detailed descriptions, examples, and task breakdowns, refer to `Task Description.md`.

## Core Components

### TASK 1: DISTANCE TO WALL
Calculates the distance from the robot ('X') to the nearest wall ('W').

### TASK 2: MOVEMENT HANDLER
Executes robot movement with collision detection, handles directions 'u'(up), 'd'(down), 'l'(left), 'r'(right), and updates world state.

### TASK 3: DIRT DETECTION
Generates the path from the robot to the most prioritized dirt ('D'), with priorities based on distance and direction.

### TASK 4: CLEANING PATH GENERATOR
Generates the full cleaning path for the robot, including backtracking if necessary, and returns the path to clean all accessible dirt.

### OPTIMAL CLEANER (BONUS)
If you have done all of the above tasks, you might perceive that the current solutions for cleaning all of the dirts in the world still has some restrictions. Now if you want more challenge, creates a function `optimal_vacuuminator(world)` that returns a list of moves to clean all the dirt in the world in the fewest moves possible. If the Vacuuminator is unable to clean all dirt, it returns `None`. Assumes the world is less than 6 tiles in width and length. If you want to see the C version for this problem's solution, then refers to [The-Optimal_Cleaner-Robot](https://2024s1-comp10001-d7ccc59f4734fd6399530ec2572d0fddd929b27d8ca441.pages.gitlab.unimelb.edu.au/)

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


