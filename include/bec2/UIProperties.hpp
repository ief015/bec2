#pragma once
#include "ui/Window.hpp"
#include "ui/Textbox.hpp"
#include "ui/Checkbox.hpp"
#include "ui/ColorPicker.hpp"
#include "ui/Label.hpp"


class UIProperties : public Window
{
private:
	Label* m_lblMass;
	Label* m_lblRadius;
	Label* m_lblReopen;

	Textbox* m_txtName;
	Textbox* m_txtMass;
	Textbox* m_txtRadius;

	Checkbox* m_chkFixed;
	Label* m_lblChkFixed;

	ColorPicker* m_colPicker;

public:
	UIProperties();
	virtual ~UIProperties();

	const sf::String& retreiveName() const;
	double retreiveMass() const;
	double retreiveRadius() const;
	
	bool retreiveFixed() const;

	sf::Color retreiveColor();
};

