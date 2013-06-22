#pragma once
#include <SFML/Graphics.hpp>


class FontRes
{
public:
	static sf::Font* OpenSans;
	static sf::Font* OpenSans_Bold;
	static sf::Font* OpenSans_Light;

	static void initializeFonts();
	static void freeFonts();
};
