#include <bec2/ui/WidgetTemplate.hpp>
#include <bec2/ui/TexRes.hpp>
#include <bec2/ui/FontRes.hpp>


WidgetTemplate::WidgetTemplate()
{

}


WidgetTemplate::~WidgetTemplate()
{

}



void WidgetTemplate::onUpdate(double dt)
{
	SFWidget::onUpdate(dt);
}


void WidgetTemplate::onDrawSF(sf::RenderWindow& rw)
{
	
}



void WidgetTemplate::onMouseDown(double x, double y, unsigned int b)
{
	SFWidget::onMouseDown(x, y, b);
}


void WidgetTemplate::onMouseUp(double x, double y, unsigned int b)
{
	SFWidget::onMouseUp(x, y, b);
}


void WidgetTemplate::onMouseWheel(double x, double y, int d)
{
	SFWidget::onMouseWheel(x, y, d);
}


void WidgetTemplate::onMouseMove(double x, double y, double dx, double dy)
{
	SFWidget::onMouseMove(x, y, dx, dy);
}


void WidgetTemplate::onKeyDown(int key)
{
	SFWidget::onKeyDown(key);
}


void WidgetTemplate::onKeyUp(int key)
{
	SFWidget::onKeyUp(key);
}


void WidgetTemplate::onKeyText(unsigned int ch)
{
	SFWidget::onKeyText(ch);
}



void WidgetTemplate::onMove(double dx, double dy)
{

}


void WidgetTemplate::onResize()
{

}


void WidgetTemplate::onPress(double x, double y, unsigned int b)
{
	
}


void WidgetTemplate::onRelease(double x, double y, unsigned int b)
{

}


void WidgetTemplate::onClick(double x, double y, unsigned int b)
{
	
}


void WidgetTemplate::onFocusGained()
{
	
}


void WidgetTemplate::onFocusLost()
{
	
}


void WidgetTemplate::onMouseEnter(double x, double y)
{

}


void WidgetTemplate::onMouseLeave(double x, double y)
{

}


void WidgetTemplate::onAdopt(Widget& child)
{

}


void WidgetTemplate::onDisown(Widget& child)
{

}


void WidgetTemplate::onAdopted(Widget& parent)
{

}


void WidgetTemplate::onDisowned(Widget& parent)
{

}
