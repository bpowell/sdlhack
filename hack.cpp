#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <string>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Sprite{
	private:
		SDL_Renderer *renderer;
		SDL_Texture *texture;
		SDL_Rect size;
		int default_clip;
		SDL_Rect srcrect;
		SDL_Rect location;
	public:
		Sprite(SDL_Renderer *renderer, std::string path, SDL_Rect size, SDL_Rect location, int default_clip) 
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

			srcrect.x = size.w * default_clip;
			srcrect.y = 0;
			srcrect.w = srcrect.h = 32;
		}

		~Sprite(){
			if(texture!=NULL){
				SDL_DestroyTexture(texture);
			}
		}

		void render(){
			SDL_RenderCopy(renderer, texture, &srcrect, &location);
		}
};

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

int main(int argc, char *argv[]){
	Game *game = new Game();
	if(game->valid==false){
		std::cout << "SDL failed to initialize." << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Rect size;
	size.x = size.y = 0;
	size.w = size.h = 32;
	SDL_Rect loc;
	loc.x = loc.y = 10;
	loc.w = loc.h = 42;
	Sprite *s = new Sprite(game->getRenderer(), "toons.png", size, loc, 0);

	SDL_Event event;
	bool quit = false;
	int mouse_x = 0, mouse_y = 0;

	while(!quit){
		while(SDL_PollEvent(&event)!=0){
			if(event.type==SDL_QUIT)
				quit = true;

			if(event.type==SDL_MOUSEBUTTONDOWN || event.type==SDL_MOUSEBUTTONUP){
				SDL_GetMouseState(&mouse_x, &mouse_y);
				std::cout << mouse_x << "\t" << mouse_y << std::endl;
			}
		}

		s->render();
		SDL_RenderPresent(game->getRenderer());
	}

	delete game;

	return 0;
}
