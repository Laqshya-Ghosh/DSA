#include <stdio.h>

/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
enum {
    EMPTY = 0,
    RED,
    BLUE,
};

typedef char board_t[4][5];
typedef char player_t;

typedef struct {
    int col;
    int score;
} move_t;

void copy(board_t * temp, board_t board) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      (*temp)[i][j] = board[i][j];
    }
  }
}

int has_won(board_t board, player_t player)
{
  for (int i = 0; i < 4; i++) {
    if ((board[i][0] == player) && (board[i][1] == player) && (board[i][2] == player) && (board[i][3] == player)) {
      return 1;
    }
    if ((board[i][1] == player) && (board[i][2] == player) && (board[i][3] == player) && (board[i][4] == player)) {
      return 1;
    }
  }
  for (int j = 0; j < 5; j++) {
    if ((board[0][j] == player) && (board[1][j] == player) && (board[2][j] == player) && (board[3][j] == player)) {
      return 1;
    }
  }
  if ((board[0][0] == player) && (board[1][1] == player) && (board[2][2] == player) && (board[3][3] == player)) {
    return 1;
  }
  if ((board[0][1] == player) && (board[0][2] == player) && (board[0][3] == player) && (board[0][4] == player)) {
    return 1;
  }
  if ((board[3][0] == player) && (board[2][1] == player) && (board[1][2] == player) && (board[0][3] == player)) {
    return 1;
  }
  if ((board[3][1] == player) && (board[2][2] == player) && (board[1][3] == player) && (board[0][4] == player)) {
    return 1;
  }
  return 0;
}

int is_full(board_t board)
{
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      if (board[i][j] == EMPTY) {
        return 0;
      }
    }
  }
  return 1;
}

// int ord(board_t board)
// {
//     int p = 1;
//     int i = 0;
//     int d;

//     for (int row = 0; row < 4; ++row) {
//         for (int col = 0; col < 5; ++col) {
//             switch (board[row][col]) {
//             case 'R': d = 1; break;
//             case 'B': d = 2; break;
//             case '.': d = 0; break;
//             }
//             i += d * p;
//             p *= 3;
//         }
//     }

//     return i;
// }

int check_valid_move(board_t current_board, move_t move) {
  if (current_board[0][move.col] == EMPTY) {
    return 1; // IS VALID
  } else {
    return 0; // IS NOT VALID
  }
}

int make_move(board_t cr_board, move_t move, player_t player) {
  if (check_valid_move(cr_board, move) == 1) {
    for (int i = 3; i > -1; i--) {
      if (cr_board[i][move.col] == EMPTY) {
        cr_board[i][move.col] = player;
        break;
      }
    }
  } else {
      printf("Invalid move, try again.\n");
  }
}

void rev_move(board_t board, move_t move) {
  for (int i = 0; i < 4; i++) {
      if (board[i][move.col] != EMPTY) {
        board[i][move.col] = EMPTY;
        break;
    }
  }
}

move_t best_move(board_t board, player_t player) {
  player_t not_player;
  move_t best;
  best.col = 0;
  best.score = 0;
  board_t temp;
  board_t temp1;
  copy(&temp, board);
  copy(&temp1, temp);
  int movescores[5] = {2, 2, 2, 2, 2};
  if (player == RED) {
    not_player = BLUE;
  } else {
    not_player = RED;
  }

  // from the perspective of the player, if this means a win, then we will play this move, and return a score of 1. If we lose, we return -1. Else, we give 0 to that move.
  for (int i = 0; i < 5; i++) {
    best.col = i;
    if (check_valid_move(temp1, best) == 1) {
      make_move(temp1, best, player);
      if ((has_won(temp1, player)) == 1) {
        best.score = 1;
        return best;
      }
      if (is_full(temp1) == 1) {
        best.score = 0;
        return best;
      }
      rev_move(temp1, best);
    }
  }

  // This is written from the perspective of the player. If this move they make, leads to their victory(loss of the enemy, so it means they return a score of -1), then we play that move.
  for (int i = 0; i < 5; i++) {
    best.col = i;
    if (check_valid_move(temp, best) == 1) {
      make_move(temp, best, player);
      movescores[i] = -best_move(temp, not_player).score;
    }
  }
  for (int i = 0; i < 5; i++) {
    if (movescores[i] == 0) {
      best.col = i;
      return best;
    }
  }

  for (int i = 0; i < 5; i++) {
    if (check_valid_move(temp, best) == 1) {
      best.col = i;
      return best;
    }
  }
  return best;
}

void print_board(board_t board) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      if (board[i][j] == EMPTY) {
        printf(". ");
      }
      if (board[i][j] == RED) {
        printf("R ");
      }
      if (board[i][j] == BLUE) {
        printf("B ");
      }
    }
    printf("\n");
  }
}

void init_board(board_t board) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      board[i][j] = EMPTY;
    }
  }
}

int main() {
  player_t USER = RED;
  player_t COMP = BLUE;

  move_t move;\

  board_t board1;
  init_board(board1);
  print_board(board1);
  while ((has_won(board1, USER) == 0) && (has_won(board1, COMP) == 0) && (is_full(board1) == 0)) {
    scanf("%d", &move.col);
    make_move(board1, move, USER);
    make_move(board1, best_move(board1, COMP), COMP);
    print_board(board1);
  }
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */
  return 0;
}
