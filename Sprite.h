#ifndef _SPRITE_MANAGER_H_
#define _SPRITE_MANAGER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <memory>
#include <map>

class Sprite;

class SpriteManager{
	private:
		std::map<int,Sprite*> sprite_map;;

	public:
		SpriteManager();
		~SpriteManager();

		int load(Sprite *sprite);
};

#endif
