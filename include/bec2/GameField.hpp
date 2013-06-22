#pragma once
#include "ui/SFWidget.hpp"
#include "ui/FontRes.hpp"
#include "ui/TexRes.hpp"

#include "UIProperties.hpp"

#include "Renderer.hpp"
#include "Body.hpp"

#include <vector>

class GameField : public SFWidget
{
private:
	double m_gravity, m_gameSpeed;
	bool m_paused;

	sf::RectangleShape m_backdrop;
	sf::VertexArray m_path;

	bool m_showDebug;
	sf::Clock m_clkFPS, m_clkTick;
	sf::Text* m_txtFPS;
	sf::Text* m_txtTick;
	sf::Text* m_txtBodyInfo;

	sf::Text* m_txtInstructions;

	bool m_dragging;
	Vector m_draggingPos;

	SFWidget* m_dummyWidget;
	UIProperties* m_properties;

public:
	GameField();
	virtual ~GameField();

	double fps, tickms;

	std::vector<Body*> bodies;
	void stepBodies();
	void clearBodies();

	void makeTrajectory(sf::VertexArray& buf, double x, double y, double vx, double vy, double trajectoryMass, double trajectoryRadius);

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
