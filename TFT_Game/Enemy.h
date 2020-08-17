#ifndef ENEMY_H
#define ENEMY_H

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


namespace{
	bool invader1[8][11] = // frame animation 1
	{
		{0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
		{1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}
	};
	bool invader2[8][11] = // frame animation 1
	{
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		{1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}
	};
}

// Enemy class
class Enemy
{
private:
	int m_x, m_y; //position of enemy
	int m_prevx, m_prevy; //previous posiotion of enemy
	
	int buzzer; // for buzzer
	
	bool alive; //life state of enemy
	
	int animationFrame; //animation frame of enemy
	
	
	
	TFT_ILI9163C *m_tft; // a pointer to the display

public:
	// Constructor // Destructor
	Enemy(TFT_ILI9163C *m_tft, int x, int y, int B);
	virtual ~Enemy();
	
	//Getters
	bool getAlive();
	int getX();
	int getY();
	
	//functions
	void end();
	bool collide(int x1, int y1);
	void update();
	void render();
};

#endif // !ENEMY_H