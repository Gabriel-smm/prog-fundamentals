//gamefun.c


#include "Gamefunc.h"

void drawShip(int xc, int yc, int SIZE_SHIP, float angle){

  int R_nose = SIZE_SHIP * 0.9;           // Distance from center to nose (front tip)
  int R_wing = SIZE_SHIP * 0.7;     // Distance from center to wings
  int R_back = SIZE_SHIP * 0.13;     // Distance from center to back indent

  float offset_nose = 0;
  float offset_right = M_PI + 0.9772952118001; //this long number is, according to my calculations for the dimension of my ship,
  float offset_left = M_PI - 0.9772952118001;  //the right angle for the wings (tan(a) = (4/3))
  float offset_back = M_PI;

  gfx_color(238, 75, 43);
  gfx_line( xc + R_nose * cos(angle + offset_nose), yc + R_nose * sin(angle + offset_nose),
            xc + R_wing * cos(angle + offset_right), yc + R_wing * sin(angle + offset_right));

  gfx_line( xc + R_nose * cos(angle + offset_nose), yc + R_nose * sin(angle + offset_nose),
            xc + R_wing * cos(angle + offset_left), yc + R_wing * sin(angle + offset_left));


  gfx_line( xc + R_wing * cos(angle + offset_left), yc + R_wing * sin(angle + offset_left),
            xc + R_back * cos(angle + offset_back), yc + R_back * sin(angle + offset_back));
  

  gfx_line( xc + R_wing * cos(angle + offset_right), yc + R_wing * sin(angle + offset_right),
            xc + R_back * cos(angle + offset_back), yc + R_back * sin(angle + offset_back));


}

void wall_collision(float *pxc, float *pyc, float *pdx, float *pdy, float angle, int SIZE_SHIP, int wid, int ht){
  if ((*pxc + SIZE_SHIP * 0.9) >= wid) {
    *pdx = -(*pdx);
    *pxc = wid - (SIZE_SHIP * 0.9) * 2;
    *pxc += *pdx; // this prevents the "stuck on edge" bug
  }

  if ((*pyc + SIZE_SHIP * 0.9) >= ht) {
    *pdy = -(*pdy);
    *pyc = ht - SIZE_SHIP * 0.9;
    *pyc += *pdy; // this prevents the "stuck on edge" bug
  }

  if ((*pxc - SIZE_SHIP * 0.9) <= 0) {
    *pdx = -(*pdx);
    *pxc = 0 + SIZE_SHIP * 0.9;
    *pxc += *pdx; // this prevents the "stuck on edge" bug
  }

  if ((*pyc - SIZE_SHIP * 0.9) <= 0) {
    *pdy = -(*pdy);
    *pyc = 0 + SIZE_SHIP * 0.9;
    *pyc += *pdy; // this prevents the "stuck on edge" bug
  }

}

void drawAsteroid(float *pxc, float *pyc, int radius, float dx, float dy, int type){
  
  gfx_color(200, 200, 200);  // gray color for asteroids
  
  if (type == 1) {
    // type 1: irregular octagon
    float angles[8] = {0, M_PI/4, M_PI/2, 3*M_PI/4, M_PI, 5*M_PI/4, 3*M_PI/2, 7*M_PI/4};
    float radii[8] = {0.9, 0.7, 0.85, 0.75, 0.95, 0.8, 0.9, 0.7};  //different radius for each point
    
    for (int i = 0; i < 8; i++) {
      int next = (i + 1) % 8;
      int x1 = *pxc + radius * radii[i] * cos(angles[i]) + dx;
      int y1 = *pyc + radius * radii[i] * sin(angles[i]) + dy;
      int x2 = *pxc + radius * radii[next] * cos(angles[next]) + dx;
      int y2 = *pyc + radius * radii[next] * sin(angles[next]) + dy;
      gfx_line(x1, y1, x2, y2);
    }
  }
  else if (type == 2) {
    // type 2: jagged hexagon
    float angles[6] = {0, M_PI/3, 2*M_PI/3, M_PI, 4*M_PI/3, 5*M_PI/3};
    float radii[6] = {0.85, 0.95, 0.75, 0.9, 0.7, 0.8}; //different radius for each point
    
    for (int i = 0; i < 6; i++) {
      int next = (i + 1) % 6;
      int x1 = *pxc + radius * radii[i] * cos(angles[i]) + dx;
      int y1 = *pyc + radius * radii[i] * sin(angles[i]) + dy;
      int x2 = *pxc + radius * radii[next] * cos(angles[next]) + dx;
      int y2 = *pyc + radius * radii[next] * sin(angles[next]) + dy;
      gfx_line(x1, y1, x2, y2);
    }
  }
  else {
    // type 3: irregular pentagon with spikes
    float angles[10] = {0, M_PI/5, 2*M_PI/5, 3*M_PI/5, 4*M_PI/5, M_PI, 6*M_PI/5, 7*M_PI/5, 8*M_PI/5, 9*M_PI/5};
    float radii[10] = {0.9, 0.5, 0.85, 0.6, 0.95, 0.55, 0.8, 0.5, 0.9, 0.6};  //different radius for each point
    
    for (int i = 0; i < 10; i++) {
      int next = (i + 1) % 10;
      int x1 = *pxc + radius * radii[i] * cos(angles[i]) + dx;
      int y1 = *pyc + radius * radii[i] * sin(angles[i]) + dy;
      int x2 = *pxc + radius * radii[next] * cos(angles[next]) + dx;
      int y2 = *pyc + radius * radii[next] * sin(angles[next]) + dy;
      gfx_line(x1, y1, x2, y2);
    }
  }

  *pxc += dx;
  *pyc += dy;

}

