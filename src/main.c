#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { SPOCK, SCISSORS, PAPER, ROCK, LIZARD, SHAPE_COUNT } player1, player2;
enum { startMenu, gameMenu, exitMenu } GAMESTATUS;

int score[] = {0, 0};
#define startMenu 0
#define gameMenu 1
#define exitgame

const char *SHAPE_STRINGS[] = {"🖖", "✂️", "️🗒️", "🪨", "🦎", "🙇"};
const char *LITERAL_STRINGS[] = {"SPUCK", "SCISSOR", "PAPER", "ROCK", "LIZARD"};

bool RUNNING = true;
int inputbuffer;
char charbufferfufer;
void gameprocess();
void printStartmenu();
void printGamemenu();
int checkscore();
int printExitmenu();
int calculateoutcome(int plhand, int rbhand);
int getuserinput();
int playerscore = 0, roboscore = 0;
char *winner;

int difference;

int main() {
  GAMESTATUS = startMenu;
  gameprocess();
  return 0;
}

void gameprocess() {
  while (RUNNING) {
    switch (GAMESTATUS) {
    case startMenu:
      printStartmenu();

      break;
    case gameMenu:
      printGamemenu();

      break;
    case exitMenu:
      printExitmenu();
      break;
    default:
      puts("Unknown GAMESTATUS\n");
      printf("%d", GAMESTATUS);
    }
  }
}

void printStartmenu() {
  printf("Hello and welcome to the exciting game of.......\n");
  for (size_t player1 = 0; player1 < SHAPE_COUNT; player1++) {
    printf("< %-10s : %s >\n", LITERAL_STRINGS[player1],
           SHAPE_STRINGS[player1]);
  }
  printf("(s/S) start game  |  (e/E) exit game\n");
  puts("How would you like to proceed?");

  while (isspace(inputbuffer = getchar()) && inputbuffer != EOF)
    ;
  if (inputbuffer == 's') {
    printf("OH YEAH! YOU CHOSE TO PARTY!!!%s\n", SHAPE_STRINGS[5]);
    GAMESTATUS = gameMenu;
  } else if (inputbuffer == 'e') {
    GAMESTATUS = exitMenu;
  }
}

void printGamemenu() {
  // while (RUNNING) {
  srand(time(NULL));
  puts("Game starting...\n\n\n");
  while (RUNNING) {
    puts("\nPls Select shape, if you dare");
    for (int i = 0; i < SHAPE_COUNT; i++) {
      printf("< %s : %s : %d >\t", LITERAL_STRINGS[i], SHAPE_STRINGS[i], i);
    }
    puts(" ");
    int robohand = rand() % SHAPE_COUNT;
    int playerhand = getuserinput();
    printf("You chose --> %-5s  VS ROBOGUY --> %-5s\n",
           SHAPE_STRINGS[playerhand], SHAPE_STRINGS[robohand]);
    int outcome = calculateoutcome(playerhand, robohand);
    if (checkscore()) {
      break;
    }
  }

  //}
}

int getuserinput() {
  int playerhand;
  while (1) {
    scanf("%d", &playerhand);
    if (playerhand > 4 || playerhand < 0) {
      printf("Brother there are 5 shapes. from 0-4 pls choose one of those.");
    } else {
      break;
    }
  }

  return playerhand;
}

int calculateoutcome(int plhand, int rbhand) {

  difference = (rbhand - plhand + 5) % 5;
  if (difference == 1 || difference == 3) {
    score[0] += 1;
    printf("You scored!! -->");
  } else if (difference == 2 || difference == 4) {
    score[1] += 1;
    printf("ROBOGUY scored!! -->");
  }
  printf("The current score is You: %d, ROBOGUY: %d\n", score[0], score[1]);
  return difference;
}

int checkscore() {
  if (score[0] == 5) {
    printf("Final Score is...... YOU: %d <VS> ROBOGUY: %d\nYOU WIN!!!!!\n",
           score[0], score[1]);
    winner = "You\0";
    GAMESTATUS = exitMenu;
    return 1;
  } else if (score[1] == 5) {
    printf("Final Score is...... YOU: %d <VS> ROBOGUY: %d\nROBOGUY WINS!!!!!\n",
           score[0], score[1]);
    winner = "ROBOGUY\0";
    GAMESTATUS = exitMenu;
    return 1;
  } else {
    return 0;
  }
}

int printExitmenu() {
  printf("Thanks for playing this round of RPSSL\nThe winner of your game "
         "was: %s with %d points!\n",
         winner, abs(score[0] - score[1]));
  printf("Would you like to play again? <Y/y> or <N/n>\t");
  while (isspace(inputbuffer = getchar()) && inputbuffer != EOF)
    ;
  char lowerbuffer = tolower(inputbuffer);
  if (lowerbuffer == 'y') {
    GAMESTATUS = gameMenu;
    score[0] = 0;
    score[1] = 0;
    puts("");
  } else if (lowerbuffer == 'n') {
    exit(0);
  }
  return 0;
}