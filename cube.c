#include <stdio.h>
#include <stdlib.h>

enum color {
  RED,
  BLUE,
  GREEN,
  YELLOW,
  WHITE,
  ORANGE,
  EMPTY,
};

struct cell {
  enum color cell_color;
};

struct face {
  struct cell cells[4];
};

struct cube {
  struct face faces[6];
};

struct move {
  int face;
};

struct gamestate {
  int moves_made[12][2]; // assuming it takes at most 24 moves to complete a
                         // cube, [0] for storing the face, [1] for storing the
                         // move (clockwise, anti-clockwise or double)
};

void init_state(struct gamestate *game) {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 2; j++) {
      game->moves_made[i][j] = -1;
    }
  }
}

struct Node {
  struct gamestate data;
  struct Node * next;
};

struct LinkedList {
  struct Node * head;
};

struct Node * createNode(struct gamestate data) {
  struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

struct LinkedList initializeList() {
  struct LinkedList list;
  list.head = NULL;
  return list;
}

void append(struct LinkedList * list, struct gamestate data) {
  struct Node * newNode = createNode(data);
  if (list->head == NULL) {
    list->head = newNode;
  } else {
    struct Node * current = list->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  }
}

void init_cube(struct cube * cube1) {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 4; j++) {
      cube1->faces[i].cells[j].cell_color = EMPTY;
    }
  }
}

void normal_cube(struct cube * cube1) {
  // front face = RED
  cube1->faces[0].cells[0].cell_color = RED;
  cube1->faces[0].cells[1].cell_color = RED;
  cube1->faces[0].cells[2].cell_color = RED;
  cube1->faces[0].cells[3].cell_color = RED;
  // left face = GREEN
  cube1->faces[1].cells[0].cell_color = GREEN;
  cube1->faces[1].cells[1].cell_color = GREEN;
  cube1->faces[1].cells[2].cell_color = GREEN;
  cube1->faces[1].cells[3].cell_color = GREEN;
  // right face = BLUE
  cube1->faces[2].cells[0].cell_color = BLUE;
  cube1->faces[2].cells[1].cell_color = BLUE;
  cube1->faces[2].cells[2].cell_color = BLUE;
  cube1->faces[2].cells[3].cell_color = BLUE;
  // back face = ORANGE
  cube1->faces[3].cells[0].cell_color = ORANGE;
  cube1->faces[3].cells[1].cell_color = ORANGE;
  cube1->faces[3].cells[2].cell_color = ORANGE;
  cube1->faces[3].cells[3].cell_color = ORANGE;
  // top face = WHITE
  cube1->faces[4].cells[0].cell_color = WHITE;
  cube1->faces[4].cells[1].cell_color = WHITE;
  cube1->faces[4].cells[2].cell_color = WHITE;
  cube1->faces[4].cells[3].cell_color = WHITE;
  // bottom face = YELLOW
  cube1->faces[5].cells[0].cell_color = YELLOW;
  cube1->faces[5].cells[1].cell_color = YELLOW;
  cube1->faces[5].cells[2].cell_color = YELLOW;
  cube1->faces[5].cells[3].cell_color = YELLOW;
}

