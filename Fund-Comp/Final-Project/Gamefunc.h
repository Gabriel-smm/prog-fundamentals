//gamefunc.h

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "gfx2.h"
#include <stdlib.h> // to get rand and srand
#include <time.h>  // to get the seeds for srand

typedef struct {
  int size;
  float xc;
  float yc;
  float angle;
  float dx;
  float dy;
} SpaceShip;

typedef struct {
  float xc;
  float yc;
  float dx;
  float dy;
} ObjPosVel;

typedef struct {
  int radius;
  ObjPosVel ObjCartesian;
  int type;
} Asteroids;

void drawShip(int wid, int ht, int SIZE_SHIP, float angle);
void wall_collision(float *pxc, float *pyc, float *pdx, float *pdy, float angle, int SIZE_SHIP, int wid, int ht);
void drawAsteroid(float *xc, float *yc, int radius, float dx, float dy, int type);
ObjPosVel ObjectCartesian(int wid, int ht, int maxRadius, int minVel, int maxVel);
int asteroidOutOfBounds(float xc, float yc, int wid, int ht, int margin);
void respawnAsteroid(Asteroids *ast, int wid, int ht, int maxRadiusAst, int minRadiusAst, int minVelAst, int maxVelAst);
int ship_asteroidCollision(float ship_xc, float ship_yc, int shipSize, float ast_xc, float ast_yc, int astRadius);
int displayMenu(int wid, int ht, int mx, int my);
int isClickInButton(int mx, int my, int bx, int by, int bw, int bh);
void displayGameOver(int wid, int ht, int finalTime);

