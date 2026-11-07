#include <SDL3/SDL.h>
using namespace std;

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800


void cleanup(SDL_Window* win);

void grun(){
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
	}
	SDL_Window* win = SDL_CreateWindow("Game", SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	if (!win) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr);
		cleanup(win);
	}



	bool running = true;
	while(running) {
		SDL_Event event{0};
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_QUIT:
					running = false;
					break;
			} 
		}
	}
	cleanup(win);

} 

void cleanup(SDL_Window* win) {
	SDL_DestroyWindow(win);
	SDL_Quit();
} 


