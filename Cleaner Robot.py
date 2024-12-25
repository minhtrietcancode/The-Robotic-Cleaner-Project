DIR_UP = "u"
DIR_DOWN = "d"
DIR_LEFT = "l"
DIR_RIGHT = "r"

/****************************************************************************
                                  TASK 1
****************************************************************************/
# Getting position of cell based on row and column
def get_position(cell, world):
    for row in range(len(world)): 
        for col in range(len(world[0])):
            if world[row][col] == cell:
                return row, col
            
def distance_to_wall(world):
    """ 
    Function: 
        - Calculate the minimum distance from position 'X' to any wall 
          ('W') in the given grid-based world.

    Args:
        - world (List[List[str]]): A 2D matrix representing the world, 
          with 'X' representing the vacuum cleaner and 'W' representing walls.
        
    Logic:
        - Calculating the distance between "X" and "D" based on their
          row distance and column distance 

    Returns:
        - int or None: The distance from the vacuum cleaner to the nearest wall 
        - Returns None if there are no walls in the world.
    """
    # If there is no wall
    if all(cell != "W" for row in world for cell in row):
        return None 
    
    # Getting position of "X"
    x_row, x_col = get_position("X", world)
    
    # Finding the distance of the vacuum cleaner to the nearest wall
    min_distance = float('inf')  # Setting min_distance to a large number
    for row in range(len(world)):
        for col in range(len(world[0])): 
            if world[row][col] == "W":
                distance = abs(x_row - row) + abs(x_col - col)
                if distance < min_distance:
                    min_distance = distance
                
    return min_distance

/****************************************************************************
                                  TASK 2
****************************************************************************/
def make_move(world, direction):
    """ 
    Function: 
        - Moves the position of "X" in the given grid-based world according to 
          the specified direction.

    Args:
        - world (List[List[str]]): A 2D matrix representing the world, 
          where "X" denotes the vacuum cleaner.
        - direction (str): The direction in which to move the vacuum cleaner. 
          Should be one of: "up", "down", "left", "right".

    Returns:
        - List[List[str]]: The updated world matrix after moving "X" in the 
          specified direction.

    Note:
        - "X" cannot move off the edges of the world.
        - If there's a wall ('W') blocking the movement in the 
          specified direction, "X" will not move.
    """
    # The case "X" cannot move off the edges
    if direction == DIR_UP: 
        # If "X" is in the top row, it cannot move up
        if any("X" in row for row in world[0]):
            return world
    elif direction == DIR_DOWN:
        # If "X" is in the bottom row, it cannot move down
        if any("X" in row for row in world[-1]):
            return world
    elif direction == DIR_LEFT:
        # If "X" is in the leftmost column, it cannot move left
        if any(row[0] == "X" for row in world):
            return world
    elif direction == DIR_RIGHT:
        # If "X" is in the rightmost column, it cannot move right
        if any(row[-1] == "X" for row in world):
            return world

    # Get the position of "X"
    row_x, col_x = get_position("X", world)

    # Move "X" based on the direction 
    if direction == DIR_UP and row_x > 0 and world[row_x - 1][col_x] != "W":
        # Moving up "X"
        swap = world[row_x][col_x]
        world[row_x][col_x] = world[row_x - 1][col_x]
        world[row_x - 1][col_x] = swap
    
    elif direction == DIR_DOWN and row_x < len(world) - 1 \
        and world[row_x + 1][col_x] != "W":
        # Moving down "X"
        swap = world[row_x][col_x]
        world[row_x][col_x] = world[row_x + 1][col_x]
        world[row_x + 1][col_x] = swap
    
    elif direction == DIR_LEFT and col_x > 0 \
        and world[row_x][col_x - 1] != "W":
        # Moving left "X"
        swap = world[row_x][col_x]
        world[row_x][col_x] = world[row_x][col_x - 1]
        world[row_x][col_x - 1] = swap
    
    elif direction == DIR_RIGHT and col_x < len(world[0]) - 1 \
        and world[row_x][col_x + 1] != "W":
        # Moving right "X"
        swap = world[row_x][col_x]
        world[row_x][col_x] = world[row_x][col_x + 1]
        world[row_x][col_x + 1] = swap

    return world
  
