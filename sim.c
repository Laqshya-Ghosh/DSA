#include <assert.h>
#include <stdio.h>

#include "test.h"

/*
 * The status of a line.
 */
enum {
  NO = 0, /* No line */
  RED = 1,
  BLUE = 2
};

/*
 * The board records the colors of the lines.
 * board[0] = color of 12
 * board[1] = color of 13
 * ...
 * board[14] = color of 56
 */
typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */

void copy(board_t * temp, board_t board) {
  for (int i = 0; i < 15; i++) {
      (*temp)[i] = board[i];
  }
}

int has_lost(board_t board, player_t player) {
  const int win_combinations[20][3] = {
      {0, 1, 5}, {0, 2, 6}, {0, 3, 7},
      {0, 4, 8}, {1, 2, 9}, {1, 3, 10},
      {1, 4, 11}, {2, 3, 12}, {2, 4, 13}, {3, 4, 14}, {5, 6, 9}, {5, 7, 10}, {5, 8, 11}, {6, 7, 12}, {6, 8, 13}, {7, 8, 14}, {9, 10, 12}, {9, 11, 13}, {10, 11, 14}, {12, 13, 14}
  };

  for (int i = 0; i < 20; i++) {
    int line1 = win_combinations[i][0];
    int line2 = win_combinations[i][1];
    int line3 = win_combinations[i][2];

    if (board[line1] == player && board[line2] == player &&
        board[line3] == player) {
      return 1;
    }
  }

  return 0;
}

int is_full(board_t board) {
  for (int i = 0; i < 15; i++) {
    if (board[i] == NO) {
      return 0;
    }
  }

  return 1;
}

typedef struct {
  int line;
  int score;
} move_t;

int make_move(board_t board, move_t move, player_t player) {
  if (move.line < 0 || move.line >= 15) {
    printf("Invalid line number. Please choose a line between 0 and 14.\n");
    return 0;
  }

  if (board[move.line] == NO) {
    board[move.line] = player;
    return 1;
  } else {
    printf("Line %d is already taken. Please choose an empty line.\n", move.line);
    return 0;
  }
}

move_t best_move(board_t board, player_t player)
{
    move_t response;
    move_t candidate;
    board_t temp;
    copy(&temp, board);
    int no_candidate = 1;

// from perspective of the player
    for (int i = 0; i < 15; i++) {
        if (temp[i] == NO) {
            temp[i] = player;
            if (!has_lost(temp, player)) {
                temp[i] = NO;
                return (move_t){.line = i, .score = 1};
            }
            temp[i] = NO;
        }
    }

    for (int i = 0; i < 15; i++) {
        if (temp[i] == NO) {
            temp[i] = player;
            response = best_move(temp, (player == RED) ? BLUE : RED);
            temp[i] = NO;
            if (response.score == -1) {
                return (move_t){.line = i, .score = 1};
            } else if (response.score == 0) {
                candidate = (move_t){.line = i, .score = 0};
                no_candidate = 0;
            } else {
                if (no_candidate) {
                    candidate = (move_t){.line = i, .score = -1};
                    no_candidate = 0;
                }
            }
        }
    }

    return candidate;
}

void init_game(board_t board) {
  for (int i = 0; i < 15; i++) {
    board[i] = NO;
  }
}

void print_game(board_t board) {
  printf("Game Board:\n");
  printf(" 12  13  14  15  16  23  24  25  26  34  35  36  45  46  56\n");
  printf("-------------------------------------------------------------\n");
  printf("|");

  for (int i = 0; i < 15; ++i) {
    switch (board[i]) {
    case RED:
      printf(" R |");
      break;
    case BLUE:
      printf(" B |");
      break;
    case NO:
      printf("   |");
      break;
    }
  }

  printf("\n-------------------------------------------------------------\n");
}

int main()
{
    board_t board;
    player_t USER = RED;
    player_t COMP = BLUE;
    move_t move;

    init_game(board);

    while (!has_lost(board, USER) || !has_lost(board, COMP)) {
      printf("Current game:\n");
      print_game(board);

      printf("Your turn. Choose a line: ");
      scanf("%d", &move.line);
      while (!make_move(board, move, USER)) {
        printf("Invalid move. Please choose a line between 0 and 14.\n");
        printf("Your turn. Choose a line: ");
        scanf("%d", &move.line);
      }
      make_move(board, move, USER);
      if (has_lost(board, USER)) {
        printf("You lost!\n");
        print_game(board);
        break;
      }
      print_game(board);

      move = best_move(board, COMP);
      printf("Computer's turn. It plays %d.\n", move.line);\
      make_move(board, move, COMP);
      if (has_lost(board, COMP)) {
        printf("You won!\n");
        print_game(board);
        break;
      }
      print_game(board);
    }

    return 0;
}
