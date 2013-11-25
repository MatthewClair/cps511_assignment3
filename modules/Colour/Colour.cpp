#include "Colour.h"

Colour::Colour()
{
	this->red = 0;
	this->green = 0;
	this->blue = 0;
}

Colour::Colour(GLubyte red, GLubyte green, GLubyte blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

Colour::~Colour()
{ }
