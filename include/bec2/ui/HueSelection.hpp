#pragma once
#include "SFWidget.hpp"
#include "handler/HueSelectionHandler.hpp"


class HueSelection : public SFWidget
{
private:
	sf::Sprite m_spr;
	sf::RectangleShape m_border;
	sf::VertexArray m_hueLine;
	
	double m_hue;

	HueSelectionHandler* m_handler;

public:
	HueSelection(HueSelectionHandler* handler = NULL);
	virtual ~HueSelection();

	static sf::Color calcRGB(double hue);
	sf::Color getRGB() const;

	void setHue(double h);
	double getHue() const;

protected:
	virtual void onUpdate(double dt);
	virtual void onDrawSF(sf::RenderWindow& rw);

	virtual void onMouseDown(double x, double y, unsigned int b);
	virtual void onMouseUp(double x, double y, unsigned int b);
	virtual void onMouseWheel(double x, double y, int d);
	virtual void onMouseMove(double x, double y, double dx, double dy);
	virtual void onKeyDown(int key);
	virtual void onKeyUp(int key);
	virtual void onKeyText(unsigned int ch);

	virtual void onMove(double dx, double dy);
	virtual void onResize();
	virtual void onPress(double x, double y, unsigned int b);
	virtual void onRelease(double x, double y, unsigned int b);
	virtual void onClick(double x, double y, unsigned int b);
	virtual void onFocusGained();
	virtual void onFocusLost();
	virtual void onMouseEnter(double x, double y);
	virtual void onMouseLeave(double x, double y);
	virtual void onAdopt(Widget& child);
	virtual void onDisown(Widget& child);
	virtual void onAdopted(Widget& parent);
	virtual void onDisowned(Widget& parent);

};

