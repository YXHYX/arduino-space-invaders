#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Enemy.h"

class Level
{
	
private:
	
	int m_difficulty;
	int VRx;
	int VRy; 
	int SW; 
	int B;
	int enemyAmount;
	
	bool levelCompleted;
	bool playerAlive;
	
	Player* m_player;
	Enemy* m_enemyArray[15];
	TFT_ILI9163C *m_tft;
	
	//Getters
	bool enemiesDead();
	
public:
	Level(int difficulty, TFT_ILI9163C *tft, int VRx, int VRy, int SW, int B);
	virtual ~Level();
	
	//Getters
	int getScore();
	bool getLevelCompleted();
	bool getPlayerAlive();
	int getDifficulty();
	//Setters
	void setDifficulty(int difficulty);

	//Initializers
	void init(int difficulty, TFT_ILI9163C *tft, int VRx, int VRy, int SW, int B);
	void initPlayer(TFT_ILI9163C *tft, int VRx, int VRy, int SW, int B);
	void initEnemies(int amount, TFT_ILI9163C *m_tft, int B);
	
	//functions
	void levelComplete();
	
	void update();
	void render();
	
};

#endif