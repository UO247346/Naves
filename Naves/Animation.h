#pragma once

#include "Game.h"

class Animation
{
public:
	Animation(string filename, float actorWidth, float actorHeight,
		float fileWidth, float fileHeight,
		int updateFrecuence, int totalFrames, Game* game);
	bool update();
	void draw(float x, float y);
	int actorWidth; // Actor Width
	int actorHeight; // Actor height
	int fileWidth; // Sprite Sheet width
	int fileHeight; // Sprite Sheet height
	int currentFrame;
	int totalFrames;
	Game* game;

	// Auxiliares
	SDL_Texture* texture; // imagen
	SDL_Rect source; // Parte de la imagen que se recorta del fichero
	float frameWidth; // Ancho de un fotograma
	float frameHeigt; // Alto de un fotograma
	int updateFrecuence = 0;
	int updateTime = 0;
};
bool Animation::update() {
	updateTime++;
	if (updateTime > updateFrecuence) {
		updateTime = 0;
		// Actualizar el frame
		currentFrame++;
		// Si lleva al ultimo frame vuelve al primero
		if (currentFrame >= totalFrames) {
			// Reiniciar es infinita
			currentFrame = 0;
		}
	}
	//Actualizar el rectangulo del source (siguiente frame)
	source.x = currentFrame * frameWidth;
	return false; // luego lo cambiamos
}
void Animation::draw(float x, float y) {
	// Donde se va a pegar en el renderizador
	SDL_Rect destination;
	destination.x = x - actorWidth / 2;
	destination.y = y - actorHeight / 2;
	destination.w = actorWidth;
	destination.h = actorHeight;
	// Modificar para que la referencia sea el punto central

	SDL_RenderCopyEx(game->renderer,
		texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}