/****************************************************************************
                                  TASK 3
****************************************************************************/
def path_to_next(world):
    """
    Function:
        - Finds the shortest path from the vacuum cleaner ("X") to the nearest 
          dirt ("D") in the given world.

    Args:
        - world (List[List[str]]): A 2D matrix representing the world.
        
    Logic:
        - Collects all possible paths from the vacuum cleaner ("X") 
          to each dirt ("D") into a single list.
        - Sorts the list of paths based on their length and direction priority.
        
    Returns:
        - List[str]: A list of directions representing the shortest path to 
          reach the nearest dirt from the vacuum cleaner. 
        - Returns an empty list if no path is available.        
    """
    # Getting the position of "X"
    row_x, col_x = get_position("X", world)
    
    # List to store all possible paths to reach each "D" (dirt)  
    possible_path = []
    
    # Iterating through each cell in the world
    for row in range(len(world)):
        for col in range(len(world[0])):            
            # The case "D" is to the right or left of "X"
            if world[row][col] == "D" and row == row_x:  # In the same row               
                # Getting distance between the column of "X" and "D" 
                col_distance = abs(col_x - col)  
                # "D" is to the left of "X" and there are no walls between 
                if col < col_x and "W" not in world[row][col:(col_x + 1)]: 
                    possible_path.append([DIR_LEFT] * col_distance)                     
                # "D" is to the right of "X" and there are no walls between 
                if col > col_x and "W" not in world[row][col_x:(col + 1)]:  
                    possible_path.append([DIR_RIGHT] * col_distance) 
                    
            # The case "D" is above or below "X"
            if world[row][col] == "D" and col == col_x:  # In the same column                
                # Getting distance between the row of "X" and "D"
                row_distance = abs(row_x - row)                 
                # "D" is above "X" and there are no walls between 
                if (row_x > row and "W" not in [world[between][col] 
                    for between in range(row + 1, row_x)]): 
                    possible_path.append([DIR_UP] * row_distance)                     
                # "D" is below "X" and there are no walls between 
                if (row_x < row and "W" not in [world[between][col] 
                    for between in range(row_x + 1, row)]):  
                    possible_path.append([DIR_DOWN] * row_distance) 
                
    # The case when there is no available path to the dirt
    if not possible_path:
        return []

    # Define a dictionary to map directions to their priority levels
    priority = {"u": 0, "r": 1, "d": 2, "l": 3}
    
    # Sorting the list of paths based on its length and direction priority
    possible_path.sort(key=lambda path: (len(path), priority[path[0]]))
                    
    return possible_path[0]
  
