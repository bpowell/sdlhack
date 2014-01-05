#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager(){}

TextureManager::~TextureManager(){
	std::map<int,SDL_Texture*>::iterator it;
	for(it=texture_map.begin(); it!=texture_map.end(); ++it){
		SDL_DestroyTexture(it->second);
	}
}

int TextureManager::load(std::string filename, SDL_Renderer *renderer){
	SDL_Surface *surface = IMG_Load(filename.c_str());

	if(surface==NULL){
		std::cout << "Cannot load image " << filename << std::endl;
		return -1;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(texture==NULL){
		std::cout << "Cannot load image " << filename << std::endl;
		return -1;
	}

	SDL_FreeSurface(surface);

	texture_map.insert(std::pair<int,SDL_Texture*>(texture_map.size(), texture));
	return texture_map.size()-1;
}
