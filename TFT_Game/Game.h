#ifndef GAME_H
#define GAME_H

// Includes
#include "Player.h"
#include "Enemy.h"

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
    Player* m_player;
	Enemy* m_enemyArray[3];
	
	

	//time variables
	long m_currentMillis;
	long m_previousMillis;

	TFT_ILI9163C *m_tft;
public:
    Game(TFT_ILI9163C *tft, int VRx, int VR, int SW, int B);
    virtual ~Game();
	
	
	void showScore(bool on);
	
	void run(int interval);
    void render();
    void update();

	void init();

};

#endif // GAMEENGINE_H
