#include "Sprite.h"
#include <iostream>

Sprite::Sprite(SDL_Renderer *renderer, std::string path, Vector2D location, Vector2D size, int default_clip) :
	renderer(renderer), location(location), size(size), default_clip(default_clip)
{
		texture = NULL;
		SDL_Surface *surface = IMG_Load(path.c_str());

		if(surface==NULL){
			std::cerr << "Cannot load image " << path << std::endl;
			return;
		}

		if(default_clip<0){
			std::cerr << "Cannot load clip from image " << path << std::endl;
			return;
		}

		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if(texture==NULL){
			std::cerr << "Cannot load image " << path << std::endl;
			return;
		}

		SDL_FreeSurface(surface);
}

SpriteManager::SpriteManager(){}

SpriteManager::~SpriteManager(){
}

int SpriteManager::load(SpritePtr sprite){
	return 1;
}
