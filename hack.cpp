#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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
			SDL_DestroyWindow(window);
			SDL_DestroyRenderer(renderer);
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

	SDL_RenderPresent(game->getRenderer());
	while(true){};

	return 0;
}