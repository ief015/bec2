#include <bec2/ui/ColorPicker.hpp>
#include <bec2/ui/TexRes.hpp>
#include <bec2/ui/FontRes.hpp>


ColorPicker::ColorPicker()
{
	m_hue = new HueSelection(this);
	m_satvis = new SatVisSelection(this);

	m_hue->setSize(m_hue->getWidth(), 20.);
	m_satvis->setPosition(0., 24.);

	m_satvis->setSaturationColor(m_hue->getRGB());

	this->addWidget(m_hue);
	this->addWidget(m_satvis);
}


ColorPicker::~ColorPicker()
{
	delete m_hue;
	delete m_satvis;
}



sf::Color ColorPicker::getColor() const
{
	return m_satvis->getColor();
}



void ColorPicker::onHueChanged(HueSelection* self)
{
	m_satvis->setSaturationColor(m_hue->getRGB());
}


void ColorPicker::onSatVisChanged(SatVisSelection* self)
{

}



void ColorPicker::onUpdate(double dt)
{
	SFWidget::onUpdate(dt);
}


void ColorPicker::onDrawSF(sf::RenderWindow& rw)
{
	
}



void ColorPicker::onMouseDown(double x, double y, unsigned int b)
{
	SFWidget::onMouseDown(x, y, b);
}


void ColorPicker::onMouseUp(double x, double y, unsigned int b)
{
	SFWidget::onMouseUp(x, y, b);
}


void ColorPicker::onMouseWheel(double x, double y, int d)
{
	SFWidget::onMouseWheel(x, y, d);
}


void ColorPicker::onMouseMove(double x, double y, double dx, double dy)
{
	SFWidget::onMouseMove(x, y, dx, dy);
}


void ColorPicker::onKeyDown(int key)
{
	SFWidget::onKeyDown(key);
}


void ColorPicker::onKeyUp(int key)
{
	SFWidget::onKeyUp(key);
}


void ColorPicker::onKeyText(unsigned int ch)
{
	SFWidget::onKeyText(ch);
}



void ColorPicker::onMove(double dx, double dy)
{

}


void ColorPicker::onResize()
{
	this->height = this->width + m_hue->getHeight() + 4.;

	m_hue->setSize(this->width, m_hue->getHeight());
	m_satvis->setSize(this->width, this->width);
}


void ColorPicker::onPress(double x, double y, unsigned int b)
{

}


void ColorPicker::onRelease(double x, double y, unsigned int b)
{

}


void ColorPicker::onClick(double x, double y, unsigned int b)
{
	
}


void ColorPicker::onFocusGained()
{
	
}


void ColorPicker::onFocusLost()
{
	
}


void ColorPicker::onMouseEnter(double x, double y)
{

}


void ColorPicker::onMouseLeave(double x, double y)
{

}


void ColorPicker::onAdopt(Widget& child)
{

}


void ColorPicker::onDisown(Widget& child)
{

}


void ColorPicker::onAdopted(Widget& parent)
{

}


void ColorPicker::onDisowned(Widget& parent)
{

}
