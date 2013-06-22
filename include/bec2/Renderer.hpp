#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Renderer
{
private:
	sf::RenderWindow* rw;

public:
	Renderer()
	{
		rw = new sf::RenderWindow();
	}

	virtual ~Renderer()
	{
		delete rw;
	}

	sf::RenderWindow& operator *()
	{
		return *rw;
	}

	sf::RenderWindow& operator *() const
	{
		return *rw;
	}

	sf::RenderWindow* operator->()
	{
		return rw;
	}

	sf::RenderWindow* operator->() const
	{
		return rw;
	}
};
