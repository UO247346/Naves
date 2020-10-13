#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {
	//Audio
	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();
	//Puntos
	points = 0;
	textPoints = new Text("hola", WIDTH * 0.92, HEIGHT * 0.04, game);
	textPoints->content = to_string(points);
	//Vidas
	vidas = 3;
	textLives = new Vidas("hola", WIDTH * 0.15, HEIGHT * 0.04, game);
	textLives->content = to_string(vidas);
	//Jugador 1
	player1 = new Player(50, 50, game, "res/jugador_nave.png");
	//Jugador 2
	player2 = new Player(50, 50, game, "res/jugador_nave.png");
	//Fondo
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5,-1, game);//Usando el nuevo constructor
	//Pubntos
	backgroundPoints = new Actor("res/icono_puntos.png",
		WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);
	//Vidas
	backgroundLives = new Actor("res/corazon.png",
		WIDTH * 0.05, HEIGHT * 0.10, 45, 45, game);
	projectiles.clear(); // Vaciar por si reiniciamos el juego
	enemies.clear(); // Vaciar por si reiniciamos el juego
	monedas.clear();// Vaciar por si reiniciamos el juego
	enemies.push_back(new Enemy(300, 50, game));
	enemies.push_back(new Enemy(300, 200, game));


}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}
	//procesar controles
	// Disparar 1
	if (controlShoot1) {
		Projectile* newProjectile = player1->shoot();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
		}
	}
	// Disparar2
	if (controlShoot2) {
		Projectile* newProjectile = player2->shoot();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
		}
	}
	//Jugador 1
	// Eje X1
	if (controlMoveX1 > 0) {
		player1->moveX(1);
	}
	else if (controlMoveX1 < 0) {
		player1->moveX(-1);
	}
	else {
		player1->moveX(0);
	}

	// Eje Y1
	if (controlMoveY1 > 0) {
		player1->moveY(1);
	}
	else if (controlMoveY1 < 0) {
		player1->moveY(-1);
	}
	else {
		player1->moveY(0);
	}
	//Jugador 2
	// Eje X2
	if (controlMoveX2 > 0) {
		player2->moveX(1);
	}
	else if (controlMoveX2 < 0) {
		player2->moveX(-1);
	}
	else {
		player2->moveX(0);
	}

	// Eje Y2
	if (controlMoveY2 > 0) {
		player2->moveY(1);
	}
	else if (controlMoveY2 < 0) {
		player2->moveY(-1);
	}
	else {
		player2->moveY(0);
	}


}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_3:
			player1 = new Player(50, 50, game, "res/Space Invaders/nave.png");
			player2 = new Player(50, 50, game, "res/Space Invaders/nave.png");
			break;
		case SDLK_4:
			player1 = new Player(50, 50, game, "res/jugador_nave.png");
			player2 = new Player(50, 50, game, "res/jugador_nave.png");
			break;
		case SDLK_d: // derecha
			controlMoveX1 = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX1 = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY1 = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY1 = 1;
			break;
		case SDLK_l: // derecha
			controlMoveX2 = 1;
			break;
		case SDLK_j: // izquierda
			controlMoveX2 = -1;
			break;
		case SDLK_i: // arriba
			controlMoveY2 = -1;
			break;
		case SDLK_k: // abajo
			controlMoveY2 = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot1 = true;
			break;
		case SDLK_6: // dispara
			controlShoot2 = true;
			break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX1 == 1) {
				controlMoveX1 = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX1 == -1) {
				controlMoveX1 = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY1 == -1) {
				controlMoveY1 = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY1 == 1) {
				controlMoveY1 = 0;
			}
			break;
		case SDLK_l: // derecha
			if (controlMoveX2 == 1) {
				controlMoveX2 = 0;
			}
			break;
		case SDLK_j: // izquierda
			if (controlMoveX2 == -1) {
				controlMoveX2 = 0;
			}
			break;
		case SDLK_i: // arriba
			if (controlMoveY2 == -1) {
				controlMoveY2 = 0;
			}
			break;
		case SDLK_k: // abajo
			if (controlMoveY2 == 1) {
				controlMoveY2 = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot1 = false;
			break;
		case SDLK_6: // dispara
			controlShoot2 = false;
			break;
		}

	}
	if (event.type == SDL_QUIT) {
		game->loopActive = false;
	}
}

void GameLayer::update() {
	background->update();//Movemos el fondo
	// Generar enemigos y monedas
	newEnemyTime--;
	if (newEnemyTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		enemies.push_back(new Enemy(rX, rY, game));
		newEnemyTime = 110;
	}
	newMonedaTime--;
	if (newMonedaTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		monedas.push_back(new Moneda(rX, rY, game));
		newMonedaTime = 250;
	}
	//Mover al jugador 1
	player1->update();
	//Mover al jugador 2
	player2->update();
	//Actualizar enemigos
	for (auto const& enemy : enemies) {
		enemy->update();
	}
	//Actualizar monedas
	for (auto const& moneda : monedas) {
		moneda->update();
	}
	//Actualizar disparos
	for (auto const& projectile : projectiles) {
		projectile->update();
	}
	// Colisiones , Enemy - Projectile - Monedas
	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	list<Moneda*> deleteMonedas;
	//Eliminar disparos que se salen
	for (auto const& projectile : projectiles) {
		if (projectile->isInRender() == false) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}
	//Colisiones
	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				bool eInList = std::find(deleteEnemies.begin(),
					deleteEnemies.end(),
					enemy) != deleteEnemies.end();

				if (!eInList) {
					deleteEnemies.push_back(enemy);
				}
				points++;
				textPoints->content = to_string(points);
			}
		}
	}
	//Choque con enemigo
	for (auto const& enemy : enemies) {
		if (player1->isOverlap(enemy)|| player2->isOverlap(enemy)) {
			//Codigo de vidas
			enemies.remove(enemy);
			vidas--;
			textLives->content = to_string(vidas);
			return;
		}
	}
	//Choque con monedas
	for (auto const& Moneda : monedas) {
		if (player1->isOverlap(Moneda) || player2->isOverlap(Moneda)) {
			//Codigo de vidas
			monedas.remove(Moneda);
			vidas++;
			textLives->content = to_string(vidas);
			return;
		}
	}
	//Eliminar los enemigos muertos
	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
	}
	deleteEnemies.clear();
	//Eliminar los proyectiles gastados
	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();
	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();//Lo pintamos antes que el jugador, va por detras
	player1->draw();
	player2->draw();
	//Disparos antes que enemigos
	for (auto const& projectile : projectiles) {
		projectile->draw();
	}
	//Enemigos antes que colisiones, por si les damos
	for (auto const& enemy : enemies) {
		enemy->draw();
	}
	//Monedas
	for (auto const& moneda : monedas) {
		moneda->draw();
	}
	// Colisiones
	//for (auto const& enemy : enemies) {
	//	if (player1->isOverlap(enemy)) {
			//Codigo de vidas
			//vidas--;
			//textLives->content = to_string(vidas);
	if (vidas == 0) {
		init();
	}
		//	return; // Cortar el for
		//}
	//}

	textPoints->draw();
	textLives->draw();
	backgroundPoints->draw();
	backgroundLives->draw();
	SDL_RenderPresent(game->renderer); // Renderiza
}
