#include "SDL3/SDL.h"

int main() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		throw SDL_GetError();
	}
	
	return 0;
}