void rotate_cube_clockwise(struct cube * cube1, struct move move) {
  enum color temp1; // saves the top left block w.r.t to the face chosen
  enum color temp2; // saves the top right block w.r.t to the face chosen
  enum color temp3; // saves the top right block of the face chosen
  if (move.face == 0) {
    // Swap the adjacent sides 3 times
    temp1 = cube1->faces[4].cells[2].cell_color;
    temp2 = cube1->faces[4].cells[3].cell_color;
    cube1->faces[4].cells[2].cell_color = cube1->faces[1].cells[3].cell_color;
    cube1->faces[4].cells[3].cell_color = cube1->faces[1].cells[1].cell_color;
    cube1->faces[1].cells[1].cell_color = cube1->faces[5].cells[0].cell_color;
    cube1->faces[1].cells[3].cell_color = cube1->faces[5].cells[1].cell_color;
    cube1->faces[5].cells[1].cell_color = cube1->faces[2].cells[0].cell_color;
    cube1->faces[5].cells[0].cell_color = cube1->faces[2].cells[2].cell_color;
    cube1->faces[2].cells[0].cell_color = temp1;
    cube1->faces[2].cells[2].cell_color = temp2;
  }
  // if (move.face == 1) {
  //   temp1 = cube1->faces[4].cells[0].cell_color;
  //   temp2 = cube1->faces[4].cells[2].cell_color;
  //   cube1->faces[4].cells[0].cell_color = cube1->faces[3].cells[3].cell_color;
  //   cube1->faces[4].cells[2].cell_color = cube1->faces[3].cells[1].cell_color;
  //   cube1->faces[3].cells[1].cell_color = cube1->faces[5].cells[2].cell_color;
  //   cube1->faces[3].cells[3].cell_color = cube1->faces[5].cells[0].cell_color;
  //   cube1->faces[5].cells[0].cell_color = cube1->faces[0].cells[0].cell_color;
  //   cube1->faces[5].cells[2].cell_color = cube1->faces[0].cells[2].cell_color;
  //   cube1->faces[0].cells[0].cell_color = temp1;
  //   cube1->faces[0].cells[2].cell_color = temp2;
  // }
  if (move.face == 2) {
    temp1 = cube1->faces[4].cells[1].cell_color;
    temp2 = cube1->faces[4].cells[3].cell_color;
    cube1->faces[4].cells[1].cell_color = cube1->faces[0].cells[1].cell_color;
    cube1->faces[4].cells[3].cell_color = cube1->faces[0].cells[3].cell_color;
    cube1->faces[0].cells[1].cell_color = cube1->faces[5].cells[1].cell_color;
    cube1->faces[0].cells[3].cell_color = cube1->faces[5].cells[3].cell_color;
    cube1->faces[5].cells[1].cell_color = cube1->faces[3].cells[2].cell_color;
    cube1->faces[5].cells[3].cell_color = cube1->faces[3].cells[0].cell_color;
    cube1->faces[3].cells[0].cell_color = temp2;
    cube1->faces[3].cells[2].cell_color = temp1;
  }
  // if (move.face == 3) {
  //   temp1 = cube1->faces[4].cells[0].cell_color;
  //   temp2 = cube1->faces[4].cells[1].cell_color;
  //   cube1->faces[4].cells[0].cell_color = cube1->faces[2].cells[1].cell_color;
  //   cube1->faces[4].cells[1].cell_color = cube1->faces[2].cells[3].cell_color;
  //   cube1->faces[2].cells[1].cell_color = cube1->faces[5].cells[3].cell_color;
  //   cube1->faces[2].cells[3].cell_color = cube1->faces[5].cells[2].cell_color;
  //   cube1->faces[5].cells[2].cell_color = cube1->faces[1].cells[0].cell_color;
  //   cube1->faces[5].cells[3].cell_color = cube1->faces[1].cells[2].cell_color;
  //   cube1->faces[1].cells[0].cell_color = temp2;
  //   cube1->faces[1].cells[2].cell_color = temp1;
  // }
  if (move.face == 4) {
    temp1 = cube1->faces[0].cells[0].cell_color;
    temp2 = cube1->faces[0].cells[1].cell_color;
    cube1->faces[0].cells[0].cell_color = cube1->faces[2].cells[0].cell_color;
    cube1->faces[0].cells[1].cell_color = cube1->faces[2].cells[1].cell_color;
    cube1->faces[2].cells[0].cell_color = cube1->faces[3].cells[0].cell_color;
    cube1->faces[2].cells[1].cell_color = cube1->faces[3].cells[1].cell_color;
    cube1->faces[3].cells[0].cell_color = cube1->faces[1].cells[0].cell_color;
    cube1->faces[3].cells[1].cell_color = cube1->faces[1].cells[1].cell_color;
    cube1->faces[1].cells[0].cell_color = temp1;
    cube1->faces[1].cells[1].cell_color = temp2;
  }
  // if (move.face == 5) {
  //   temp1 = cube1->faces[0].cells[2].cell_color;
  //   temp2 = cube1->faces[0].cells[3].cell_color;
  //   cube1->faces[0].cells[2].cell_color = cube1->faces[1].cells[2].cell_color;
  //   cube1->faces[0].cells[3].cell_color = cube1->faces[1].cells[3].cell_color;
  //   cube1->faces[1].cells[2].cell_color = cube1->faces[3].cells[2].cell_color;
  //   cube1->faces[1].cells[3].cell_color = cube1->faces[3].cells[3].cell_color;
  //   cube1->faces[3].cells[2].cell_color = cube1->faces[2].cells[2].cell_color;
  //   cube1->faces[3].cells[3].cell_color = cube1->faces[2].cells[3].cell_color;
  //   cube1->faces[2].cells[2].cell_color = temp1;
  //   cube1->faces[2].cells[3].cell_color = temp2;
  // }
  temp3 = cube1->faces[move.face].cells[0].cell_color;
  cube1->faces[move.face].cells[0].cell_color =
      cube1->faces[move.face].cells[2].cell_color;
  cube1->faces[move.face].cells[2].cell_color =
      cube1->faces[move.face].cells[3].cell_color;
  cube1->faces[move.face].cells[3].cell_color =
      cube1->faces[move.face].cells[1].cell_color;
  cube1->faces[move.face].cells[1].cell_color = temp3;
}

