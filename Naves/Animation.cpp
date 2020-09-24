#include "Animation.h"

Animation::Animation(string filename, float actorWidth, float actorHeight,
	float fileWidth, float fileHeight,
	int updateFrecuence, int totalFrames, Game* game) {

	// Cargar textura
	SDL_Surface* surface = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(game->renderer, surface);

	this->actorWidth = actorWidth;
	this->actorHeight = actorHeight;
	this->fileWidth = fileWidth;
	this->fileHeight = fileHeight;
	this->updateFrecuence = updateFrecuence;
	this->totalFrames = totalFrames;
	this->game = game;

	updateTime = 0; // última actualización
	currentFrame = 0;

	// Calcular lo que mide un fotograma/frame
	frameWidth = fileWidth / totalFrames;
	frameHeigt = fileHeight;

	// Rectangulo de recorte de fotograma
	source.x = 0;
	source.y = 0;
	source.w = frameWidth;
	source.h = frameHeigt;
}
