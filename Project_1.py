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

    
    
