import enum
import random
from dataclasses import dataclass


class MoveState(enum.Enum):
    PLAYER_MOVE = 1
    COMPUTER_MOVE = 2


class Cell(enum.Enum):
    EMPTY = 0
    X = 1
    O = 2


@dataclass
class CalculatedMove:
    def __init__(self, index, score):
        self.index = index
        self.score = score


DISPLAY_EMPTY = '  '
DISPLAY_X = 'XX'
DISPLAY_O = 'OO'
DISPLAY_UNKNOWN = '??'
BOARD_SIDE_SIZE = 3
BOARD_SIZE = BOARD_SIDE_SIZE * BOARD_SIDE_SIZE


def get_cell_display(cell):
    if Cell.EMPTY == cell:
        return DISPLAY_EMPTY
    if Cell.X == cell:
        return DISPLAY_X
    if Cell.O == cell:
        return DISPLAY_O
    return DISPLAY_UNKNOWN


def get_index(coordinate):
    return int(coordinate[1]*BOARD_SIDE_SIZE + coordinate[0])


def get_coordinate(index):
    return (int(index % BOARD_SIDE_SIZE), int(index/BOARD_SIDE_SIZE))


def get_available_indexes(board):
    return [i for i, cell in enumerate(board) if cell == Cell.EMPTY]


def toggle_cell(current_cell):
    return Cell.O if current_cell == Cell.X else Cell.X


def create_empty_board():
    return [Cell.EMPTY] * BOARD_SIZE


def put_move_board(board, index, current_cell):
    board[index] = current_cell


def print_board(board):
    table_length = BOARD_SIDE_SIZE * 3 + 1
    table_horizontal_line = '-' * table_length
    space = '   '
    board_display = [get_cell_display(cell) for cell in board]
    row_break = table_horizontal_line + space + table_horizontal_line
    print(row_break)
    for y_position in range(BOARD_SIDE_SIZE):
        guide_string = '|'.join([f'{index:2d}' for index in range(
            y_position * BOARD_SIDE_SIZE, (y_position + 1) * BOARD_SIDE_SIZE)])
        board_string = '|'.join(
            board_display[y_position*BOARD_SIDE_SIZE: (y_position+1)*BOARD_SIDE_SIZE])
        print(f'|{guide_string}|{space}|{board_string}|')
        print(row_break)


def is_a_row_win(board, index, current_cell):
    coordinate = get_coordinate(index)
    is_winning = True
    for x_position in range(BOARD_SIDE_SIZE):
        if current_cell != board[get_index((x_position, coordinate[1]))]:
            is_winning = False
            break
    return is_winning


def is_a_column_win(board, index, current_cell):
    coordinate = get_coordinate(index)
    is_winning = True
    for y_position in range(BOARD_SIDE_SIZE):
        if current_cell != board[get_index((coordinate[0], y_position))]:
            is_winning = False
            break
    return is_winning


def is_a_diagonal_positive_slope_win(board, index, current_cell):
    coordinate = get_coordinate(index)
    x_position, y_position = coordinate
    distance_to_corner = min(x_position, y_position)
    x_position -= distance_to_corner
    y_position -= distance_to_corner
    if (x_position, y_position) == (0, 0):
        is_winning = True
        while x_position < BOARD_SIDE_SIZE and y_position < BOARD_SIDE_SIZE:
            if current_cell != board[get_index((x_position, y_position))]:
                is_winning = False
                break
            x_position += 1
            y_position += 1
    else:
        is_winning = False
    return is_winning


def is_a_diagonal_negative_slope_win(board, index, current_cell):
    coordinate = get_coordinate(index)
    last_index = BOARD_SIDE_SIZE-1
    x_position, y_position = coordinate
    distance_to_corner = min(x_position, last_index-y_position)
    x_position -= distance_to_corner
    y_position += distance_to_corner
    if (x_position, y_position) == (0, last_index):
        is_winning = True
        while x_position < BOARD_SIDE_SIZE and y_position >= 0:
            if current_cell != board[get_index((x_position, y_position))]:
                is_winning = False
                break
            x_position += 1
            y_position -= 1
    else:
        is_winning = False
    return is_winning


