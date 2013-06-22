#pragma once
#include "SFWidget.hpp"


class Window : public SFWidget
{
private:
	sf::Text* m_txtTitle;

	sf::Texture* m_texIcon;
	sf::Sprite* m_sprIcon;
	
	sf::RectangleShape m_rectWindow;
	sf::VertexArray m_lineTitle;
	sf::Sprite* m_sprClose;

	bool m_dragging;
	bool m_iconReady;
	bool m_resizingLeft;
	bool m_resizingRight;
	bool m_resizingTop;
	bool m_resizingBottom;
	bool m_closeBtnDown;
	
	bool m_resizable;
	bool m_closable;

public:
	Window();
	virtual ~Window();

	void setTitle(const sf::String& title);
	const sf::String& getTitle() const;
	bool setIcon(const sf::Image& icon16);
	bool getResizable() const;
	void setResizable(bool canResize);
	bool getClosable() const;
	void setClosable(bool canClose);

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

