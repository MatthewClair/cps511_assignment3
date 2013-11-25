#ifndef _INCLUDE_COLOUR_H_
#define _INCLUDE_COLOUR_H_

#include <GL/gl.h>

class Colour
{
	public:
		Colour();
		Colour(GLubyte red, GLubyte green, GLubyte blue);
		~Colour();

	GLubyte red;
	GLubyte green;
	GLubyte blue;
};

#endif
