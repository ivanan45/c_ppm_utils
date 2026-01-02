#include "ppm.h"
#include <stdio.h>
#include <string.h>

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

	for (int i = 0; i < img->width * img->height; i++) {
		printf("%d %d %d\n", img->data[i].r, img->data[i].g, img->data[i].b);
	}

	PPM_free(img);
	return 0;
}
