Note that this is the Python description for the tasks in the assignment Project. There are four tasks in total, however if you guys want to see the optimal solution for the problem, then refers to 

### TASK 1: DISTANCE TO THE NEAREST WALL (3 marks)
The Vacuuminator needs to figure out how far it needs to travel to reach the nearest wall.

Write a function `distance_to_wall(world)` that returns an integer representing the smallest number of moves the Vacuuminator can make before hitting a wall. If there are no walls present, it should return `None`.

**Hint**: Calculate the number of moves by using the rows and columns between the Vacuuminator and the wall.

### Example Calls:
```python
>>> distance_to_wall([['D', 'W'], ['X', 'E']])
2

>>> distance_to_wall([['W', 'E'], ['X', 'E']])
1

>>> distance_to_wall([['D', 'D'], ['D', 'D'], ['W', 'W'], ['D', 'E'], ['W', 'E'], ['E', 'D'], ['E', 'X']])
3
```

### TASK 2: MAKING A MOVE (3 marks)
We now need to allow the Vacuuminator to move around the world. Write a function `make_move(world, direction)`. The direction may be one of 'u', 'd', 'l', or 'r' as described on the Background slide. Your function should return a list of lists representing the world after the move has been made.

Note that a move may not be possible either because:
- It would take the Vacuuminator off the edge of the world.
- It would take the Vacuuminator into a wall.

If an impossible move is requested, the Vacuuminator should not attempt to make it and should instead return the current state of the world.

### Example Calls:
```python
>>> make_move([['E', 'W'], ['E', 'X']], 'l')
[['E', 'W'], ['X', 'E']]

>>> make_move([['E', 'W'], ['E', 'X']], 'r')
[['E', 'W'], ['E', 'X']]

>>> make_move([['E', 'W'], ['E', 'X']], 'u')
[['E', 'W'], ['E', 'X']]
```

### TASK 3: FINDING DIRT (4 marks)
In the previous questions, we assumed the Vacuuminator had perfect knowledge of the world around it. In practice, mobile robots need to rely on sensors to find out information about the world. In this question, we assume that the Vacuuminator has exactly four sensors:

- A 'left sensor' which will identify the nearest dirty square immediately to the left of the Vacuuminator (i.e., in the same row with a lower index position).
- A 'right sensor' which will identify the nearest dirty square immediately to the right of the Vacuuminator (i.e., in the same row with a higher index position).
- An 'up sensor' which will identify the nearest dirty square immediately above the Vacuuminator (i.e., in the same column with a lower index position).
- A 'down sensor' which will identify the nearest dirty square immediately below the Vacuuminator (i.e., in the same column with a higher index position).

The Vacuuminator's sensors are unable to penetrate walls, i.e., dirt on the opposite side of a wall will not be detected. The Vacuuminator is also unable to identify dirt that its sensors can't see (e.g., dirt that is diagonal to its current position).

Write a function `path_to_next(world)` that will identify the nearest piece of dirt detected using the Vacuuminator's sensors. Your function should return a list containing the moves required for the Vacuuminator to reach that piece of dirt from its current position.

In the event that there are multiple pieces of dirt that are at an equal distance from the Vacuuminator, they should be prioritized in the following order:
- Highest Priority: Dirt above the Vacuuminator
- Second Priority: Dirt to the right of the Vacuuminator
- Third Priority: Dirt below the Vacuuminator
- Lowest Priority: Dirt to the left of the Vacuuminator

The Vacuuminator stays at its position when scanning, then goes straight to the nearest target dirt (which is directly at up, right, down, or left directions from the Vacuuminator’s current position, and the target may be one or more unit distances further away).

If no dirt can be detected, your function should return an empty list.

### Example Calls:
```python
>>> print(path_to_next([['E', 'D'], ['E', 'X']]))
['u']

>>> print(path_to_next([['E', 'D'], ['E', 'E'], ['E', 'X']]))
['u', 'u']

>>> print(path_to_next([['D', 'E'], ['E', 'X']]))
[]
```

### TASK 4: CLEANING ALL THE DIRT LOCATED (5 marks)
We now wish to produce a sequence of moves to clean all the dirt the Vacuuminator can find, and then return the Vacuuminator to its starting position. The Vacuuminator should repeatedly scan for and clean up dirt found from its current position according to the rules in Task 3. It should continue to do so as long as it finds new dirt from its current position. We will call this a cleaning cycle.

Once the Vacuuminator is no longer able to find any new dirt, it should backtrack along its path, scanning for new dirt at each square. If it finds any new dirt in its scan, it should begin a new cleaning cycle, starting with this dirt.

The Vacuuminator should continue until it has backtracked through every move it has made and found no more dirt, scanning and cleaning as it goes. Note that once the Vacuuminator has selected a patch of dirt to clean, it will not scan for any new dirt until that patch has been cleaned. Scanning for new dirt will only happen while the Vacuuminator is backtracking.

Write a function `clean_path(world)`. This function should return a list of moves that the Vacuuminator will use to clean the world according to the rules above.

A working version of the Task 3 `path_to_next(world)` function is provided to help you with this task.

### Example Calls:
```python
>>> clean_path([['E', 'D'], ['E', 'E'], ['E', 'X']])
['u', 'u', 'd', 'd']

>>> clean_path([['D', 'D'], ['E', 'E'], ['E', 'X']])
['u', 'u', 'l', 'r', 'd', 'd']

>>> clean_path([['E', 'D', 'E'], ['X', 'D', 'D'], ['E', 'E', 'E']])
['r', 'u', 'd', 'r', 'l', 'l']

>>> clean_path([['E', 'D', 'E'], ['X', 'D', 'E'], ['E', 'D', 'E']])
['r', 'u', 'd', 'd', 'u', 'u', 'd', 'l']

>>> clean_path([['E', 'D', 'D'], ['D', 'E', 'E'], ['D', 'E', 'X']])
['u', 'u', 'l', 'r', 'd', 'l', 'l', 'd', 'u', 'r', 'r', 'd']

