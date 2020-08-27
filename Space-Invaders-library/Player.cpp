#include "Player.h"

Player::Player(TFT_ILI9163C *tft, int VRx, int VRy, int SW, int B)
: tft(tft), VRx(VRx), VRy(VRy), SW(SW){
	this->x = 32, this->y = 32;
	
	this->bulletx = 0, this->bullety = 0;
	this->bulletShoot = false;
	this->prevx = 0, this->prevy = 0;
	this->score = 0;
	this->buzzer = B;
	
	this->alive = true;
}

Player::~Player(){
    delete tft;
}

void Player::shoot(){
	
	if(digitalRead(SW) == false){
		if(bulletShoot == false){
			this->bulletx = this->x+4;
			this->bullety = this->y;
			tone(this->buzzer, 1000, 100);
			this->bulletShoot = true;
		}
	}
	if(bulletShoot == true){
	
		bullety += 8;
		
		this->tft->drawLine(this->bulletx, this->bullety, this->bulletx, this->bullety+8, LIME);
		this->tft->drawLine(this->bulletx, this->bullety-8, this->bulletx, this->bullety, BLACK);
		if(bullety > 150)
		{
			//this->tft->drawLine(this->bulletx, this->bullety, this->bulletx, this->bullety+8, BLACK);
			bulletShoot = false;
		}
	}
}

void Player::stopShoot()
{
	this->tft->drawLine(this->bulletx, this->bullety, this->bulletx, this->bullety+8, BLACK);
	bulletShoot = false;
}

int Player::getScore(){
	return this->score;
}

void Player::addPoints(int points){
	this->score = this->score + points;
}	

bool Player::collide(int x1, int y1){
	
	if( x1 < x + 12 &&
		x1 + 12 > x &&
		y1 < y + 8 &&
		y1 + 8 > y)
	{
		tone(buzzer, 200, 150);
		alive = false;
		return true;
	}
	
	return false;
}

void Player::update(){
	this->prevx = x;
	this->prevy = y;
	if(map(analogRead(VRx), 0, 1023, 0, 127) > 84)
		x += 4;
	else if(map(analogRead(VRx), 0, 1023, 0, 127) < 44)
		x -= 4;
	if(map(analogRead(VRy), 0, 1023, 0, 127) > 84)
		y += 4;
	else if(map(analogRead(VRy), 0, 1023, 0, 127) < 44)
		y -= 4;
	if(x > 120)
		x = 120;
	else if (x < 8)
		x = 8;
	
	if(y > 120)
		y = 120;
	else if (y < 18)
		y = 18;
	this->shoot();
}

void Player::render(){
	if(x != prevx || y != prevy){
		tft->fillRect(prevx, prevy, 8, 8, BLACK);
		tft->fillTriangle(prevx+8, prevy, prevx+8, prevy+4, prevx+16, prevy, BLACK);
		tft->fillTriangle(prevx, prevy, prevx, prevy+4, prevx-8, prevy, BLACK);
	}
	tft->fillRect(x, y, 8, 8, CYAN);
	tft->fillTriangle(x+8, y, x+8, y+4, x+16, y, DARK_CYAN);
	tft->fillTriangle(x, y, x, y+4, x-8, y, DARK_CYAN);
}

int Player::getBX(){
	return this->bulletx;
}

int Player::getBY(){
	return this->bullety;
}

bool Player::getAlive(){
	return this->alive;
}
