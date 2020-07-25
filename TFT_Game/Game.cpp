#include "Game.h"

Game::Game(TFT_ILI9163C *tft, int VRx, int VRy, int SW, int B) : m_tft(tft){
	m_player         = new Player(tft, VRx, VRy, SW, B);
	//m_enemy			 = new Enemy(tft, random(2,7)*16, random(2,7)*16, B);
	for(int i = 0; i < 3; i++)
		this->m_enemyArray[i] = new Enemy(tft, random(2,7)*16, random(2,7)*16, B); 
	m_gameOver 		 = false;
	m_score 		 = 0;
	m_currentMillis  = 0;
	m_previousMillis = 0;
}
Game::~Game(){
	delete m_tft;
	delete m_player;
	for(int i = 0; i < 3; i++)
		delete m_enemyArray[i];
	//delete m_enemy;
}

void Game::showScore(bool on){
	if(!on)
	{
		m_tft->fillRect(0, 0, 127, 16, BLACK);
		return;
	}
	m_tft->fillRect(0, 0, 127, 16, BLACK);
	m_tft->setCursor(8, 2);
	m_tft->setTextColor(WHITE);  
	m_tft->setTextSize(2);
	m_tft->print("Score:");
	m_tft->print(this->m_player->getScore());
}

void Game::run(int interval){
	while(!m_gameOver){
		m_currentMillis = millis();
        // update the game if 100 millisecond has passed
        if(m_currentMillis - m_previousMillis >= interval)
        {
			update();
			render();
            m_previousMillis = m_currentMillis;
        }
	}
}
void Game::update(){
	
	
	
	//update player
	this->m_player->update();
	
	
	for(int i = 0; i < 3; i++){

		this->m_player->shoot(this->m_enemyArray[i]->collide(this->m_player->getBX(), this->m_player->getBY()));
		
		if(!(this->m_enemyArray[i] == null)){
			if(this->m_enemyArray[i]->collide(this->m_player->getBX(), this->m_player->getBY()))
				this->m_player->addPoints();

			//check if enemy is alive
			if(this->m_enemyArray[i]->getAlive() || !(this->m_enemyArray[i] == null)){
				this->m_enemyArray[i]->update();
			}
			//if enemy isnt alive assign it to null
			if(!this->m_enemyArray[i]->getAlive() || this->m_enemyArray[i] == null){
				if(this->m_enemyArray[i] == null)
					return;
				this->m_enemyArray[i]->end();
				this->m_enemyArray[i] = null;
			}
		}
	}
}

void Game::render(){
	if(this->m_player->getScore() != this->m_score){
		showScore(true);
		this->m_score = this->m_player->getScore();
	}
	this->m_player->render();
	for(int i = 0; i < 3; i++){
	if(this->m_enemyArray[i] == null)
			return;
	this->m_enemyArray[i]->render();
	}
}

void Game::init(){

	m_tft->begin();
	m_tft->fillScreen();
	
	for(int i = 1; i < 4; i++)
	{
		m_tft->setRotation(i);
		m_tft->fillScreen();
	}
	m_tft->setRotation(2);
	showScore(true);
}
