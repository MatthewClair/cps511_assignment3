#include <stdio.h>
#include <stdlib.h>

#include "Image.h"

Image::Image()
{
	sizeX = 0;
	sizeY = 0;
	data = NULL;
}

Image::Image(const char *filename)
{
	this->loadImage(filename);
}

bool Image::loadImage(const char *filename)
{
	FILE *file;
	unsigned long size;                 // size of the image in bytes.
	unsigned long i;                    // standard counter.
	unsigned short int planes;          // number of planes in image (must be 1)
	unsigned short int bpp;             // number of bits per pixel (must be 24)
	char temp;                          // used to convert bgr to rgb color.

	// Make sure the file exists
	if ((file = fopen(filename, "rb"))==NULL)
	{
		printf("File Not Found : %s\n",filename);
		return 0;
	}

	// Skip to bmp header
	fseek(file,18, SEEK_CUR);

	// read width
	if ((i = fread(&this->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}
	printf("Width of %s: %lu\n",filename, this->sizeX);

	//read the height
	if ((i = fread(&this->sizeY,4,1,file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}
	printf("Height of %s: %lu\n", filename, this->sizeY);

	// calculate the size (assuming 24 bpp)
	size = this->sizeX * this->sizeY * 3;

	// read the planes
	if ((fread(&planes, 2, 1, file)) != 1) {
		printf("Error reading planes from %s. \n", filename);
		return 0;
	}

	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
	}

	// read the bpp
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s. \n", filename);
		return 0;
	}

	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}

	// seek past the rest of the bitmap header
	fseek(file, 24, SEEK_CUR);

	// Read the data
	this->data = (char *) malloc(size);
	if (this->data == NULL) {
		printf("Error allocating memory for colour-corrected image data");
		return 0;
	}

	if ((i = fread(this->data,size,1,file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	// reverse all of the colours bgr => rgb)
	for (i=0;i<size;i+=3) {
		temp = this->data[i];
		this->data[i] = this->data[i+2];
		this->data[i+2] = temp;
	}

	// Thats all folks
	return 1;

}


