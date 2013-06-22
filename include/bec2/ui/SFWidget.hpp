#pragma once
#include "Widget.hpp"

//#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class SFWidget : public Widget
{
public:
	SFWidget();
	virtual ~SFWidget();
	
protected:
	void onDraw(double scrx, double scry, void* udata = NULL);
	virtual void onDrawSF(sf::RenderWindow& rt);
};