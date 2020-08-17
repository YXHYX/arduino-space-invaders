#ifndef GAME_H
#define GAME_H

// Includes
#include "Level.h"

// Defines
#define null 0

/*namespace
{

}*/

class Game
{
public:


private:

	//Game variables
	int m_score;
	bool m_gameOver;
	int m_difficulty;
	Level* m_level;

	int VRx;
	int VRy;
	int SW;
	int B;
	//time variables
	long m_currentMillis;
	long m_previousMillis;

	TFT_ILI9163C *m_tft;
public:
    Game(TFT_ILI9163C *tft, int VRx, int VR, int SW, int B);
    virtual ~Game();
	
	
	void showScore(bool on);
	void levelComplete();
	
	void run(int interval);
    void render();
    void update();

	void init();

};

#endif // GAMEENGINE_H
