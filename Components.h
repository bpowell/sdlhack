#ifndef _COMPONENTS_H_
#define _COMPONENTS_H_

#include "Component.h"

class PositionComponent : public Component{
	public:
		float x;
		float y;

		PositionComponent(float x, float y);
};

class SpriteComponent : public Component{
	public:
		SDL_Renderer *renderer;
		SDL_Texture *texture;

		SpriteComponent(SDL_Renderer *renderer, std::string path);
};

#endif
