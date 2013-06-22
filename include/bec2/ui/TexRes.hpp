#pragma once
#include <SFML/Graphics.hpp>
#include <map>


class TexRes
{
private:
	static std::map<std::string, sf::Texture*> m_textures;

public:
	static bool preload(const std::string& texname, sf::Texture** out_tex = NULL);
	static const sf::Texture* getTexture(const std::string& texname);
	static void freeAll();

};