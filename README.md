# arduino-space-invaders
Space invaders game using an Arduino Uno and a TFT display 

## Installation
Download the code, extract the library and install it on Arduino IDE by copying it to the libraries folder in the Arduino folder.

## Requirements
You will need some libraries
```
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

```

## Usage
Here is an example of the library

```cpp
//Include the library
#include "Game.h"

//This Game Engine is supposed to help create games easily 

//Defines for TFT
#define __CS 10
#define __DC 9

//Create a TFT object
TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC);

//Create a Game object
Game game(&tft, A1, A2, 7, 6);

void setup()
{
     //for random
     randomSeed(analogRead(0));
     //intialize the game
     game.init();
     //before running the game, we've go to set up the some pins to inputs and outputs
     pinMode(A1, INPUT); //joystick X axis pin
     pinMode(A2, INPUT); //joystick Y axis pin
     pinMode(7, INPUT_PULLUP); //joystick Button pin
     pinMode(6, OUTPUT); //buzzer pin
}
void loop()
{
     game.run(100); //run the game on an interval of 100ms without using delay;
}
```


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