/****************************************************************************
                                  TASK 4
****************************************************************************/
# Updating make_move to replace "D" with "E" as Vacuuminator passes through
def make_move(world, direction):
    # The case "X" cannot move off the edges
    if direction == DIR_UP: 
        # If "X" is in the top row, it cannot move up
        if any("X" in row for row in world[0]):
            return world
    elif direction == DIR_DOWN:
        # If "X" is in the bottom row, it cannot move down
        if any("X" in row for row in world[-1]):
            return world
    elif direction == DIR_LEFT:
        # If "X" is in the leftmost column, it cannot move left
        if any(row[0] == "X" for row in world):
            return world
    elif direction == DIR_RIGHT:
        # If "X" is in the rightmost column, it cannot move right
        if any(row[-1] == "X" for row in world):
            return world
        
    # Get the position of X
    row_x, col_x = get_position("X", world)
    
    # Move "X" based on the direction 
    if (direction == DIR_UP and row_x > 0 
        and world[row_x - 1][col_x] != "W"):
        # Moving up "X"
        if world[row_x - 1][col_x] == "D":  # If there's "D" (dirt)
            # Move "X" to that position and replace dirt with an empty space
            world[row_x - 1][col_x] = "X"
            world[row_x][col_x] = "E"
        else:
            # Otherwise, swap "X" with the cell above it
            swap = world[row_x][col_x]
            world[row_x][col_x] = world[row_x - 1][col_x]
            world[row_x - 1][col_x] = swap
        
    elif direction == DIR_DOWN and row_x < len(world) - 1 \
        and world[row_x + 1][col_x] != "W":
        # Moving down "X"
        if world[row_x + 1][col_x] == "D":  # If there's "D" (dirt)
            # Move "X" to that position and replace dirt with an empty space
            world[row_x + 1][col_x] = "X"
            world[row_x][col_x] = "E"
        else:
            # Otherwise, swap "X" with the cell below it
            swap = world[row_x][col_x]
            world[row_x][col_x] = world[row_x + 1][col_x]
            world[row_x + 1][col_x] = swap
        
    elif direction == DIR_LEFT and col_x > 0 \
        and world[row_x][col_x - 1] != "W":
        # Moving left "X"
        if world[row_x][col_x - 1] == "D":  # If there's "D" (dirt)
            # Move "X" to that position and replace dirt with an empty space
            world[row_x][col_x - 1] = "X"
            world[row_x][col_x] = "E"
        else:
            # Otherwise, swap "X" with the cell to its left
            swap = world[row_x][col_x]
            world[row_x][col_x] = world[row_x][col_x - 1]
            world[row_x][col_x - 1] = swap
        
    elif direction == DIR_RIGHT and col_x < len(world[0]) - 1 \
        and world[row_x][col_x + 1] != "W":
        # Moving right "X"
        if world[row_x][col_x + 1] == "D":  # If there's "D" (dirt)
            # Move "X" to that position and replace dirt with an empty space
            world[row_x][col_x + 1] = "X"
            world[row_x][col_x] = "E"
        else:
            # Otherwise, swap "X" with the cell to its right
            swap = world[row_x][col_x]
            world[row_x][col_x] = world[row_x][col_x + 1]
            world[row_x][col_x + 1] = swap

    return world



def clean_path(world):  
    """
    Function:
        - Cleans the dirt ('D') from the given grid-based world using a vacuum 
          cleaner represented by 'X'.

    Args:
        - world (List[List[str]]): A 2D matrix representing the world, with 'X' 
          representing the vacuum cleaner and 'D' representing dirt.
        
    Logic:
        - Iterates through the world to find the nearest dirt ('D') and 
          moves the vacuum cleaner ('X') towards it.
        - Tracks the movements in a stack to backtrack when no dirt is nearby.
        - Continues cleaning until all dirt is removed from the world.
        
    Returns:
        - List[str]: A list of directions representing the movements of the 
          vacuum cleaner to clean all dirt from the world.  
    """
    # Dictionary to reverse directions
    reverse_dict = {"l": "r", "r": "l", "u": "d", "d": "u"}
    
    # Stack to track back movements
    track = []
    
    # List to store all of the moves
    output = []
    
    # Continuously move towards the nearest dirt until all dirt is cleaned
    while True:
        # Check the next directions towards the nearest dirt
        next_directions = path_to_next(world)
    
        if next_directions:
            # Move according to the next direction towards the nearest dirt
            for direction in next_directions:
                # Record the current direction in the output list
                output.append(direction)
                # Move according to the current direction
                make_move(world, direction)
                # Record the reverse direction for potential backtracking
                track.append(reverse_dict[direction])
            
        elif track:  # Check if there's any track to backtrack 
            # Backtrack to the previous position if no dirt nearby
            previous_move = track.pop()
            # Move to the previous position
            make_move(world, previous_move)
            # Record the backtrack move in the output list
            output.append(previous_move)
        
        else:
            # Exit the loop when all dirt is cleaned 
            break
            
    return output    

/****************************************************************************
                                THE END
****************************************************************************/
