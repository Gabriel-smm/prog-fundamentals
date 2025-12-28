// example1.c
//   a simple example 

#include "gfx.h"
#include <math.h>

#define SIZE 100 // size of the shapes

void drawSquare();
void drawCircle();
void drawTriangle();
void drawPolygon(int c);

int main()
{
  const int xsize = 500, ysize = 300; //size of the screen
  char c; // variable used to store the input from the user

  
  gfx_open(xsize, ysize, "Lab 9: part1");

  
  gfx_color(0,200,100);

  
  while(1) {
    c = gfx_wait();       
    if(c == 'q') break;   
    if(c == 1) {
      drawSquare();
    } else if(c == 'c') {
      drawCircle();
    } else if(c == 't') {
      drawTriangle();
    } else if(c >= '3' && c <= '9') {
      drawPolygon(((int) c - 48));
    } else if(c == 27) {
      gfx_clear();
    }    

  }

  return 0;
}






void drawSquare(){
  int x = gfx_xpos();
  int y = gfx_ypos();
  gfx_color(0, 0, 255);
  gfx_line(x - (SIZE/2), y - (SIZE/2), x + (SIZE/2), y - (SIZE/2));
  gfx_line(x - (SIZE/2), y + (SIZE/2), x + (SIZE/2), y + (SIZE/2));

  gfx_line(x - (SIZE/2), y - (SIZE/2), x - (SIZE/2), y + (SIZE/2));
  gfx_line(x + (SIZE/2), y - (SIZE/2), x + (SIZE/2), y + (SIZE/2));
}

void drawCircle(){
  int x = gfx_xpos();
  int y = gfx_ypos();
  gfx_color(255, 255, 255);
  gfx_circle(x, y, SIZE/2);
}

void drawTriangle(){
  int x = gfx_xpos();
  int y = gfx_ypos();
  gfx_color(0, 255, 0);

  gfx_line(x, y - (SIZE/2), x + (SIZE/2), y + (SIZE/2));
  gfx_line(x, y - (SIZE/2), x - (SIZE/2), y + (SIZE/2));
  gfx_line(x - (SIZE/2), y + (SIZE/2), x + (SIZE/2), y + (SIZE/2));
}

void drawPolygon(int c){
  int x = gfx_xpos();
  int y = gfx_ypos();
  gfx_color(128, 0, 128);

  const double deltaAngle = (2 * M_PI) / c;

  for(int i = 0; i < c; i++){
    gfx_line(x + (SIZE / 2) * cos(deltaAngle * i), y + (SIZE / 2) * sin(deltaAngle * i),       //use of the polar coordinates (x = x0 + r * cos(angle))
    x + (SIZE / 2) * cos(deltaAngle * (i + 1)), y + (SIZE / 2) * sin(deltaAngle * (i + 1)));   // y = y0 + r * sin(angle)
  }

}