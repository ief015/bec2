#include <bec2/ui/Label.hpp>
#include <bec2/ui/TexRes.hpp>
#include <bec2/ui/FontRes.hpp>


Label::Label()
{
	m_label.setCharacterSize(12);
	m_label.setFont(*FontRes::OpenSans);
	m_label.setColor(sf::Color(235, 235, 235));
}


Label::~Label()
{

}


const sf::String& Label::getString() const
{
	return m_label.getString();
}


void Label::setString(const sf::String& str, bool autoResize)
{
	m_label.setString(str);

	if (autoResize)
	{
		sf::FloatRect rect = m_label.getLocalBounds();
		width = rect.width;
		height = rect.height;
		this->onResize();
	}
}


void Label::onUpdate(double dt)
{
	SFWidget::onUpdate(dt);
}


void Label::onDrawSF(sf::RenderWindow& rw)
{
	rw.draw(m_label);
}



void Label::onMouseDown(double x, double y, unsigned int b)
{
	SFWidget::onMouseDown(x, y, b);
}


void Label::onMouseUp(double x, double y, unsigned int b)
{
	SFWidget::onMouseUp(x, y, b);
}


void Label::onMouseWheel(double x, double y, int d)
{
	SFWidget::onMouseWheel(x, y, d);
}


void Label::onMouseMove(double x, double y, double dx, double dy)
{
	SFWidget::onMouseMove(x, y, dx, dy);
}


void Label::onKeyDown(int key)
{
	SFWidget::onKeyDown(key);
}


void Label::onKeyUp(int key)
{
	SFWidget::onKeyUp(key);
}


void Label::onKeyText(unsigned int ch)
{
	SFWidget::onKeyText(ch);
}



void Label::onMove(double dx, double dy)
{

}


void Label::onResize()
{

}


void Label::onPress(double x, double y, unsigned int b)
{
	
}


void Label::onRelease(double x, double y, unsigned int b)
{

}


void Label::onClick(double x, double y, unsigned int b)
{
	
}


void Label::onFocusGained()
{
	
}


void Label::onFocusLost()
{
	
}


void Label::onMouseEnter(double x, double y)
{

}


void Label::onMouseLeave(double x, double y)
{

}


void Label::onAdopt(Widget& child)
{

}


void Label::onDisown(Widget& child)
{

}


void Label::onAdopted(Widget& parent)
{

}


void Label::onDisowned(Widget& parent)
{

}
