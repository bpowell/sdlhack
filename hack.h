#ifndef _HACK_H_
#define _HACK_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>

typedef int StatPoint;

class Person{
	protected:
		StatPoint strength;
		StatPoint attack;
		StatPoint defense;
		StatPoint vitality;
		bool is_fighting;

	public:
		Person();

		void set_fighting(bool fight);
};

class Sprite{
	protected:
		SDL_Renderer *renderer;
		SDL_Texture *texture;
		SDL_Rect size;
		SDL_Rect location;
		int default_clip;
		SDL_Rect srcrect;

		void switch_clip(int clip);

	public:
		Sprite(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip);
		~Sprite();
		SDL_Rect get_location();
		virtual void update(int mx, int my) = 0;
		void render();
};

class MobSprite : public Sprite{
	public:
		MobSprite(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip);
};

class HeroSprite : public Sprite{
	public:
		HeroSprite(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip);

		void update(int mx, int my);
};

class Hero;

class Mob : public MobSprite, public Person{
	public:
		Mob(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip);
		using Sprite::update;
		void update(int mx, int my, Hero **hero);
};

#endif