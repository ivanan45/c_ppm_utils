#include "ppm.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PPM_Image* PPM_read(const char* filepath) {
	FILE* fp = fopen(filepath, "rb");
	if (fp == NULL) {
		fprintf(stderr, "Failed to read file '%s'!\n", filepath);
		return NULL;
	}

	PPM_Image* img = malloc(sizeof(*img));
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

	img->data = malloc(sizeof(PPM_Pixel) * img->width * img->height);

	if (fread(img->data, sizeof(PPM_Pixel), img->width * img->height, fp) != img->width * img->height) {
		fprintf(stderr, "Failed to read the image data!\n");
		if (img->data) {
			free(img->data);
		}
		free(img);
		return NULL;
	}

	return img;
}

void PPM_free(PPM_Image* img) {
	if (img) {
		if (img->data) {
			free(img->data);
			img->data = NULL;
		}

		img->width = img->height = img->maxval = 0;
		free(img);
		img = NULL;
	}
}
