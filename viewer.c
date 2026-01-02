#include "ppm.h"
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	// Filename not provided
	if (argc != 2) {
		printf("Usage: ./viewer <filepath>\n");
		return -1;
	}

	struct PPM_Image* img = PPM_read(argv[1]);
	if (img == NULL) {
		fprintf(stderr, "Failed to load the image!\n");
		return -2;
	}

	// Basic SDL2 init
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(argv[1], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			img->width, img->height, 0);
	SDL_Surface* win_surf = SDL_GetWindowSurface(window);

	SDL_Rect pixel = { .x = 0, .y = 0, .w = 1, .h = 1 };
	for (int y = 0; y < img->height; y++) {
		for (int x = 0; x < img->width; x++) {
			pixel.x = x;
			pixel.y = y;

			PPM_Pixel tmp = img->data[y * img->width + x];
			Uint32 color = SDL_MapRGB(win_surf->format, tmp.r, tmp.g, tmp.b);

			SDL_FillRect(win_surf, &pixel, color);
		}
	}

	SDL_UpdateWindowSurface(window);

	SDL_Delay(4000);

	printf("%d %d\n", img->width, img->height);
	PPM_free(img);
	return 0;
}
