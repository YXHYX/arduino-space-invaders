#include "Enemy.h"
//constructor 
Enemy::Enemy(TFT_ILI9163C *tft, int x, int y, int B) : m_tft(tft) {
	m_x = x, m_y 	= y; 	//intialize position
	m_bulletx = 0, m_bullety = 0;
	animationFrame 	= 0; 	//intialize frame of animation
	alive 			= true;	//intialize life state
	buzzer			= B;	//intialize the buzzer
	timer 			= random(70, 100);
}
//deconstructor
Enemy::~Enemy(){
	delete m_tft; //yeet that pointer
}
//check collisions idk
bool Enemy::collide(int x1, int y1){
	if(x1 < m_x + 12 &&
		x1 + 12 > m_x &&
		y1 < m_y + 8 &&
		y1 + 8 > m_y){
		//collision detected
		this->m_tft->fillRect(m_x, m_y, 11, 8, BLACK);
		this->m_tft->drawLine(this->m_bulletx, this->m_bullety-8, this->m_bulletx, this->m_bullety+8, BLACK);
		tone(buzzer, 300, 130);
		this->m_tft->fillRect(m_x, m_y, 12, 10, BLACK);	
		alive = false; //dead
		return true;
	}
	return false;
}

void Enemy::shoot()
{
	this->timer++;
	if(this->timer == 150){	
		this->m_bulletx = this->m_x + random(0, 6);
		this->m_bullety = this->m_y;
		this->shootBullet = true;
		tone(buzzer, 1200, 50);
		this->timer = random(0, 100);
	}
	
	if(this->shootBullet == true)
	{
		this->m_bullety -= 4;
		this->m_tft->drawLine(this->m_bulletx, this->m_bullety, this->m_bulletx, this->m_bullety+8, BLACK);

		if(this->m_bullety > 23)
			this->m_tft->drawLine(this->m_bulletx, this->m_bullety-8, this->m_bulletx, this->m_bullety, GREEN);

		if(this->m_bullety < 24){
			this->m_bullety = this->m_y;
			this->shootBullet = false;
		}
	}
}

void Enemy::update(){
	
	if(animationFrame == 5)
		animationFrame = -1;
	else
		animationFrame++;
	shoot();
}
void Enemy::render(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 11; j++){
			if(animationFrame < 3 && animationFrame >= 0){
				if(invader1[i][j] == 0)
					m_tft->drawPixel(m_x+j, m_y+i, BLACK);
				else
					m_tft->drawPixel(m_x+j, m_y+i, WHITE);
			}
				
			if(animationFrame < 6 && animationFrame >= 3){
				if(invader2[i][j] == 0)
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

int Enemy::getBulletX(){
	return this->m_bulletx;
}

int Enemy::getBulletY(){
	return this->m_bullety;
}