ObjPosVel ObjectCartesian(int wid, int ht, int maxRadius, int minVel, int maxVel){
  ObjPosVel a;                                       //the structure (rand() % (max - min + 1) + min) 
  int randomSide = rand() % ((4) - 0) + 1 + (0);     //will be maintained to make it easier to substitute the numbers

  if(randomSide == 1){         //the object will be created in the right side of the window
    
    a.xc = wid + maxRadius; 
    a.yc = rand() % ((ht) - 0) + 1 + (0);
    a.dx = rand() % ((minVel) - 0) + 1 + (-maxVel); //negative velocity in x
    a.dy = rand() % ((maxVel) - 0) + 1 + (-maxVel);

  } else if(randomSide == 2){  //the object will be created in the left side of the window
    
    a.xc = (-maxRadius);
    a.yc = rand() % ((ht) - 0) + 1 + (0);
    a.dx = rand() % ((maxVel) - 0) + 1 + (minVel); 
    a.dy = rand() % ((maxVel) - 0) + 1 + (-maxVel);

  } else if(randomSide == 3){  //the object will be created in the upper side of the window
    
    a.yc = (-maxRadius);
    a.xc = rand() % ((wid) - 0) + 1 + (0);
    a.dx = rand() % ((maxVel) - 0) + 1 + (-maxVel); 
    a.dy = rand() % ((maxVel) - 0) + 1 + (minVel);

  } else if(randomSide == 4){  //the object will be created in the bottom side of the window
    
    a.yc = ht + maxRadius;
    a.xc = rand() % ((wid) - 0) + 1 + (0);
    a.dx = rand() % ((maxVel) - 0) + 1 + (-maxVel); 
    a.dy = rand() % ((minVel) - 0) + 1 + (-maxVel);

  }

  return a;
}

int asteroidOutOfBounds(float xc, float yc, int wid, int ht, int margin){
  // checks if asteroid is more than 'margin' (set to 200 pixels) outside the screen
  if(xc < -margin || xc > wid + margin || yc < -margin || yc > ht + margin){
    return 1; // out of bounds
  }
  return 0; // still in bounds
}

void respawnAsteroid(Asteroids *ast, int wid, int ht, int maxRadiusAst, int minRadiusAst, int minVelAst, int maxVelAst){
  ast->radius = rand() % (maxRadiusAst - minRadiusAst + 1) + minRadiusAst;  //new size for the asteroid
  ast->ObjCartesian = ObjectCartesian(wid, ht, maxRadiusAst, minVelAst, maxVelAst); //new position and velocity
  ast->type = rand() % 3 + 1; //new random type with 3 number starting with 1
}

int ship_asteroidCollision(float ship_xc, float ship_yc, int shipSize, float ast_xc, float ast_yc, int astRadius){
  float shipR = shipSize * 0.9f;
  float dx = ship_xc - ast_xc;              //the function computes the distance between the center of the ship
  float dy = ship_yc - ast_yc;              //and the center of the asteroid, then it compares with the sum of the radii from bot hitboxes
  float sumR = shipR + astRadius;
  return (dx*dx + dy*dy) <= (sumR*sumR); 
}

int isClickInButton(int mx, int my, int bx, int by, int bw, int bh){
  return (mx >= bx && mx <= bx + bw && my >= by && my <= by + bh); //checks if mouse position is inside the start box
}

int displayMenu(int wid, int ht, int mx, int my){
  
  gfx_clear();
  
  gfx_color(255, 165, 0);  
  gfx_text(wid / 2 - 85, ht / 2 - 54, "SPACE ODYSSEY");
  
  // subtitle
  gfx_color(100, 200, 255);  
  gfx_text(wid / 2 - 120, ht / 2 - 20, "Dodge the asteroids!");
  
  // start rectangular button
  int btn_x = wid / 2 - 67;
  int btn_y = ht / 2 + 10;
  int btn_w = 120;
  int btn_h = 50;
  
  gfx_color(0, 200, 0);
  gfx_rectangle(btn_x, btn_y, btn_w, btn_h);
  gfx_rectangle(btn_x + 2, btn_y + 2, btn_w - 4, btn_h - 4);
  
  // start text
  gfx_color(255, 255, 255);  // White text
  gfx_text(btn_x + 35, btn_y + 35, "START");

  if(isClickInButton(mx, my, btn_x, btn_y, btn_w, btn_h)){
    gfx_flush();
    return 1;
  } else {
    gfx_flush();
    return 0;
  }
  
  
}

void displayGameOver(int wid, int ht, int finalTime){
  gfx_clear();
  
  //GAME OVER title
  gfx_color(255, 0, 0);  
  gfx_text(wid / 2 - 50, ht / 2 - 40, "GAME OVER");
  
  
  char timeMsg[64];
  snprintf(timeMsg, sizeof(timeMsg), "You survived %d seconds", finalTime);
  gfx_color(255, 255, 255); 
  gfx_text(wid / 2 - 140, ht / 2, timeMsg);
  
  
  gfx_color(100, 200, 255);  
  gfx_text((wid - 180) / 2, ht / 2 + 40, "Press Q to quit");

  gfx_color(100, 200, 255);  
  gfx_text((wid - 220) / 2, ht / 2 + 80, "Press R to restart");
  
  gfx_flush();
}
