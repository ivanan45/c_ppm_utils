#ifndef PPM_H_
#define PPM_H_

typedef struct PPM_Pixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} PPM_Pixel;

typedef struct PPM_Image {
	PPM_Pixel* data;
	int width;
	int height;
	int maxval;
} PPM_Image;

PPM_Image* PPM_read(const char* filepath);
void PPM_free(PPM_Image* img);

#endif // PPM_H_
