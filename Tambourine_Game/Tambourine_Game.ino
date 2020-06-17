#include <Tinyfont.h>
#include <Arduboy2.h>


#include "Sprite.h"


Arduboy2 arduboy;
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

enum class GameState
{
  MainMenu,
  Gameplay,
  Subscribe,
};

GameState gameState = GameState::MainMenu;

int points;

bool tap;

bool yes;
bool no;

void reset()
{
  points = 0;
  tap = false;
  yes = false;
  no = false;
  gameState = GameState::MainMenu;
}

void setup() {
  arduboy.begin();
  reset();
  Serial.begin(9600);

}

void loop() {

  Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
  
  if(!arduboy.nextFrame())
    return;
  arduboy.pollButtons();

  arduboy.clear();

  switch (gameState)
  {
    case GameState::MainMenu:
      updateMainMenu();
      drawMainMenu();
      break;
      
    case GameState::Gameplay:
      updateGameplay();
      drawGameplay();
      break;
    case GameState::Subscribe:
      updateSubscribe();
      drawSubscribe();
  }

  arduboy.display();
}

void updateMainMenu()
{
  if(arduboy.justPressed(A_BUTTON))
  {
    gameState = GameState::Gameplay;
  }
}

void drawMainMenu()
{
  arduboy.setCursor(20,15);
  arduboy.print("Pewds Tambourine");

  tinyfont.setCursor(18,25);
  tinyfont.print("By u/AshteroidePlayz");

  arduboy.setCursor(25,40);
  arduboy.print("Floor Gang Ouh!");
  arduboy.setCursor(35,50);
  arduboy.print("-Pewdiepie");
}

void updateGameplay()
{
  if(arduboy.pressed(A_BUTTON)) {
    tap = true;
  if(arduboy.justPressed(A_BUTTON)) {
    ++points;
  }
  } else {
    tap = false;
  }
}

void updateSubscribe() {
  if(arduboy.justPressed(DOWN_BUTTON)) {
    yes = false;
    no = true;
  }
  if(arduboy.justPressed(UP_BUTTON)) {
    no = false;
    yes = true;
  }
}

void drawSubscribe() {
  arduboy.clear();
  arduboy.setCursor(5,10);
  arduboy.print("Are you Subscribed?");
  arduboy.setCursor(45,20);
  arduboy.print("Up: Yes");
  arduboy.setCursor(45,30);
  arduboy.print("Down: No");

  if(yes == true) {
    arduboy.clear();
    arduboy.setCursor(30,20);
    arduboy.print("YOU GET BIG PP");
    arduboy.display();
    delay(2000);
    reset();
  }else if(no == true) {
    arduboy.clear();
    arduboy.setCursor(40,20);
    arduboy.print("SMALL PP");
    arduboy.setCursor(10,30);
    arduboy.print("Subscribe to regain");
    arduboy.setCursor(35,40);
    arduboy.print("PP Increase");
    arduboy.display();
    delay(2000);
    reset();
  }
}

void drawGameplay() {
  arduboy.print("PP Increase: ");
  arduboy.print(points);
  arduboy.print("%");
  if(tap == true) {
    arduboy.drawBitmap(60,15,Hand,48,56,WHITE);
    arduboy.drawBitmap(0,10,Tamb,120,64,WHITE);
    arduboy.setCursor(2,12);
    arduboy.print("Floor Gang!");
  } else {
    arduboy.drawBitmap(85,20,Hand,48,56,WHITE);
    arduboy.drawBitmap(0,10,Tamb,120,64,WHITE);
  }
  if (points == 25) {
    gameState = GameState::Subscribe;
  }
  arduboy.display();
}
