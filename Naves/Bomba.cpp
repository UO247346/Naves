#include "Bomba.h"

Bomba::Bomba(float x, float y, Game* game) :
	Actor("res/bomba.png", x, y, 30, 30, game) {
	vx = 5;
}

void Bomba::update() {
	x = x - vx;
}