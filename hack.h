#ifndef _HACK_H_
#define _HACK_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <memory>

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
		bool get_fighting();
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
		virtual void walk(int mx, int my) = 0;
		void render();
};

class MobSprite : public Sprite{
	public:
		MobSprite(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip);
};

class HeroSprite : public Sprite{
	public:
		HeroSprite(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip);

		void walk(int mx, int my);
};

class Hero;

class Mob : public MobSprite, public Person{
	public:
		Mob(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip);

		void walk(int mx, int my, std::shared_ptr<Hero> hero);
		void walk(int mx, int my);
};

class Hero: public HeroSprite, public Person{
	public:
		Hero(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip);
		void check_collision(std::vector<std::shared_ptr<Mob>> mobs);
		void walk(int mx, int my);
};

#endif
