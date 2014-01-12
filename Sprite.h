#ifndef _SPRITE_MANAGER_H_
#define _SPRITE_MANAGER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <memory>
#include <map>

class Sprite{
	protected:
		SDL_Renderer *renderer;
		SDL_Texture *texture;
		int default_clip;

	public:
		Sprite(SDL_Renderer *renderer, std::string path, int default_clip);
		~Sprite();
};

typedef std::shared_ptr<Sprite> SpritePtr;

class SpriteManager{
	private:
		std::map<int,SpritePtr> sprite_map;;

	public:
		SpriteManager();
		~SpriteManager();

		int load(SpritePtr sprite);
};

#endif
