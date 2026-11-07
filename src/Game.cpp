#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "../include/Game.hpp"
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800


struct SDL_State {
	SDL_Window *window;
	SDL_Renderer *renderer;
	int width, height, logW, logH;
};

bool initialize(SDL_State &state);
void cleanup(SDL_State &state);

void grun() {

	SDL_State state;
	state.width = 480;
	state.height = 800;
	state.logW = 480;
	state.logH = 800;
	if (!initialize(state)) {
		printf("INITIALIZATION ERROR");
	} 

	SDL_Texture* idleTex = IMG_LoadTexture(state.renderer, "./../images/transparent/sprites.png"); // make the file in respect to where you are building the project 
	if (!idleTex) {

		printf("SPRITE TEXTURE ERROR");
	}
	SDL_SetTextureScaleMode(idleTex, SDL_SCALEMODE_NEAREST); 
	// sdl texture loaded on gpu and sdl_surface loaded on system memory

	const bool* keys = SDL_GetKeyboardState(nullptr);
	float playerX = 200;
	float playerY = 200;
	const float floor = state.logH;
	uint64_t prevTime = SDL_GetTicks();
	bool running = true;
	while(running) {
		uint64_t nowTime = SDL_GetTicks(); // time between frames in m/s
		float deltaTime = (nowTime - prevTime) / 1000.0f; // converting to secs	
		SDL_Event event{0};
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_QUIT:
					running = false;
					break;

				case SDL_EVENT_WINDOW_RESIZED: // maintain aspect ratio
					state.width = event.window.data1;
					state.height = event.window.data2;
					break;
			} 
		}
	
	// do time based movement instead of frame based movement because different people have different hardware leading to different frame rates

	float moveAmount = 0;
	float horizontalSpeed = 75.f;
	if (keys[SDL_SCANCODE_A]) {
		moveAmount += -horizontalSpeed;
	}
	if (keys[SDL_SCANCODE_D]) {
		moveAmount += horizontalSpeed;

	} 
	playerX += moveAmount * deltaTime;

	
	// draw
	SDL_SetRenderDrawColor(state.renderer, 150, 111, 109, 255);
	
	SDL_RenderClear(state.renderer);
	const float spriteSize = 32.f;
	const float renderScale = 3.f;
	SDL_FRect src = {
		.x = 0.f,
		.y = 0.f,
		.w = spriteSize,
		.h = spriteSize
	};

	SDL_FRect destination {

		.x = playerX,
		.y = floor - (spriteSize*renderScale),
		.w = spriteSize * renderScale,
		.h = spriteSize * renderScale

	};
	
	SDL_RenderTexture(state.renderer, idleTex, &src, &destination);
	//SDL_RenderTexture(state.renderer, idleTex, nullptr, &destination); 
/*	SDL_RenderTextureRotated(
			state.renderer,
			idleTex,
			nullptr,
			&destination,
			-90.0,
			nullptr,
			SDL_FLIP_NONE
			);
	*/
	SDL_RenderPresent(state.renderer);
	prevTime = nowTime;
	}
	// free the vram used from textures
	SDL_DestroyTexture(idleTex);
	cleanup(state);
	
} 


void cleanup(SDL_State &state) {
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
} 

bool initialize(SDL_State &state) {
	bool initialization = true;
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		initialization = false;
	}

	state.window = SDL_CreateWindow("Game", state.width, state.height, SDL_WINDOW_RESIZABLE);

	if (!state.window) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr);
		cleanup(state);
		initialization = false;
	}

	state.renderer = SDL_CreateRenderer(state.window, nullptr);
	if (!state.renderer) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", state.window);
		initialization = false;
	}

	SDL_SetRenderLogicalPresentation(state.renderer, state.logW, state.logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	return initialization;	
}

