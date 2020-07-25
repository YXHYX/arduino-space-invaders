#include "Enemy.h"
//constructor 
Enemy::Enemy(TFT_ILI9163C *tft, int x, int y, int B) : m_tft(tft) {
	m_x = x, m_y 	= y; 	//intialize position
	animationFrame 	= 0; 	//intialize frame of animation
	alive 			= true;	//intialize life state
	buzzer			= B;	//intialize the buzzer
}
//deconstructor
Enemy::~Enemy(){
	delete m_tft; //yeet that pointer
}

void Enemy::end(){
	tone(buzzer, 300, 130);
	this->m_tft->fillRect(m_x, m_y, 12, 10, BLACK);		
	return;
}
//check collisions idk
bool Enemy::collide(int x1, int y1){
	if(x1 < m_x + 8 &&
		x1 + 8 > m_x &&
		y1 < m_y + 8 &&
		y1 + 8 > m_y){
		//collision detected
		alive = false; //dead
		return true;
	}
	return false;
}
void Enemy::update(){
	
	if(alive == false)
		return;
	if(animationFrame == 5)
		animationFrame = -1;
	else
		animationFrame++;
}
void Enemy::render(){
	
	if(alive == false)
	{
		this->m_tft->fillRect(m_x, m_y, 11, 8, BLACK);		
		return;
	}
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 11; j++){
			if(animationFrame < 3 && animationFrame >= 0){
				if(this->invader1[i][j] == 0)
					m_tft->drawPixel(m_x+j, m_y+i, BLACK);
				else
					m_tft->drawPixel(m_x+j, m_y+i, WHITE);
			}
				
			if(animationFrame < 6 && animationFrame >= 3){
				if(this->invader2[i][j] == 0)
					m_tft->drawPixel(m_x+j, m_y+i, BLACK);
				else
					m_tft->drawPixel(m_x+j, m_y+i, WHITE);
			
			}
		}	
	}
}

bool Enemy::getAlive(){
	return this->alive;
}

int Enemy::getX(){
	return this->m_x;
}

int Enemy::getY(){
	return this->m_y;
}