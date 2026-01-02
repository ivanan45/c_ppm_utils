#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PPM_Pixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct PPM_Image {
	struct PPM_Pixel* data;
	int width;
	int height;
	int maxval;
};

struct PPM_Image* PPM_read(const char* filepath) {
	FILE* fp = fopen(filepath, "rb");
	if (fp == NULL) {
		fprintf(stderr, "Failed to read file '%s'!\n", filepath);
		return NULL;
	}

	struct PPM_Image* img = malloc(sizeof(*img));
	if (img == NULL) {
		fprintf(stderr, "Failed to create the image!\n");
		return NULL;
	}

	// Get the first line
	char buf[128];
	if (fgets(buf, sizeof buf, fp) == NULL) {
		fprintf(stderr, "File is empty!\n");
		free(img);
		return NULL;
	}

	// Check that the format is set correctly (P6)
	if (strcmp(buf, "P6\n") != 0) {
		fprintf(stderr, "Invalid format!\n");
		free(img);
		return NULL;
	}

	// Skip the comment
	if (getc(fp) == '#') {
		while (getc(fp) != '\n');
	}

	// Get width, height and maxval
	fscanf(fp, "%d %d", &img->width, &img->height);
	fscanf(fp, "%d", &img->maxval);

	img->data = malloc(sizeof(struct PPM_Pixel) * img->width * img->height);

	if (fread(img->data, sizeof(struct PPM_Pixel), img->width * img->height, fp) != img->width * img->height) {
		fprintf(stderr, "Failed to read the image data!\n");
		if (img->data) {
			free(img->data);
		}
		free(img);
		return NULL;
	}

	return img;
}

void PPM_free(struct PPM_Image* img) {
	if (img) {
		if (img->data) {
			free(img->data);
		}

		img->width = img->height = img->maxval = 0;
		free(img);
	}
}

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
