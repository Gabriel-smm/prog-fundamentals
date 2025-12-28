//funanim.c
//Gabriel Marques
//this program creates a fun animation of a various polygons
#include "Gamefunc.h"


int main()
{

  srand(time(0));  //this will generate a new seed every time the time is incremented
  int wid = 1250, ht = 630;
  SpaceShip ship = {20, wid / 2, ht / 2, M_PI / 2, 0, 0};

  int minVelAst = 3, maxVelAst = 14; //velocity in module
  int minRadiusAst = ship.size, maxRadiusAst = 80;
  Asteroids o1 = {rand() % (maxRadiusAst - minRadiusAst + 1) + (minRadiusAst), //(rand() % (max - min + 1) + min)
                  ObjectCartesian(wid, ht, maxRadiusAst, minVelAst, maxVelAst),
                  rand() % ((3) - (0) + 1) + (1)};
  
  Asteroids o2 = {rand() % (maxRadiusAst - minRadiusAst + 1) + (minRadiusAst), //(rand() % (max - min + 1) + min)
                ObjectCartesian(wid, ht, maxRadiusAst, minVelAst, maxVelAst),
                rand() % ((3) - (0) + 1) + (1)};


  time_t startTime = time(NULL); // track total play time
  //declaring here prevents the loop from declaring the varible multimple times
  int lives = 3;  
  int invincible = 0;  // invincibility frames after hit
  int invincibleTimer = 0;
  int elapsedSec; 
  char timerText[32];
  char livesText[32];

  


  gfx_open(wid, ht, "SPACE ODYSSEY");
  gfx_changefont("12x24"); // font size for timer

  gfx_clear_color(0,0,0); 
  gfx_clear();

  //display menu until player clicks START
  int gameStarted = 0;
  displayMenu(wid, ht, 0, 0); //first initiate the static image outside the loop, 
                              //which is what will appear on the screen if the user dont press anything 
  
  while(!gameStarted){
    if(gfx_event_waiting()){
      char c = gfx_wait();
      if(c == 'q') return 0;
      if (c == 1){
        int mx = gfx_xpos();
        int my = gfx_ypos();
        gameStarted = displayMenu(wid, ht, mx, my); //calling the display again if the user press some key
      }
      
    }
    usleep(2000);  //small delay prevents excessive CPU usage
  }

  while(1){

    while (gfx_event_waiting()) {
        char c = gfx_wait();
        if (c == 'q') return 0;
        if (c == 'a') ship.angle -= 0.4; //sensibility of ship's rotation
        if (c == 'd') ship.angle += 0.4;
        if (c == 'w') {
          ship.dx += cos(ship.angle) * 0.35; //ship's velocity
          ship.dy += sin(ship.angle) * 0.35; 
          if (ship.dx > 7) ship.dx = 7;     //the following lines limit the ship's terminal veloctity
          if (ship.dx < -7) ship.dx = -7;
          if (ship.dy > 7) ship.dy = 7;
          if (ship.dy < -7) ship.dy = -7;
        }
      }
    
    //this causes drifting
    ship.xc += ship.dx;
    ship.yc += ship.dy;

    gfx_clear();
    elapsedSec = (int)difftime(time(NULL), startTime);
    
    //draw timer
    snprintf(timerText, sizeof(timerText), "Time: %ds", elapsedSec);
    gfx_color(255, 255, 255);
    gfx_text(wid - 130, 40, timerText);
    
    //draw HP/Lives
    snprintf(livesText, sizeof(livesText), "Lives: %d", lives); //this is a way to format and print inputs other than strings securely (through a buffer)
    gfx_color(255, 100, 100);
    gfx_text(20, 40, livesText);
    
    //invincibility timer - makes the user "untouchable", for a brief moment
    if(invincible){
      invincibleTimer--;
      if(invincibleTimer <= 0){
        invincible = 0;
      }
    }
    
    wall_collision(&ship.xc, &ship.yc, &ship.dx, &ship.dy, ship.angle, ship.size, wid, ht);
    
    // makes the ship flash during invincibility
    if(!invincible || (invincibleTimer % 10 < 5)){
      drawShip(ship.xc, ship.yc, ship.size, ship.angle);
    }
    
    // checks if asteroid is out of bounds (200 pixels outside screen) and respawn
    if(asteroidOutOfBounds(o1.ObjCartesian.xc, o1.ObjCartesian.yc, wid, ht, 200)){
      respawnAsteroid(&o1, wid, ht, maxRadiusAst, minRadiusAst, minVelAst, maxVelAst);
    }
    if(asteroidOutOfBounds(o2.ObjCartesian.xc, o2.ObjCartesian.yc, wid, ht, 200)){
      respawnAsteroid(&o2, wid, ht, maxRadiusAst, minRadiusAst, minVelAst, maxVelAst);
    }
    
    //collision detection and lives handling
    if(!invincible && (ship_asteroidCollision(ship.xc, ship.yc, ship.size, o1.ObjCartesian.xc, o1.ObjCartesian.yc, o1.radius) 
                       || ship_asteroidCollision(ship.xc, ship.yc, ship.size, o2.ObjCartesian.xc, o2.ObjCartesian.yc, o2.radius))){

      lives--;
      invincible = 1;
      invincibleTimer = 60;  // ~1 second of invincibility, 60 iterations of the loop (so it depends on the number in usleep())
      
      //reset ship to the center after losing HP 
      ship.angle = M_PI / 2;
      ship.xc = wid/2;
      ship.yc = ht/2;
      ship.dy = 0;
      ship.dx = 0;
      
      respawnAsteroid(&o1, wid, ht, maxRadiusAst, minRadiusAst, minVelAst, maxVelAst);
      drawAsteroid(&o1.ObjCartesian.xc, &o1.ObjCartesian.yc, o1.radius, o1.ObjCartesian.dx, o1.ObjCartesian.dy, o1.type);
      respawnAsteroid(&o2, wid, ht, maxRadiusAst, minRadiusAst, minVelAst, maxVelAst);
      drawAsteroid(&o2.ObjCartesian.xc, &o2.ObjCartesian.yc, o2.radius, o2.ObjCartesian.dx, o2.ObjCartesian.dy, o2.type);      

      //check game over
      if(lives <= 0){
        displayGameOver(wid, ht, elapsedSec);
        // Wait for quit
        while(1){
          if(gfx_event_waiting()){
            char c = gfx_wait();
            if(c == 'q') return 0;
            if(c == 'r'){
              startTime = time(NULL);
              lives = 3;
              break;
            }
          }
          usleep(12000); //12ms
        }
      }
    }
    
    drawAsteroid(&o1.ObjCartesian.xc, &o1.ObjCartesian.yc, o1.radius, o1.ObjCartesian.dx, o1.ObjCartesian.dy, o1.type);
    drawAsteroid(&o2.ObjCartesian.xc, &o2.ObjCartesian.yc, o2.radius, o2.ObjCartesian.dx, o2.ObjCartesian.dy, o2.type);
    gfx_flush();
    usleep(18000);  //18ms

  }

    
  return 0;
}



