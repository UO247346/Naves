
#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include <list>
#include "Text.h"
#include "Vidas.h"
#include "Audio.h" 
#include "Moneda.h"
#include "Bomba.h"
class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	Audio* audioBackground;
	Text* textPoints;
	Vidas* textLives;
	int points;
	int vidas;
	int newEnemyTime = 0;
	int newMonedaTime = 0;
	int newBombaTime = 0;
	//Declaraciones de los objetos del juego
	Actor* backgroundPoints;
	Actor* backgroundLives;
	Player* player1;//Jugador1
	Player* player2;//Jugador2
	Background* background;//Fondo
	bool controlShoot1 = false;
	bool controlShoot2 = false;
	int controlMoveY1 = 0;
	int controlMoveX1 = 0;
	int controlMoveY2 = 0;
	int controlMoveX2 = 0;
	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list <Moneda*> monedas;
	list <Bomba*> bombas;
};


