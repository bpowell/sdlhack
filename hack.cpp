#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "hack.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
static char MOUSE_DOWN  = 0;
#define HERO_UP 	0
#define HERO_DOWN	1
#define HERO_LEFT	2
#define HERO_RIGHT	3

Person::Person(){
	strength = 10;
	attack = 10;
	defense = 10;
	vitality = 10;
	is_fighting = false;
}

void Person::set_fighting(bool fight){
	is_fighting = fight;
}

bool Person::get_fighting(){
	return is_fighting;
}

void Sprite::switch_clip(int clip){
	srcrect.x = size.w * clip;
	srcrect.y = 0;
	srcrect.w = srcrect.h = 32;
}

Sprite::Sprite(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip) 
	: renderer(renderer), size(size), location(location), default_clip(default_clip){
		texture = NULL;
		SDL_Surface *surface = IMG_Load(path.c_str());

		if(surface==NULL){
			std::cout << "Cannot load image " << path << std::endl;
			return;
		}

		if(default_clip<0){
			std::cout << "Cannot load clip from image " << path << std::endl;
			return;
		}

		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if(texture==NULL){
			std::cout << "Cannot load image " << path << std::endl;
			return;
		}

		SDL_FreeSurface(surface);

		switch_clip(default_clip);
	}

Sprite::~Sprite(){
	if(texture!=NULL){
		SDL_DestroyTexture(texture);
	}
}

void Sprite::render(){
	SDL_RenderCopy(renderer, texture, &srcrect, &location);
}

SDL_Rect Sprite::get_location(){
	return location;
}

MobSprite::MobSprite(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip) :
	Sprite(renderer, path, size, location, default_clip){
}

Mob::Mob(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip) :
	MobSprite(renderer, path, size, location, default_clip){
}

void Mob::walk(int mx, int my){
	mx = mx + my;
	return;
}

void Mob::walk(int mx, int my, std::shared_ptr<Hero> hero){
	SDL_Rect mouse;
	mouse.x = mouse.w = mx;
	mouse.y = mouse.h = my;

	if(SDL_HasIntersection(&location, &mouse) && MOUSE_DOWN==1){
		std::cout << "I've been touched!\n";
		hero->set_fighting(true);
	}

	if(is_fighting==true){
		std::cout << "We be fighting\n";
	}
}

HeroSprite::HeroSprite(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip) :
	Sprite(renderer, path, size, location, default_clip){
}

void HeroSprite::walk(int mx, int my){
	int xdir = mx-location.x;
	int ydir = my-location.y;

	if(abs(xdir)>abs(ydir)){
		if(xdir>0){
			location.x++;
			switch_clip(HERO_RIGHT);
		}else{
			location.x--;
			switch_clip(HERO_LEFT);
		}
	}else{
		if(ydir>0){
			switch_clip(HERO_DOWN);
			location.y++;
		}else{
			location.y--;
			switch_clip(HERO_UP);
		}
	}
}

Hero::Hero(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip) :
	HeroSprite(renderer, path, size, location, default_clip){
}

void Hero::update(){
	if(get_fighting()==true){
		std::cout << "Hero is fighting\n";
	}
}

void Hero::check_collision(std::vector<std::shared_ptr<Mob>> mobs){
	for(std::vector<std::shared_ptr<Mob>>::iterator it = mobs.begin(); it != mobs.end(); ++it){
		SDL_Rect temp = (*it)->get_location();
		if(SDL_HasIntersection(&location, &temp)==SDL_TRUE){
			std::cout << "We touched!\n";
			(*it)->set_fighting(true);
			is_fighting = true;
		}else{
			(*it)->set_fighting(false);
			is_fighting = false;
		}
	}
}

class Game{
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
	public:
		bool valid;

		SDL_Renderer *getRenderer(){
			return renderer;
		}

		Game(){
			if(SDL_Init(SDL_INIT_VIDEO) < 0){
				valid = false;
				return;
			}

			if(!(SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"))){
				std::cout << "VSYNC not enabled." << std::endl;
			}

			if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1")){
				std::cout << "Linear texture filtering not enabled." << std::endl;
			}

			window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

			if(window==NULL){
				valid = false;
				return;
			}

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if(renderer==NULL){
				valid = false;
				return;
			}

			valid = true;
		}

		~Game(){
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
};

int main(){
	Game *game = new Game();
	if(game->valid==false){
		std::cout << "SDL failed to initialize." << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}

	std::vector<std::shared_ptr<Mob>> mobs;

	SDL_Rect size;
	size.x = size.y = 0;
	size.w = size.h = 32;
	SDL_Rect loc;
	loc.x = loc.y = 10;
	loc.w = loc.h = 32;
	std::shared_ptr<Hero> s (new Hero(game->getRenderer(), "toons.png", size, loc, HERO_UP));

	SDL_Rect loc2;
	loc2.x = loc2.y = 60;
	loc2.w = loc2.h = 32;
	std::shared_ptr<Mob> mob (new Mob(game->getRenderer(), "toons.png", size, loc2, HERO_UP));
	mobs.push_back(mob);

	SDL_Event event;
	bool quit = false;
	int mouse_x = 0, mouse_y = 0;

	while(!quit){
		while(SDL_PollEvent(&event)!=0){
			SDL_GetMouseState(&mouse_x, &mouse_y);

			if(event.type==SDL_QUIT)
				quit = true;

			if(event.type==SDL_MOUSEBUTTONDOWN){
				MOUSE_DOWN = 1;
				s->walk(mouse_x, mouse_y);
			}

			if(event.type==SDL_MOUSEBUTTONUP){
				MOUSE_DOWN = 0;
			}

			if(event.type==SDL_MOUSEMOTION && MOUSE_DOWN==1){
				SDL_GetMouseState(&mouse_x, &mouse_y);
				s->walk(mouse_x, mouse_y);
			}
		}

		s->update();
		s->check_collision(mobs);

		SDL_RenderClear(game->getRenderer());
		s->render();
		for(std::vector<std::shared_ptr<Mob>>::iterator it = mobs.begin(); it != mobs.end(); ++it){
			(*it)->walk(mouse_x, mouse_y, s);
			(*it)->render();
		}

		SDL_RenderPresent(game->getRenderer());
	}

	delete game;

	return 0;
}
