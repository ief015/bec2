#include <bec2/ui/HueSelection.hpp>
#include <bec2/ui/TexRes.hpp>
#include <bec2/ui/FontRes.hpp>


HueSelection::HueSelection(HueSelectionHandler* handler) : m_handler(handler)
{
	m_hue = 0.;

	if (const sf::Texture* t = TexRes::getTexture("ui/hue"))
		m_spr.setTexture(*t, true);
	m_spr.setColor(sf::Color(255, 255, 255, 200));
	
	m_hueLine.setPrimitiveType(sf::Lines);
	m_hueLine.append(sf::Vertex( sf::Vector2f(0.f, 0.f), sf::Color::Black ));
	m_hueLine.append(sf::Vertex( sf::Vector2f(0.f, 0.f), sf::Color::Black ));
	
	this->width = m_spr.getTextureRect().width;
	this->height = m_spr.getTextureRect().height;

	m_border.setSize(sf::Vector2f(static_cast<float>(this->width), static_cast<float>(this->height)));
	m_border.setFillColor(sf::Color::Transparent);
	m_border.setOutlineColor(sf::Color(72, 72, 72));
	m_border.setOutlineThickness(1.f);
}


HueSelection::~HueSelection()
{

}



/* static */ sf::Color HueSelection::calcRGB(double hue)
{
	sf::Color col;

	hue = (hue - floor(hue)) * 360.;

	if (hue < 60.)
	{
		col.r = 255;
		col.g = static_cast<sf::Uint8>( (hue / 60.) * 255. );
	}
	else if (hue < 120.)
	{
		col.g = 255;
		col.r = static_cast<sf::Uint8>( (1. - ((hue - 60.) / 60.)) * 255. );
	}
	else if (hue < 180.)
	{
		col.g = 255;
		col.b = static_cast<sf::Uint8>( ((hue - 120.) / 60.) * 255. );
	}
	else if (hue < 240.)
	{
		col.b = 255;
		col.g = static_cast<sf::Uint8>( (1. - ((hue - 180.) / 60.)) * 255. );
	}
	else if (hue < 300.)
	{
		col.b = 255;
		col.r = static_cast<sf::Uint8>( ((hue - 240.) / 60.) * 255. );
	}
	else if (hue <= 360.)
	{
		col.r = 255;
		col.b = static_cast<sf::Uint8>( (1. - ((hue - 300.) / 60.)) * 255. );
	}

	return col;
}


sf::Color HueSelection::getRGB() const
{
	return HueSelection::calcRGB(m_hue);
}



void HueSelection::setHue(double h)
{
	m_hue = h - floor(h);
	if (m_handler) m_handler->onHueChanged(this);
}


double HueSelection::getHue() const
{
	return m_hue;
}



void HueSelection::onUpdate(double dt)
{
	SFWidget::onUpdate(dt);
}


void HueSelection::onDrawSF(sf::RenderWindow& rw)
{
	bool focused = this->isFocused();

	m_hueLine[0].position.x = static_cast<float>(ceil(m_hue * (this->width - 1.))+0.5);
	m_hueLine[1].position.x = m_hueLine[0].position.x;
	m_hueLine[1].position.y = static_cast<float>(this->height);
	
	m_border.setOutlineColor(focused ? sf::Color(128, 128, 128) : sf::Color(72, 72, 72));

	rw.draw(m_spr);
	rw.draw(m_hueLine);
	rw.draw(m_border);
}



void HueSelection::onMouseDown(double x, double y, unsigned int b)
{
	SFWidget::onMouseDown(x, y, b);
}


void HueSelection::onMouseUp(double x, double y, unsigned int b)
{
	SFWidget::onMouseUp(x, y, b);
}


void HueSelection::onMouseWheel(double x, double y, int d)
{
	SFWidget::onMouseWheel(x, y, d);
}


void HueSelection::onMouseMove(double x, double y, double dx, double dy)
{
	SFWidget::onMouseMove(x, y, dx, dy);

	unsigned int btn;
	if (this->isHeldDown(&btn))
	{
		if (btn == sf::Mouse::Left)
		{
			double hue = x / this->width;

			if (hue < 0.)
				hue = 0.;
			if (hue > 1. - DBL_EPSILON)
				hue = 1. - DBL_EPSILON;

			this->setHue(hue);
		}
	}
}


void HueSelection::onKeyDown(int key)
{
	SFWidget::onKeyDown(key);
}


void HueSelection::onKeyUp(int key)
{
	SFWidget::onKeyUp(key);
}


void HueSelection::onKeyText(unsigned int ch)
{
	SFWidget::onKeyText(ch);
}



void HueSelection::onMove(double dx, double dy)
{

}


void HueSelection::onResize()
{
	m_spr.setScale(static_cast<float>(this->width / m_spr.getTextureRect().width), static_cast<float>(this->height));
	m_border.setSize(sf::Vector2f(static_cast<float>(this->width), static_cast<float>(this->height)));
}


void HueSelection::onPress(double x, double y, unsigned int b)
{
	if (b == sf::Mouse::Left)
	{
		double hue = x / this->width;

		if (hue < 0.)
			hue = 0.;
		if (hue > 1. - DBL_EPSILON)
			hue = 1. - DBL_EPSILON;

		this->setHue(hue);
	}
}


void HueSelection::onRelease(double x, double y, unsigned int b)
{

}


void HueSelection::onClick(double x, double y, unsigned int b)
{
	
}


void HueSelection::onFocusGained()
{
	
}


void HueSelection::onFocusLost()
{
	
}


void HueSelection::onMouseEnter(double x, double y)
{

}


void HueSelection::onMouseLeave(double x, double y)
{

}


void HueSelection::onAdopt(Widget& child)
{

}


void HueSelection::onDisown(Widget& child)
{

}


void HueSelection::onAdopted(Widget& parent)
{

}


void HueSelection::onDisowned(Widget& parent)
{

}
