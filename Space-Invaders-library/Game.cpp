#include "Game.h"

Game::Game(TFT_ILI9163C *tft, int VRx, int VRy, int SW, int B) 
	: m_tft(tft), VRx(VRx), VRy(VRy), SW(SW), B(B)
{	
	m_gameOver 		 = false;
	m_score 		 = 0;
	m_currentMillis  = 0;
	m_previousMillis = 0;
	m_levelScore 	 = 0;
	m_difficulty 	 = 1;
	this->m_level 	 = new Level(m_difficulty, m_tft, VRx, VRy, SW, B);
}
Game::~Game(){
	delete m_tft;
	delete m_level;
}

void Game::showScore(bool on){
	if(!on)
	{
		m_tft->fillRect(0, 0, 127, 16, BLACK);
		return;
	}
	
	this->m_levelScore = this->m_level->getScore();
	
	this->m_score += this->m_levelScore / this->m_levelScore;
	
	m_tft->fillRect(0, 0, 127, 16, BLACK);
	m_tft->setCursor(8, 2);
	m_tft->setTextColor(WHITE);  
	m_tft->setTextSize(2);
	m_tft->print("Score:");
	m_tft->print(this->m_score);
	this->m_tft->drawLine(0, 16, 128, 16, CYAN);
}

void Game::run(int interval){
	while(!m_gameOver){
		m_currentMillis = millis();
        // update the game if 100 millisecond has passed
        if(m_currentMillis - m_previousMillis >= interval){
			update();
			render();
            m_previousMillis = m_currentMillis;
        }
	}
}

void Game::levelComplete()
{
	if(m_difficulty > 4)
		m_difficulty = 0;
	
	this->m_tft->setCursor(16, 32);
	this->m_tft->setTextColor(GREEN);  
	this->m_tft->setTextSize(1);
	this->m_tft->println("Level Complete!"); 
	this->m_tft->setCursor(14, 48);
	this->m_tft->println("Press joystick's");
	this->m_tft->setCursor(12, 56);
	this->m_tft->println("button to continue.");
	
	
	if(digitalRead(this->SW) == false)
	{
		Serial.println(m_difficulty);
		m_difficulty++;
		Serial.println(m_difficulty);
		m_level = null;
		this->m_tft->fillScreen();
		showScore(true);
		this->m_level = new Level(m_difficulty, m_tft, VRx, VRy, SW, B);
	}
}

void Game::levelOver()
{
	this->m_tft->setCursor(16, 32);
	this->m_tft->setTextColor(GREEN);  
	this->m_tft->setTextSize(1);
	this->m_tft->println("Level Over!"); 
	this->m_tft->setCursor(14, 48);
	this->m_tft->println("Press joystick's");
	this->m_tft->setCursor(12, 56);
	this->m_tft->println("button to retry.");
	
	
	if(digitalRead(this->SW) == false)
	{
		m_level = null;
		this->m_tft->fillScreen();
		showScore(true);
		this->m_level = new Level(m_difficulty, m_tft, VRx, VRy, SW, B);
	}
}

void Game::update(){
	this->m_level->update();
	
	if(this->m_levelScore != this->m_level->getScore())
		this->showScore(true);
}

void Game::render(){
	this->m_level->render();
	
	if(this->m_level->getLevelCompleted() || !this->m_level->getPlayerAlive())
		this->m_tft->fillScreen();
	
	while(!this->m_level->getPlayerAlive() || this->m_level == null)
	{
		this->levelOver();
	}
	
	while(this->m_level->getLevelCompleted() || this->m_level == null)
	{
		this->levelComplete();
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
	//8, 2
}