void rotate_cube_anti_clockwise(struct cube * cube1, struct move move) {
  enum color temp1; // saves the top left block w.r.t to the face chosen
  enum color temp2; // saves the top right block w.r.t to the face chosen
  enum color temp3; // saves the top right block of the face chosen
  if (move.face == 0) {
    // Swap the adjacent sides 3 times
    temp1 = cube1->faces[4].cells[2].cell_color;
    temp2 = cube1->faces[4].cells[3].cell_color;
    cube1->faces[4].cells[2].cell_color = cube1->faces[2].cells[0].cell_color;
    cube1->faces[4].cells[3].cell_color = cube1->faces[2].cells[2].cell_color;
    cube1->faces[2].cells[0].cell_color = cube1->faces[5].cells[1].cell_color;
    cube1->faces[2].cells[2].cell_color = cube1->faces[5].cells[0].cell_color;
    cube1->faces[5].cells[0].cell_color = cube1->faces[1].cells[1].cell_color;
    cube1->faces[5].cells[1].cell_color = cube1->faces[1].cells[3].cell_color;
    cube1->faces[1].cells[1].cell_color = temp2;
    cube1->faces[1].cells[3].cell_color = temp1;
  }
  // if (move.face == 1) {
  //   temp1 = cube1->faces[4].cells[0].cell_color;
  //   temp2 = cube1->faces[4].cells[2].cell_color;
  //   cube1->faces[4].cells[0].cell_color = cube1->faces[0].cells[0].cell_color;
  //   cube1->faces[4].cells[2].cell_color = cube1->faces[0].cells[2].cell_color;
  //   cube1->faces[0].cells[0].cell_color = cube1->faces[5].cells[0].cell_color;
  //   cube1->faces[0].cells[2].cell_color = cube1->faces[5].cells[2].cell_color;
  //   cube1->faces[5].cells[0].cell_color = cube1->faces[3].cells[3].cell_color;
  //   cube1->faces[5].cells[2].cell_color = cube1->faces[3].cells[1].cell_color;
  //   cube1->faces[3].cells[1].cell_color = temp2;
  //   cube1->faces[3].cells[3].cell_color = temp1;
  // }
  if (move.face == 2) {
    temp1 = cube1->faces[4].cells[1].cell_color;
    temp2 = cube1->faces[4].cells[3].cell_color;
    cube1->faces[4].cells[1].cell_color = cube1->faces[3].cells[2].cell_color;
    cube1->faces[4].cells[3].cell_color = cube1->faces[3].cells[0].cell_color;
    cube1->faces[3].cells[0].cell_color = cube1->faces[5].cells[3].cell_color;
    cube1->faces[3].cells[2].cell_color = cube1->faces[5].cells[1].cell_color;
    cube1->faces[5].cells[1].cell_color = cube1->faces[0].cells[1].cell_color;
    cube1->faces[5].cells[3].cell_color = cube1->faces[0].cells[3].cell_color;
    cube1->faces[0].cells[1].cell_color = temp1;
    cube1->faces[0].cells[3].cell_color = temp2;
  }
  // if (move.face == 3) {
  //   temp1 = cube1->faces[4].cells[0].cell_color;
  //   temp2 = cube1->faces[4].cells[1].cell_color;
  //   cube1->faces[4].cells[0].cell_color = cube1->faces[1].cells[2].cell_color;
  //   cube1->faces[4].cells[1].cell_color = cube1->faces[1].cells[0].cell_color;
  //   cube1->faces[1].cells[0].cell_color = cube1->faces[5].cells[2].cell_color;
  //   cube1->faces[1].cells[2].cell_color = cube1->faces[5].cells[3].cell_color;
  //   cube1->faces[5].cells[2].cell_color = cube1->faces[2].cells[3].cell_color;
  //   cube1->faces[5].cells[3].cell_color = cube1->faces[2].cells[1].cell_color;
  //   cube1->faces[2].cells[1].cell_color = temp1;
  //   cube1->faces[2].cells[3].cell_color = temp2;
  // }
  if (move.face == 4) {
    temp1 = cube1->faces[0].cells[0].cell_color;
    temp2 = cube1->faces[0].cells[1].cell_color;
    cube1->faces[0].cells[0].cell_color = cube1->faces[1].cells[0].cell_color;
    cube1->faces[0].cells[1].cell_color = cube1->faces[1].cells[1].cell_color;
    cube1->faces[1].cells[0].cell_color = cube1->faces[3].cells[0].cell_color;
    cube1->faces[1].cells[1].cell_color = cube1->faces[3].cells[1].cell_color;
    cube1->faces[3].cells[0].cell_color = cube1->faces[2].cells[0].cell_color;
    cube1->faces[3].cells[1].cell_color = cube1->faces[2].cells[1].cell_color;
    cube1->faces[2].cells[0].cell_color = temp1;
    cube1->faces[2].cells[1].cell_color = temp2;
  }
  // if (move.face == 5) {
  //   temp1 = cube1->faces[0].cells[2].cell_color;
  //   temp2 = cube1->faces[0].cells[3].cell_color;
  //   cube1->faces[0].cells[2].cell_color = cube1->faces[2].cells[2].cell_color;
  //   cube1->faces[0].cells[3].cell_color = cube1->faces[2].cells[3].cell_color;
  //   cube1->faces[2].cells[2].cell_color = cube1->faces[3].cells[2].cell_color;
  //   cube1->faces[2].cells[3].cell_color = cube1->faces[3].cells[3].cell_color;
  //   cube1->faces[3].cells[2].cell_color = cube1->faces[1].cells[2].cell_color;
  //   cube1->faces[3].cells[3].cell_color = cube1->faces[1].cells[3].cell_color;
  //   cube1->faces[1].cells[2].cell_color = temp1;
  //   cube1->faces[1].cells[3].cell_color = temp2;
  // }
  temp3 = cube1->faces[move.face].cells[0].cell_color;
  cube1->faces[move.face].cells[0].cell_color =
      cube1->faces[move.face].cells[1].cell_color;
  cube1->faces[move.face].cells[1].cell_color =
      cube1->faces[move.face].cells[3].cell_color;
  cube1->faces[move.face].cells[3].cell_color =
      cube1->faces[move.face].cells[2].cell_color;
  cube1->faces[move.face].cells[2].cell_color = temp3;
}

