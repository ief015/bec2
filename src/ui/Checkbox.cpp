#include <bec2/ui/Checkbox.hpp>
#include <bec2/ui/TexRes.hpp>
#include <bec2/ui/FontRes.hpp>


Checkbox::Checkbox()
{
	this->onResize();

	// Set up check mark sprite.
	if (const sf::Texture* tex = TexRes::getTexture("ui/check"))
		m_sprCheck.setTexture(*tex);
	m_sprCheck.setColor(sf::Color(200, 200, 200));

	// Set up box.
	m_rect.setSize(sf::Vector2f(16.f, 16.f));
	m_rect.setFillColor(sf::Color(16, 16, 16, 200));
	m_rect.setOutlineThickness(-1.f);

	m_checked = false;
}


Checkbox::~Checkbox()
{

}



bool Checkbox::isChecked() const
{
	return m_checked;
}


void Checkbox::setChecked(bool check)
{
	m_checked = check;
}



void Checkbox::onUpdate(double dt)
{
	SFWidget::onUpdate(dt);
}


void Checkbox::onDrawSF(sf::RenderWindow& rw)
{
	bool focused = this->isFocused();

	// Draw box.
	m_rect.setOutlineColor(focused ? sf::Color(128, 128, 128) : sf::Color(72, 72, 72));
	rw.draw(m_rect);

	// Draw check.
	if (m_checked)
	{
		rw.draw(m_sprCheck);
	}
}



void Checkbox::onMouseDown(double x, double y, unsigned int b)
{
	SFWidget::onMouseDown(x, y, b);
}


void Checkbox::onMouseUp(double x, double y, unsigned int b)
{
	SFWidget::onMouseUp(x, y, b);
}


void Checkbox::onMouseWheel(double x, double y, int d)
{
	SFWidget::onMouseWheel(x, y, d);
}


void Checkbox::onMouseMove(double x, double y, double dx, double dy)
{
	SFWidget::onMouseMove(x, y, dx, dy);
}


void Checkbox::onKeyDown(int key)
{
	SFWidget::onKeyDown(key);
}


void Checkbox::onKeyUp(int key)
{
	SFWidget::onKeyUp(key);
}


void Checkbox::onKeyText(unsigned int ch)
{
	SFWidget::onKeyText(ch);
}



void Checkbox::onMove(double dx, double dy)
{

}


void Checkbox::onResize()
{
	if (this->width < 16.)
		this->width = 16.;
	this->height = 16.;
}


void Checkbox::onPress(double x, double y, unsigned int b)
{
	
}


void Checkbox::onRelease(double x, double y, unsigned int b)
{

}


void Checkbox::onClick(double x, double y, unsigned int b)
{
	if (b == sf::Mouse::Left)
		this->setChecked(!m_checked);
}


void Checkbox::onFocusGained()
{
	
}


void Checkbox::onFocusLost()
{
	
}


void Checkbox::onMouseEnter(double x, double y)
{

}


void Checkbox::onMouseLeave(double x, double y)
{

}


void Checkbox::onAdopt(Widget& child)
{

}


void Checkbox::onDisown(Widget& child)
{

}


void Checkbox::onAdopted(Widget& parent)
{

}


void Checkbox::onDisowned(Widget& parent)
{

}
