#include <bec2/ui/SatVisSelection.hpp>
#include <bec2/ui/TexRes.hpp>
#include <bec2/ui/FontRes.hpp>


SatVisSelection::SatVisSelection(SatVisSelectionHandler* handler) : m_handler(handler)
{
	m_background.setFillColor(sf::Color(255, 255, 255, 172));
	m_background.setOutlineColor(sf::Color(72, 72, 72));
	m_background.setOutlineThickness(1.f);
	
	m_saturation.resize(4);
	m_saturation.setPrimitiveType(sf::Quads);
	m_saturation[0].color = sf::Color::Transparent;
	m_saturation[1].color = sf::Color::Transparent;
	m_saturation[2].color = sf::Color::Red;
	m_saturation[3].color = sf::Color::Red;

	m_visibility.resize(4);
	m_visibility.setPrimitiveType(sf::Quads);
	m_visibility[0].color = sf::Color::Transparent;
	m_visibility[1].color = sf::Color::Black;
	m_visibility[2].color = sf::Color::Black;
	m_visibility[3].color = sf::Color::Transparent;
	
	m_picker.setPointCount(10);
	m_picker.setRadius(4.f);
	m_picker.setOrigin(4.f, 4.f);
	m_picker.setOutlineThickness(1.5f);
	m_picker.setFillColor(sf::Color::Transparent);

	m_vis = 1.;
	m_sat = 1.;

	this->width = 256;
	this->height = 256;
	this->onResize();
}


SatVisSelection::~SatVisSelection()
{

}



sf::Color SatVisSelection::getColor() const
{
	double r, g, b;
	r = this->getSaturationColor().r / 255.;
	g = this->getSaturationColor().g / 255.;
	b = this->getSaturationColor().b / 255.;
	
	r += (1.-r) * (1.-m_sat);
	g += (1.-g) * (1.-m_sat);
	b += (1.-b) * (1.-m_sat);

	r *= m_vis;
	g *= m_vis;
	b *= m_vis;
	
	return sf::Color(static_cast<sf::Uint8>(r * 255.), static_cast<sf::Uint8>(g * 255.), static_cast<sf::Uint8>(b * 255.));
}


void SatVisSelection::setSaturationColor(const sf::Color& col)
{
	m_saturation[2].color = col;
	m_saturation[3].color = col;

	this->invalidatePicker();
}


const sf::Color& SatVisSelection::getSaturationColor() const
{
	return m_saturation[2].color;
}



void SatVisSelection::invalidatePicker()
{
	m_picker.setPosition( static_cast<float>(m_sat * this->width), static_cast<float>((1. - m_vis) * this->height));

	sf::Color col = this->getColor();
	m_picker.setOutlineColor(sf::Color(255 - col.r, 255 - col.g, 255 - col.b, 172));
}



void SatVisSelection::onUpdate(double dt)
{
	SFWidget::onUpdate(dt);
}


void SatVisSelection::onDrawSF(sf::RenderWindow& rw)
{
	bool focused = this->isFocused();
	m_background.setOutlineColor(focused ? sf::Color(128, 128, 128) : sf::Color(72, 72, 72));

	rw.draw(m_background);
	rw.draw(m_saturation);
	rw.draw(m_visibility);

	rw.draw(m_picker);
}



void SatVisSelection::onMouseDown(double x, double y, unsigned int b)
{
	SFWidget::onMouseDown(x, y, b);
}


void SatVisSelection::onMouseUp(double x, double y, unsigned int b)
{
	SFWidget::onMouseUp(x, y, b);
}


void SatVisSelection::onMouseWheel(double x, double y, int d)
{
	SFWidget::onMouseWheel(x, y, d);
}


void SatVisSelection::onMouseMove(double x, double y, double dx, double dy)
{
	SFWidget::onMouseMove(x, y, dx, dy);

	unsigned int btn;
	if (this->isHeldDown(&btn))
	{
		if (btn == sf::Mouse::Left)
		{
			m_sat = (x / this->width);

			if (m_sat < 0.)
				m_sat = 0.;
			if (m_sat > 1.)
				m_sat = 1.;

			m_vis = 1. - (y / this->height);

			if (m_vis < 0.)
				m_vis = 0.;
			if (m_vis > 1.)
				m_vis = 1.;

			invalidatePicker();
			if (m_handler) m_handler->onSatVisChanged(this);
		}
	}
}


void SatVisSelection::onKeyDown(int key)
{
	SFWidget::onKeyDown(key);
}


void SatVisSelection::onKeyUp(int key)
{
	SFWidget::onKeyUp(key);
}


void SatVisSelection::onKeyText(unsigned int ch)
{
	SFWidget::onKeyText(ch);
}



void SatVisSelection::onMove(double dx, double dy)
{

}


void SatVisSelection::onResize()
{
	m_background.setSize(sf::Vector2f(static_cast<float>(this->width), static_cast<float>(this->height)));

	m_visibility[0].position.x = 0.f;
	m_visibility[0].position.y = 0.f;
	m_visibility[1].position.x = 0.f;
	m_visibility[1].position.y = static_cast<float>(this->height);
	m_visibility[2].position.x = static_cast<float>(this->width);
	m_visibility[2].position.y = static_cast<float>(this->height);
	m_visibility[3].position.x = static_cast<float>(this->width);
	m_visibility[3].position.y = 0.f;

	m_saturation[0].position.x = 0.f;
	m_saturation[0].position.y = 0.f;
	m_saturation[1].position.x = 0.f;
	m_saturation[1].position.y = static_cast<float>(this->height);
	m_saturation[2].position.x = static_cast<float>(this->width);
	m_saturation[2].position.y = static_cast<float>(this->height);
	m_saturation[3].position.x = static_cast<float>(this->width);
	m_saturation[3].position.y = 0.f;

	invalidatePicker();
}


void SatVisSelection::onPress(double x, double y, unsigned int b)
{
	if (b == sf::Mouse::Left)
	{
		m_sat = (x / this->width);

		if (m_sat < 0.)
			m_sat = 0.;
		if (m_sat > 1.)
			m_sat = 1.;

		m_vis = 1. - (y / this->height);

		if (m_vis < 0.)
			m_vis = 0.;
		if (m_vis > 1.)
			m_vis = 1.;
		
		invalidatePicker();

		if (m_handler) m_handler->onSatVisChanged(this);
	}
}


void SatVisSelection::onRelease(double x, double y, unsigned int b)
{

}


void SatVisSelection::onClick(double x, double y, unsigned int b)
{
	
}


void SatVisSelection::onFocusGained()
{
	
}


void SatVisSelection::onFocusLost()
{
	
}


void SatVisSelection::onMouseEnter(double x, double y)
{

}


void SatVisSelection::onMouseLeave(double x, double y)
{

}


void SatVisSelection::onAdopt(Widget& child)
{

}


void SatVisSelection::onDisown(Widget& child)
{

}


void SatVisSelection::onAdopted(Widget& parent)
{

}


void SatVisSelection::onDisowned(Widget& parent)
{

}
