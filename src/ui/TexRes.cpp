#include <bec2/ui/TexRes.hpp>


std::map<std::string, sf::Texture*> TexRes::m_textures = std::map<std::string, sf::Texture*>();


bool TexRes::preload(const std::string& texname, sf::Texture** out_tex)
{
	sf::Texture* tex = new sf::Texture();

	if (!tex->loadFromFile(std::string("res/") + texname + std::string(".png")))
	{
		delete tex;
		return false;
	}

	m_textures[texname] = tex;

	if (out_tex)
		*out_tex = tex;

	return true;
}


const sf::Texture* TexRes::getTexture(const std::string& texname)
{
	auto iter = m_textures.find(texname);

	if (iter == m_textures.end())
	{
		/*
		sf::Texture* tex = NULL;

		if (preload(texname, &tex))
			return tex;
		else
			return NULL;
		*/

		return NULL;
	}

	return iter->second;
}

void TexRes::freeAll()
{
	for (auto iter = m_textures.begin(); iter != m_textures.end(); iter++)
	{
		delete iter->second;
	}
	m_textures.clear();
}