def is_a_win(board, index, current_cell):
    return (is_a_row_win(board, index, current_cell)
            or is_a_column_win(board, index, current_cell)
            or is_a_diagonal_positive_slope_win(board, index, current_cell)
            or is_a_diagonal_negative_slope_win(board, index, current_cell))


def is_a_draw(board):
    return len(get_available_indexes(board)) == 0


def is_first_move(board):
    return board == create_empty_board()


def get_player_input(board):
    is_valid = False
    while not is_valid:
        try:
            index = int(input('Your move, input index: '))
            if index < 0 or index >= BOARD_SIZE:
                raise ValueError
            if board[index] != Cell.EMPTY:
                raise ValueError
            is_valid = True
        except ValueError:
            print('Dont waste my time.')
    return index


# scores is defined as number_of_empty+1 (positive if winning, negative if losing)
# check minimax algorithm for clarification (https://en.wikipedia.org/wiki/Minimax)
def get_best_calculated_move(board, cell, depth):
    if depth == 0:
        # just put a random move
        return CalculatedMove(get_random_index(board), 0)
    calculated_moves = []
    available_indexes = get_available_indexes(board)
    for index_to_analyze in available_indexes:
        board_to_analyze = board.copy()
        put_move_board(board_to_analyze, index_to_analyze, cell)
        number_of_empty_cells = len(
            get_available_indexes(board_to_analyze))
        if is_a_win(board_to_analyze, index_to_analyze, cell):  # win
            # quick exit if there is a win
            # CalculatedMoves.append(CalculatedMove(index_to_analyze, number_of_empty_cells+1))
            return CalculatedMove(index_to_analyze, number_of_empty_cells+1)
        if number_of_empty_cells == 0:  # draw
            calculated_moves.append(CalculatedMove(index_to_analyze, 0))
        else:
            opponent_move = get_best_calculated_move(
                board_to_analyze, toggle_cell(cell), depth-1)
            calculated_moves.append(CalculatedMove(
                index_to_analyze, -1*opponent_move.score))
    best_move = max(calculated_moves,
                    key=lambda CalculatedMove: CalculatedMove.score)
    return best_move


def get_best_index(board, cell):
    if is_first_move(board):
        return get_random_index(board)
    # -1 depth means unlimited depth
    return get_best_calculated_move(board, cell, -1).index


def get_random_index(board):
    return random.choice(get_available_indexes(board))


def play_tic_tac_toe():
    current_cell = Cell.O
    state = MoveState.COMPUTER_MOVE
    main_board = create_empty_board()
    print('Game start')
    print_board(main_board)
    while True:
        if state == MoveState.PLAYER_MOVE:
            print('Player to move')
            index = get_player_input(main_board)
            put_move_board(main_board, index, current_cell)
        elif state == MoveState.COMPUTER_MOVE:
            print('Computer to move')
            index = get_best_index(main_board, current_cell)  # smart AI
            # index = get_random_index(main_board)  # stupid AI
            print('The computer moved at index:', index)
            put_move_board(main_board, index, current_cell)

        print_board(main_board)

        if is_a_win(main_board, index, current_cell):
            if state == MoveState.PLAYER_MOVE:
                print('You win')
            elif state == MoveState.COMPUTER_MOVE:
                print('You lose')
            break
        if is_a_draw(main_board):
            print('Draw')
            break
        state = MoveState.PLAYER_MOVE if state == MoveState.COMPUTER_MOVE else MoveState.COMPUTER_MOVE
        current_cell = toggle_cell(current_cell)


if __name__ == '__main__':  # good practice :)
    play_tic_tac_toe()
