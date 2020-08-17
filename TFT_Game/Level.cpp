#include "Level.h"


//Constructor / Destructor
Level::Level(int difficulty, TFT_ILI9163C *tft, int VRx, int VRy, int SW, int B)
	: m_tft(m_tft), VRx(VRx), VRy(VRy), SW(SW), B(B)
{
	this->init(difficulty, tft, VRx, VRy, SW, B);
	this->levelCompleted = false;
}

Level::~Level()
{
	delete this->m_player;
	delete this->m_tft;
	for(int i = 0; i < 20; i++)
		delete this->m_enemyArray[i];
}

//Getters

bool Level::enemiesDead()
{
	for(int i = 0; i < this->enemyAmount; i++)
		if(this->m_enemyArray[i]->getAlive())
				return false;
	return true;
}

int Level::getScore()
{
	return this->m_player->getScore();
}

bool Level::getLevelCompleted()
{
	return this->levelCompleted;
}

//Setters
void Level::setDifficulty(int difficulty)
{
	this->m_difficulty = difficulty;
}

//Initializers
void Level::init(int difficulty, TFT_ILI9163C *tft, int VRx, int VRy, int SW, int B)
{
	this->setDifficulty(difficulty);
	this->initPlayer(tft, VRx, VRy, SW, B);
	
	switch(this->m_difficulty)
	{
			//easy difficulty
		case 1:
			this->initEnemies(3, tft, B);
			break;
			
			//normal difficulty
		case 2:
			this->initEnemies(6, tft, B);
			break;
			
			//hard difficulty
		case 3:
			this->initEnemies(10, tft, B);
			break;
	}
}

void Level::initPlayer(TFT_ILI9163C *tft, int VRx, int VRy, int SW, int B)
{
	m_player = new Player(tft, VRx, VRy, SW, B);
}

void Level::initEnemies(int amount, TFT_ILI9163C *tft, int B)
{
	this->enemyAmount = amount;
	for(int i = 0; i < this->enemyAmount; i++){
		if(i < 6)
			this->m_enemyArray[i] = new Enemy(tft, (i+2)*16, 80, B);
		else if(i > 5 && i < 11)
			this->m_enemyArray[i] = new Enemy(tft, (i+2-5)*16, 64, B);
		else if(i > 10 && i < 16)
			this->m_enemyArray[i] = new Enemy(tft, (i+2-10)*16, 48, B);
		else if(i > 15 && i < 20)
			this->m_enemyArray[i] = new Enemy(tft, (i+2-15)*16, 32, B);		
	}
}

//Functions

void Level::update()
{
	if(!levelCompleted)
	{
		this->m_player->update();
		for(int i = 0; i < this->enemyAmount; i++){
			if(this->m_enemyArray[i]->getAlive()){
				if(this->m_enemyArray[i]->collide(this->m_player->getBX(), this->m_player->getBY()))
					this->m_player->stopShoot();
			
				if(this->m_enemyArray[i]->collide(this->m_player->getBX(), this->m_player->getBY()))
					this->m_player->addPoints();
				
				//update the enemy
				this->m_enemyArray[i]->update();
				
				//if enemy is dead, do not update nor render it
				if(!this->m_enemyArray[i]->getAlive()){
					this->m_enemyArray[i]->end();
				}
			}
		}
		
		levelCompleted = this->enemiesDead();
	}
}

void Level::render()
{
	this->m_player->render();
	
	for(int i = 0; i < this->enemyAmount; i++){
		if(!this->m_enemyArray[i]->getAlive())
			continue;
		this->m_enemyArray[i]->render();
	}
}