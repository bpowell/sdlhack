#include "Sprite.h"
#include <iostream>

Sprite::Sprite(SDL_Renderer *renderer, std::string path, int default_clip) :
	renderer(renderer), default_clip(default_clip)
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