void double_rotation(struct cube * cube1, struct move move) {
  rotate_cube_anti_clockwise(cube1, move);
  rotate_cube_anti_clockwise(cube1, move);
}

int check_if_complete(struct cube cube1) {
  for (int i = 0; i < 6; i++) {
    if ((cube1.faces[i].cells[0].cell_color !=
         cube1.faces[i].cells[1].cell_color) ||
        (cube1.faces[i].cells[0].cell_color !=
         cube1.faces[i].cells[2].cell_color) ||
        (cube1.faces[i].cells[0].cell_color !=
         cube1.faces[i].cells[3].cell_color)) {
      return 0;
    }
  }
  return 1;
}

void randomize_cube(struct cube *cube) {
  normal_cube(cube);
  struct move move;
  move.face = 4;
  rotate_cube_anti_clockwise(cube, move);
  move.face = 2;
  rotate_cube_anti_clockwise(cube, move);
  move.face = 2;
  rotate_cube_anti_clockwise(cube, move);
  move.face = 2;
  rotate_cube_clockwise(cube, move);
  move.face = 0;
  rotate_cube_clockwise(cube, move);
  move.face = 2;
  rotate_cube_anti_clockwise(cube, move);
  move.face = 0;
  rotate_cube_anti_clockwise(cube, move);
  move.face = 2;
  rotate_cube_clockwise(cube, move);
  // move.face = 0;
  // rotate_cube_clockwise(cube, move);
  // move.face = 4;
  // rotate_cube_clockwise(cube, move);
  // cube1->faces[0].cells[0].cell_color = WHITE;
  // cube1->faces[0].cells[1].cell_color = WHITE;
  // cube1->faces[0].cells[2].cell_color = WHITE;
  // cube1->faces[0].cells[3].cell_color = WHITE;
  // // left face = GREEN
  // cube1->faces[1].cells[0].cell_color = BLUE;
  // cube1->faces[1].cells[1].cell_color = BLUE;
  // cube1->faces[1].cells[2].cell_color = BLUE;
  // cube1->faces[1].cells[3].cell_color = BLUE;
  // // right face = BLUE
  // cube1->faces[2].cells[0].cell_color = RED;
  // cube1->faces[2].cells[1].cell_color = RED;
  // cube1->faces[2].cells[2].cell_color = RED;
  // cube1->faces[2].cells[3].cell_color = RED;
  // // back face = ORANGE
  // cube1->faces[3].cells[0].cell_color = ORANGE;
  // cube1->faces[3].cells[1].cell_color = ORANGE;
  // cube1->faces[3].cells[2].cell_color = ORANGE;
  // cube1->faces[3].cells[3].cell_color = ORANGE;
  // // top face = WHITE
  // cube1->faces[4].cells[0].cell_color = GREEN;
  // cube1->faces[4].cells[1].cell_color = GREEN;
  // cube1->faces[4].cells[2].cell_color = GREEN;
  // cube1->faces[4].cells[3].cell_color = GREEN;
  // // bottom face = YELLOW
  // cube1->faces[5].cells[0].cell_color = BLUE;
  // cube1->faces[5].cells[1].cell_color = BLUE;
  // cube1->faces[5].cells[2].cell_color = BLUE;
  // cube1->faces[5].cells[3].cell_color = BLUE;
}

