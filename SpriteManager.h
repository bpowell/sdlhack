#ifndef _SPRITE_MANAGER_H_
#define _SPRITE_MANAGER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <memory>
#include <map>

class TextureManager{
	private:
		std::map<int,SDL_Texture*> texture_map;

	public:
		TextureManager();
		~TextureManager();

		int load(std::string filename, SDL_Renderer *renderer);
};

#endif
