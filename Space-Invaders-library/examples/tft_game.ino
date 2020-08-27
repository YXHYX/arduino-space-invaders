//game engine

#include "Game.h"

//This Game Engine is supposed to help create games easily 

//Defines for TFT
#define __CS 10
#define __DC 9

//Create a TFT object
TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC);

//Create a Game object
Game game(&tft, A2, A3, 7, 6);

void setup()
{
     //for random
     randomSeed(analogRead(0));
     game.init();
     pinMode(A0, INPUT);
     pinMode(A1, INPUT);
     pinMode(7, INPUT_PULLUP);
     pinMode(6, OUTPUT);
}
void loop()
{
     game.run(100); //run the on an interval of 100;
}
