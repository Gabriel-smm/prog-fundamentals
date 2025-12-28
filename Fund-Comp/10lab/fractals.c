// fractals.c
// Gabriel Marques
// This code display the fractals required by Lab 10

#include "gfx.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 );
void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 );
void drawSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void Squares( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4 );
void treeLine(float x1, float y1, float l, double angle);
void spiralSquare(int cx, int cy, float squareSide, float angle, float radius);
void circles(int xc, int yc, int radius);
void snowflake(int xc, int yc, int size);
void fern(int x, int y, int len, double angle);
void doubleSpiral(double x, double y, double radius, double angle);


int main() 
{
  char c; 
  int loop = 1; 
  int width = 600, height = 600, mrgn = 20;
  gfx_open(width, height, "Fractals");


  while (loop) {
    c = gfx_wait();
    gfx_clear();

    switch (c) {
      case '1': // Sierpinski Triangle   
        sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
        break;

      case '2': // Shrinking Squares  
        Squares((width/4) + 10, (height/4) + 10, 3 * (width/4) - 10, (height/4) + 10, 3 * (width/4) - 10, 3 * (height/4) - 10, (width/4) + 10, 3 * (height/4) - 10);
        break;
      
      case '3':
        spiralSquare(width/2, height/2, 2, 0, 1);     
        break;

      case '4':
        circles(width/2,height/2, 200);     
        break;

      case '5':
        snowflake(width/2, height/2, 200);     
        break;

      case '6':
        treeLine(width/2, height - mrgn, (height/3.5), M_PI);
        break;

      case '7':
        fern(width / 2, height - mrgn, height/1.6, M_PI / 2);
        break;

      case '8':
        doubleSpiral(width / 2, height / 2, width, 0);
        break;
      
      case 'q':
        loop = 0;
      default:
        continue;
        
    }
  }

  return 0;
}

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  // Base case
  if( abs(x2-x1) < 5 ) return;

  // Draw a triangle
  drawTriangle( x1, y1, x2, y2, x3, y3 );
  

  // Recursive calls
  sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
  sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
  sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}


void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  gfx_line(x1,y1,x2,y2);
  gfx_line(x2,y2,x3,y3);
  gfx_line(x3,y3,x1,y1);
}


void Squares( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4 )
{
  // base case -> stop when side length is too small
  int sideX = abs(x2 - x1 - 3) / 4.2;
  if(sideX < 1) return;

  drawSquare(x1, y1, x2, y2, x3, y3, x4, y4);
  

  Squares(x1 - sideX, y1 - sideX, 
          x1 + sideX, y1 - sideX, 
          x1 + sideX, y1 + sideX, 
          x1 - sideX, y1 + sideX);

  Squares(x2 - sideX, y2 - sideX, 
          x2 + sideX, y2 - sideX,
          x2 + sideX, y2 + sideX, 
          x2 - sideX, y2 + sideX);

  Squares(x3 - sideX, y3 - sideX, 
          x3 + sideX, y3 - sideX, 
          x3 + sideX, y3 + sideX, 
          x3 - sideX, y3 + sideX);

  Squares(x4 - sideX, y4 - sideX, 
          x4 + sideX, y4 - sideX, 
          x4 + sideX, y4 + sideX, 
          x4 - sideX, y4 + sideX);


}

void drawSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){

  gfx_line(x1,y1,x2,y2);
  gfx_line(x2,y2,x3,y3);
  gfx_line(x3,y3,x4,y4);
  gfx_line(x1,y1,x4,y4);  

}

void spiralSquare(int cx, int cy, float squareSide, float angle, float radius){


  if(squareSide > 160) return;
  drawSquare(cx - squareSide/2, cy - squareSide/2,
             cx + squareSide/2, cy - squareSide/2,
             cx + squareSide/2, cy + squareSide/2,
             cx - squareSide/2, cy + squareSide/2);

  float newAngle = angle + (35 + squareSide * 0.1) * (3.14159 / 180); 
  float newRadius = radius + pow(squareSide / 2.0, 1.1) * 0.45;
  
  spiralSquare(cx + (newRadius) * cos(newAngle), cy + (newRadius) * sin(newAngle), squareSide * 1.15, newAngle, newRadius);

}

