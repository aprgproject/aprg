import random


CELL_HIDDEN_SPACE = -1
CELL_HIDDEN_BOMB = -2
CELL_REVEALED_BOMB = -3


GRID_LENGTH = 10
GRID_WIDTH = 5
GRID_SIZE = GRID_LENGTH * GRID_WIDTH
NUMBER_OF_BOMBS = int(GRID_SIZE*0.1)


def get_index(coordinate):
    return int(coordinate[1]*GRID_LENGTH + coordinate[0])


def is_hidden(cell):
    return cell in (CELL_HIDDEN_BOMB, CELL_HIDDEN_SPACE)


def is_revealed(cell):
    return CELL_REVEALED_BOMB == cell or cell >= 0


def is_a_bomb(cell):
    return cell in (CELL_HIDDEN_BOMB, CELL_REVEALED_BOMB)


def is_within_grid(coordinate):
    return coordinate[0] >= 0 and coordinate[0] < GRID_LENGTH and coordinate[1] >= 0 and coordinate[1] < GRID_WIDTH


def are_all_spaces_revealed(grid):
    return all(CELL_HIDDEN_SPACE != cell for cell in grid)


def create_empty_grid():
    return [CELL_HIDDEN_SPACE] * GRID_SIZE


def create_grid_with_bombs():
    grid = create_empty_grid()
    for _ in range(NUMBER_OF_BOMBS):
        bomb_index = random.randrange(0, len(grid))
        grid[bomb_index] = CELL_HIDDEN_BOMB
    return grid


def get_cell_display_with_hidden(cell):
    if CELL_HIDDEN_SPACE == cell:
        return '?'
    if CELL_HIDDEN_BOMB == cell:
        return '?'
    if CELL_REVEALED_BOMB == cell:
        return '*'
    if 0 == cell:
        return ' '
    return str(cell)


def get_cell_display_with_reveal(cell):
    if CELL_HIDDEN_SPACE == cell:
        return ' '
    if CELL_HIDDEN_BOMB == cell:
        return '*'
    if CELL_REVEALED_BOMB == cell:
        return '*'
    if 0 == cell:
        return ' '
    return str(cell)


def print_grid(grid, display_function):
    horizontal_line = '-' * (GRID_LENGTH*4+1)
    board_display = [display_function(cell) for cell in grid]
    print(horizontal_line)
    for y_position in range(GRID_WIDTH):
        grid_string = ' | '.join(
            board_display[y_position*GRID_LENGTH: (y_position+1)*GRID_LENGTH])
        print(f'| {grid_string} |')
        print(horizontal_line)


def get_adjacent_coordinates(coordinate):
    return [
        (coordinate[0]-1, coordinate[1]-1),
        (coordinate[0], coordinate[1]-1),
        (coordinate[0]+1, coordinate[1]-1),
        (coordinate[0]-1, coordinate[1]),
        (coordinate[0]+1, coordinate[1]),
        (coordinate[0]-1, coordinate[1]+1),
        (coordinate[0], coordinate[1]+1),
        (coordinate[0]+1, coordinate[1]+1),
    ]


def get_number_of_adjacent_bombs(grid, coordinate):
    result = 0
    for adjacent in get_adjacent_coordinates(coordinate):
        if is_within_grid(adjacent):
            if is_a_bomb(grid[get_index(adjacent)]):
                result += 1
    return result


def sweep(grid, coordinate):
    if is_within_grid(coordinate):
        index = get_index(coordinate)
        cell = grid[index]
        if is_hidden(cell):
            if is_a_bomb(cell):
                grid[index] = CELL_REVEALED_BOMB
            else:
                adjacent_bombs = get_number_of_adjacent_bombs(grid, coordinate)
                grid[index] = adjacent_bombs
                if adjacent_bombs == 0:
                    for adjacent in get_adjacent_coordinates(coordinate):
                        sweep(grid, adjacent)


def get_player_input(grid):
    is_valid = False
    while not is_valid:
        try:
            inputs_string = input('Input a coordinate to sweep: ')
            inputs = [int(input_string)
                      for input_string in inputs_string.split(',')]
            if len(inputs) == 2:
                if not is_within_grid(inputs):
                    raise ValueError
                if is_revealed(grid[get_index(inputs)]):
                    raise ValueError
                is_valid = True
            else:
                raise ValueError
        except ValueError:
            print('Dont waste my time.')
    return tuple(inputs)


def play_mine_sweeper():
    grid = create_grid_with_bombs()
    while True:
        print_grid(grid, get_cell_display_with_hidden)
        coordinate = get_player_input(grid)
        index = get_index(coordinate)
        if is_a_bomb(grid[index]):
            print('The bomb exploded on you. Game Over!')
            print_grid(grid, get_cell_display_with_reveal)
            break
        sweep(grid, coordinate)
        if are_all_spaces_revealed(grid):
            print('You win!')
            print_grid(grid, get_cell_display_with_reveal)
            break


if __name__ == '__main__':  # good practice :)
    play_mine_sweeper()
