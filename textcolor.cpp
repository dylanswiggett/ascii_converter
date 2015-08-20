#include <cstdio>
#include <cmath>
#include <iostream>

#define RESET 0
#define BRIGHT 1
#define DIM 2
#define UNDERLINE 3
#define BLINK 4
#define REVERSE 7
#define HIDDEN 8

#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7

int colors[] = {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
float colorvecs[] = {
  0, 0, 0, // BLACK
  1, 0, 0, // RED
  0, 1, 0, // GREEN
  1, 1, 0, // YELLOW
  0, 0, 1, // BLUE
  1, 0, 1, // MAGENTA
  0, 1, 1, // CYAN
  1, 1, 1  // WHITE
};

void textcolor(int attr, int fg, int bg)
{
  char command[13];

  /* Command is the control command to the terminal */
  sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
  printf("%s", command);
}

int colornear(float r, float g, float b, int *dim)
{
  float bestdist = 1000;
  float bestcolorp = 0;

  for (int i = 0; i < 8; i++) {
    float rd = r - colorvecs[3*i];
    float gd = g - colorvecs[3*i+1];
    float bd = b - colorvecs[3*i+2];
    float cd = sqrt(rd*rd + gd*gd + bd*bd);
    if (cd < bestdist) {
      bestdist = cd;
      bestcolorp = colors[i];
    }
  }
  *dim = (bestdist > .3);
  return bestcolorp;
}

void textcolornear(float fg_r, float fg_g, float fg_b, float bg_r, float bg_g, float bg_b)
{
  int dim;
  int fg, bg;
  bg = colornear(bg_r, bg_g, bg_b, &dim);
  fg = colornear(fg_r, fg_g, fg_b, &dim);
  if (bg == fg) {
    if (bg == WHITE)
      fg = BLACK;
    else
      fg = WHITE;
  }
  textcolor(dim?DIM:0, fg, bg);
}
