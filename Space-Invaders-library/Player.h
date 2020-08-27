#ifndef PLAYER_H
#define PLAYER_H

// Includes
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

// Defines

#define BLACK     0x0000
#define BLUE      0x001F
#define RED       0xF800
#define GREEN     0x07E0
#define LIME	  0x2EFF
#define CYAN      0x07FF
#define DARK_CYAN 0x0DCB
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define WHITE     0xFFFF

class Player
{
private:
	int x,y;
	int prevx,prevy; //used to clear (better than fillScreen()!!)
	
	int buzzer; //for the buzzer
	
	int bulletx, bullety;
	
	bool bulletShoot;
	
	bool alive;
	
	int score;
	
    TFT_ILI9163C *tft;
	int VRx, VRy, SW;

public:
	Player(TFT_ILI9163C *tft, int VRx, int VRy, int SW, int B);
	virtual ~Player();

	int getScore();
	
	int getBX();
	int getBY();
	bool collide(int x1, int y1);
	
	bool getAlive();
	
	void shoot();
	void stopShoot();
	void addPoints(int points = 10);
	
    void update();
    void render();
	
	
};
#endif  PLAYER_H
