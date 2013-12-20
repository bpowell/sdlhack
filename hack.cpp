#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <string>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Sprite{
	private:
		SDL_Texture *texture;
	public:
		Sprite(SDL_Renderer *renderer, std::string path){
			texture = NULL;
			SDL_Surface *surface = IMG_Load(path.c_str());

			if(surface==NULL){
				std::cout << "Cannot load image " << path << std::endl;
				return;
			}

			texture = SDL_CreateTextureFromSurface(renderer, surface);
			if(texture==NULL){
				std::cout << "Cannot load image " << path << std::endl;
				return;
			}

			SDL_FreeSurface(surface);
		}

		~Sprite(){
			if(texture!=NULL){
				SDL_DestroyTexture(texture);
			}
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

	SDL_Event event;
	bool quit = false;

	while(!quit){
		while(SDL_PollEvent(&event)!=0){
			if(event.type==SDL_QUIT)
				quit = true;
		}

		SDL_RenderPresent(game->getRenderer());
	}

	delete game;

	return 0;
}
