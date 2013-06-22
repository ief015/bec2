#include <bec2/ui/FontRes.hpp>


sf::Font* FontRes::OpenSans = NULL;
sf::Font* FontRes::OpenSans_Bold = NULL;
sf::Font* FontRes::OpenSans_Light = NULL;


void FontRes::initializeFonts()
{
	OpenSans = new sf::Font();
	OpenSans->loadFromFile("res/opensans.ttf");

	OpenSans_Bold = new sf::Font();
	OpenSans_Bold->loadFromFile("res/opensans_bold.ttf");

	OpenSans_Light = new sf::Font();
	OpenSans_Light->loadFromFile("res/opensans_light.ttf");
}


void FontRes::freeFonts()
{
	delete OpenSans;
	delete OpenSans_Bold;
	delete OpenSans_Light;
}