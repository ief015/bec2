#pragma once
#include "SFWidget.hpp"


class Textbox : public SFWidget
{
private:
	size_t m_cursorPos;
	double m_cursorBlink;
	sf::String m_str;
	sf::String m_hint;

	sf::RectangleShape m_rectTextBox;
	sf::VertexArray m_sfcursor;
	sf::Text m_txtText;
	sf::Text m_txtHint;

public:
	Textbox();
	virtual ~Textbox();

	const sf::String& getString() const;
	void setString(const sf::String& str);

	const sf::String& getHint() const;
	void setHint(const sf::String& str);

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