void print_cube(struct cube cube1) {
  for (int i = 0; i < 6; i++) {
    switch (i) {
    case 0:
      printf("Front Face\n");
      break;
    case 1:
      printf("Left Face\n");
      break;
    case 2:
      printf("Right Face\n");
      break;
    case 3:
      printf("Back Face\n");
      break;
    case 4:
      printf("Top Face\n");
      break;
    case 5:
      printf("Bottom Face\n");
      break;
    }
    for (int j = 0; j < 4; j++) {
      switch (cube1.faces[i].cells[j].cell_color) {
      case RED:
        printf("\033[31m██\033[0m");
        break;
      case BLUE:
        printf("\033[34m██\033[0m");
        break;
      case GREEN:
        printf("\033[32m██\033[0m");
        break;
      case YELLOW:
        printf("\033[033m██\033[0m");
        break;
      case WHITE:
        printf("██");
        break;
      case ORANGE:
        printf("\033[91m██\033[0m");
        break;
      case EMPTY:
        printf("\033[30m██\033[0m");
        break;
      }
      if (j == 1) {
        printf("\n");
      }
    }
    printf("\n");
  }
}

int compare_cube(struct cube cube1, struct cube cube2) {
  for(int i = 0; i < 6; i++) {
    for(int j = 0; j < 4; j++) {
      if (cube1.faces[i].cells[j].cell_color != cube2.faces[i].cells[j].cell_color) {
        return 0;
      }
    }
  }
  return 1;
}

