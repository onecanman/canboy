#include "renderer.h"
#include <iostream>

Renderer::Renderer() {}
Renderer::~Renderer() {
	if (sdlTexture) SDL_DestroyTexture(sdlTexture);
	if (sdlRenderer) SDL_DestroyRenderer(sdlRenderer);
	if (sdlWindow) SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}

bool Renderer::init(const char* title, int scale) {
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	int w = WIDTH * scale;
	int h = HEIGHT * scale;
	sdlWindow = SDL_CreateWindow(title, w, h, 0);
	if (sdlWindow == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	sdlRenderer = SDL_CreateRenderer(sdlWindow, nullptr);
	if (sdlRenderer == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
	SDL_RenderClear(sdlRenderer);
	SDL_RenderPresent(sdlRenderer);

	return true;
}