void circles(int xc, int yc, int radius){

  if(radius < 2) return;

  gfx_circle(xc, yc, radius);

  int newRadius = radius/2.9;

  circles(xc + radius * cos(0), yc + radius * sin(0), newRadius);
  circles(xc + radius * cos(M_PI / 3), yc + radius * sin(M_PI/3), newRadius);
  circles(xc + radius * cos(2 * M_PI/3), yc + radius * sin(2 * M_PI/3), newRadius);
  circles(xc + radius * cos(M_PI), yc + radius * sin(M_PI), newRadius);
  circles(xc + radius * cos(4 * M_PI/3), yc + radius * sin(4 * M_PI/3), newRadius);
  circles(xc + radius * cos(5 * M_PI/3), yc + radius * sin(5 * M_PI/3), newRadius);

}

void snowflake(int xc, int yc, int size){

  if(size < 3) return;

  gfx_line(xc, yc,
           xc + size * cos(19 * M_PI / 10),
           yc + size * sin(19 * M_PI / 10));

  gfx_line(xc, yc,
           xc + size * cos(11 * M_PI / 10),
           yc + size * sin(11 * M_PI / 10));

  gfx_line(xc, yc,
           xc + size * cos(7 * M_PI / 10),
           yc + size * sin(7 * M_PI / 10));

  gfx_line(xc, yc,
           xc + size * cos(3 * M_PI / 10),
           yc + size * sin(3 * M_PI / 10));

  gfx_line(xc, yc,
           xc + size * cos(3 * M_PI / 2),
           yc + size * sin(3 * M_PI / 2));


  int newSize = size/2.6;
  snowflake(xc + size * cos(19 * M_PI / 10), yc + size * sin(19 * M_PI / 10), newSize);
  snowflake(xc + size * cos(11 * M_PI / 10), yc + size * sin(11 * M_PI / 10), newSize);
  snowflake(xc + size * cos(7 * M_PI / 10), yc + size * sin(7 * M_PI / 10), newSize);
  snowflake(xc + size * cos(3 * M_PI / 10), yc + size * sin(3 * M_PI / 10), newSize);
  snowflake(xc + size * cos(3 * M_PI / 2), yc + size * sin(3 * M_PI / 2), newSize);

}



void treeLine(float x1, float y1, float l, double angle){
  //Base case
  if(l < 2) return;

  gfx_line(x1, y1, x1 + l * sin(angle), y1 + l * cos(angle));

  treeLine(x1 + l * sin(angle), y1 + l * cos(angle), l * 0.67, angle + M_PI/5);
  treeLine(x1 + l * sin(angle), y1 + l * cos(angle), l * 0.67, angle - M_PI/5);
}

void fern(int x, int y, int len, double angle){
  int i;
  // Base case
  if (len < 3)
    return;

  gfx_line(x, y, x + len * cos(angle), y - len * sin(angle));

  // The branches are repeated 4 times for both sides
  for (i = 1; i <= 4; i++) {
    fern(x + i * (len * cos(angle)) / 4, y - i * (len * sin(angle)) / 4, len * 0.36, angle + M_PI / 5);
    fern(x + i * (len * cos(angle)) / 4, y - i * (len * sin(angle)) / 4, len * 0.36, angle - M_PI / 5);
  }
}

// A spiral calling itself to draw a spiral at each point 
void doubleSpiral(double x, double y, double radius, double angle){
  while (radius > 1) { //Base case (radius > 1)
    angle += M_PI / 5;

    radius *= 0.9;

    
    if (radius < 5) gfx_point(x + radius * cos(angle), y + radius * sin(angle));
    else doubleSpiral(x + cos(angle) * radius , y + sin(angle) * radius , radius / 2.6, angle);
  }
}