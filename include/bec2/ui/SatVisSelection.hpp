#pragma once
#include "SFWidget.hpp"
#include "handler/SatVisSelectionHandler.hpp"


class SatVisSelection : public SFWidget
{
private:
	sf::RectangleShape m_background;
	sf::VertexArray m_visibility;
	sf::VertexArray m_saturation;

	sf::CircleShape m_picker;

	double m_vis, m_sat;

	SatVisSelectionHandler* m_handler;

public:
	SatVisSelection(SatVisSelectionHandler* handler = NULL);
	virtual ~SatVisSelection();
	
	sf::Color getColor() const;
	void setSaturationColor(const sf::Color& col);
	const sf::Color& getSaturationColor() const;

protected:

	void invalidatePicker();

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

