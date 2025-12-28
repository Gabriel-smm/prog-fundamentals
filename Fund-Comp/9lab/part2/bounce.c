//bounce.c
//Gabriel Marques
//this program creates a animation of a bouncing ball at the desired inital start


#include <unistd.h>
#include "gfx.h"
#include <stdlib.h> // to get rand and srand
#include <time.h>  //to get the seeds for srand

int wid = 700, ht = 500;  

typedef struct {
  float xc;
  float yc;
  int radius;
  float dx;
  float dy;
} Circle;

void wall_collision(float *xc, float *yc, int radius, float *dx, float *dy);
void move_circle(float *xc, float *yc, int radius, float *dx, float *dy);

int main()
{

  gfx_open(wid, ht, "Lab9 - Part 2: Bounce");
  gfx_clear_color(0,0,0); 
  gfx_clear();
  gfx_color(255,255,255);

  Circle c1 = {103, 100, 20, 11, -7};

  while(1) {
    gfx_clear();

    srand(time(0)); //time returns the current time, which will make the sequence of randon numbers diferent every iteration

    gfx_circle(c1.xc, c1.yc, c1.radius);

    move_circle(&c1.xc, &c1.yc, c1.radius, &c1.dx, &c1.dy);

    wall_collision(&c1.xc, &c1.yc, c1.radius, &c1.dx, &c1.dy);
    
    gfx_flush();

    if (gfx_event_waiting()) {
      char c = gfx_wait();
      if (c == 'q') break;
      if (c == 1){
        c1.xc = gfx_xpos();
        c1.yc = gfx_ypos();
        c1.dy = rand() % ((15) - (-15) + 1) + (-15);
        c1.dx = rand() % ((15) - (-15) + 1) + (-15); //this formula (rand() % (max - min + 1) + min) sets the max and min to the rand()
      }
    }

    usleep(30000);
  }

  return 0;
}

void move_circle(float *pxc, float *pyc, int radius, float *pdx, float *pdy)
{
  *pxc += *pdx;
  *pyc += *pdy;
}

void wall_collision(float *pxc, float *pyc, int radius, float *pdx, float *pdy)
{
  if ((*pxc + radius) >= wid) {
    *pdx = -(*pdx);
    *pxc = wid - radius;
    *pxc += *pdx; // this prevents the "stuck on edge" bug
  }

  if ((*pyc + radius) >= ht) {
    *pdy = -(*pdy);
    *pyc = ht - radius;
    *pyc += *pdy; // this prevents the "stuck on edge" bug
  }

  if ((*pxc - radius) <= 0) {
    *pdx = -(*pdx);
    *pxc = 0 + radius;
    *pxc += *pdx; // this prevents the "stuck on edge" bug
  }

  if ((*pyc - radius) <= 0) {
    *pdy = -(*pdy);
    *pyc = 0 + radius;
    *pyc += *pdy; // this prevents the "stuck on edge" bug
  }

}

