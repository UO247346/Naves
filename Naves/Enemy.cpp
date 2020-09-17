#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/enemigo.png", x, y, 36, 40, game) {
	int VxRandom = 1 + (rand() % 12);
	vx = VxRandom;
}

void Enemy::update() {
	
	vx = (this->vx);
	x = x - vx;
	if (x < 0) {
		x = 480;
	}
}