struct gamestate solve_cube(struct cube * cube1) {
  struct LinkedList ll = initializeList();
  int faces[3] = {0, 2, 4};
  struct move move1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      move1.face = faces[i];
      struct gamestate gs;
      init_state(&gs);
      if (j == 0) {
        rotate_cube_clockwise(cube1, move1);
        for (int g = 0; g < 12; g++) {
          if (gs.moves_made[g][0] != -1) {
            continue;
          } else {
            gs.moves_made[g][0] = faces[i];
            gs.moves_made[g][1] = 0;
            break;
          }
        }
      }
      if (j == 1) {
        rotate_cube_anti_clockwise(cube1, move1);
        for (int g = 0; g < 12; g++) {
          if (gs.moves_made[g][0] != -1) {
            continue;
          } else {
            gs.moves_made[g][0] = faces[i];
            gs.moves_made[g][1] = 1;
            break;
          }
        }
      }
      if (j == 2) {
        double_rotation(cube1, move1);
        for (int g = 0; g < 12; g++) {
          if (gs.moves_made[g][0] != -1) {
            continue;
          } else {
            gs.moves_made[g][0] = faces[i];
            gs.moves_made[g][1] = 2;
            break;
          }
        }
      }
      if (check_if_complete(* cube1)) {
        return gs;
      }
      append(&ll, gs);
      // reverse move
      if (j == 0) {
        rotate_cube_anti_clockwise(cube1, move1);
      }
      if (j == 1) {
        rotate_cube_clockwise(cube1, move1);
      }
      if (j == 2) {
        double_rotation(cube1, move1);
      }
    }
  }
  struct Node * current = ll.head;
  struct gamestate gs1;
  init_state(&gs1);
  while (1) {
    // interpreting gamestate
    gs1 = current->data;
    int i = 0;
    struct move move2;
    while (gs1.moves_made[i][0] != -1) {
      move2.face = gs1.moves_made[i][0];
      if (gs1.moves_made[i][1] == 0) {
        rotate_cube_clockwise(cube1, move2);
      }
      if (gs1.moves_made[i][1] == 1) {
        rotate_cube_anti_clockwise(cube1, move2);
      }
      if (gs1.moves_made[i][1] == 2) {
        double_rotation(cube1, move2);
      }
      i++;
    }
    // making all possible moves from a given state
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        struct gamestate gs = current->data;
        move1.face = faces[i];
          if (gs1.moves_made[i][0] == move1.face) {
          if (gs1.moves_made[i][1] == 0 && j == 1) {
            continue;
          }
          if (gs1.moves_made[i][1] == 1 && j == 0) {
            continue;
          }
          if (gs1.moves_made[i][1] == 2 && j == 2) {
            continue;
          }
        }
        if (j == 0) {
          rotate_cube_clockwise(cube1, move1);
          for (int g = 0; g < 12; g++) {
            if (gs.moves_made[g][0] != -1) {
              continue;
            } else {
              gs.moves_made[g][0] = faces[i];
              gs.moves_made[g][1] = 0;
              break;
            }
          }
        }
        if (j == 1) {
          rotate_cube_anti_clockwise(cube1, move1);
          for (int g = 0; g < 12; g++) {
            if (gs.moves_made[g][0] != -1) {
              continue;
            } else {
              gs.moves_made[g][0] = faces[i];
              gs.moves_made[g][1] = 1;
              break;
            }
          }
        }
        if (j == 2) {
          double_rotation(cube1, move1);
          for (int g = 0; g < 12; g++) {
            if (gs.moves_made[g][0] != -1) {
              continue;
            } else {
              gs.moves_made[g][0] = faces[i];
              gs.moves_made[g][1] = 2;
              break;
            }
          }
        }
        if (check_if_complete(* cube1)) {
          return gs;
        }
        // print_cube(cube1);
        append(&ll, gs);
        // reverse move
        if (j == 0) {
          rotate_cube_anti_clockwise(cube1, move1);
        }
        if (j == 1) {
          rotate_cube_clockwise(cube1, move1);
        }
        if (j == 2) {
          double_rotation(cube1, move1);
        }
      }
    }
    // reversing the gamestate to the original
    int br;
    for (int a = 0; gs1.moves_made[a][0] != -1; a++) {
      if (gs1.moves_made[a + 1][0] == -1) {
        br = a;
        break;
      }
    }
    while (br != -1) {
      move2.face = gs1.moves_made[br][0];
      if (gs1.moves_made[br][1] == 0) {
        rotate_cube_anti_clockwise(cube1, move2);
      }
      if (gs1.moves_made[br][1] == 1) {
        rotate_cube_clockwise(cube1, move2);
      }
      if (gs1.moves_made[br][1] == 2) {
        double_rotation(cube1, move2);
      }
      br--;
    }
    // print_cube(cube1);
    current = current->next;
  }
}

void print_order(struct gamestate game) {
  int i = 0;
  int move_type;
  int face;
  while (game.moves_made[i][0] != -1) {
    move_type = game.moves_made[i][1];
    face = game.moves_made[i][0];
    // for face 0
    if ((move_type == 0) && (face == 0)) {
      printf("F");
    }
    else if ((move_type == 1) && (face == 0)) {
      printf("F'");
    }
    else if ((move_type == 2) && (face == 0)) {
      printf("F2");
    }
    // for face 2
    else if ((move_type == 0) && (face == 2)) {
      printf("R");
    }
    else if ((move_type == 1) && (face == 2)) {
      printf("R'");
    }
    else if ((move_type == 2) && (face == 2)) {
      printf("R2");
    }
    // for face 4
    else if ((move_type == 0) && (face == 4)) {
      printf("U");
    }
    else if ((move_type == 1) && (face == 4)) {
      printf("U'");
    }
    else if ((move_type == 2) && (face == 4)) {
      printf("U2");
    }
    if (game.moves_made[i + 1][0] != -1) {
      printf("->");
    }
    i++;
  }
  printf("\n");
}



int main() {
  struct cube cube1;
  init_cube(&cube1);
  randomize_cube(&cube1);
  print_cube(cube1);
  struct gamestate final;
  final = solve_cube(&cube1);
  print_order(final);
  return 0;
}
