#ifndef _INCLUDE_IMAGE_H_
#define _INCLUDE_IMAGE_H_

class Image
{
	public:
		Image();
		Image(const char *filename);
		bool loadImage(const char *filename);
		unsigned long sizeX;
		unsigned long sizeY;
		char *data;
};

#endif
