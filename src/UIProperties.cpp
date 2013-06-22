#include <bec2/UIProperties.hpp>
#include <bec2/ui/TexRes.hpp>
#include <bec2/ui/FontRes.hpp>


UIProperties::UIProperties()
{

	this->width = 200.;
	this->height = 355.;
	this->onResize();


	this->setTitle("Properties");
	this->setClosable(true);
	this->setResizable(false);


	/* Labels. */

	m_lblMass = new Label();
	m_lblMass->setPosition(17., 53.);
	m_lblMass->setString("Mass", false);
	this->addWidget(m_lblMass);

	m_lblRadius = new Label();
	m_lblRadius->setPosition(10., 78.);
	m_lblRadius->setString("Radius", false);
	this->addWidget(m_lblRadius);

	m_lblReopen = new Label();
	m_lblReopen->setPosition(5., this->height - 18.);
	m_lblReopen->setString("Press [P] to reopen.", false);
	this->addWidget(m_lblReopen);


	/* Textboxes. */

	m_txtName = new Textbox();
	m_txtName->setPosition(5., 25.);
	m_txtName->setSize(this->width - m_txtName->getPositionX()*2., m_txtName->getHeight());
	m_txtName->setHint("Name");
	this->addWidget(m_txtName);

	m_txtMass = new Textbox();
	m_txtMass->setPosition(50., 50.);
	m_txtMass->setSize(this->width - (m_txtMass->getPositionX() + 5.), m_txtMass->getHeight());
	m_txtMass->setHint("5");
	this->addWidget(m_txtMass);

	m_txtRadius = new Textbox();
	m_txtRadius->setPosition(50., 75.);
	m_txtRadius->setSize(this->width - (m_txtRadius->getPositionX() + 5.), m_txtRadius->getHeight());
	m_txtRadius->setHint("5");
	this->addWidget(m_txtRadius);


	/* Checkboxed. */

	m_chkFixed = new Checkbox();
	m_chkFixed->setPosition(5., 100.);
	this->addWidget(m_chkFixed);

	m_lblChkFixed = new Label();
	m_lblChkFixed->setPosition(24., 100.);
	m_lblChkFixed->setString("Fixed", false);
	this->addWidget(m_lblChkFixed);


	/* Colour Picker. */

	m_colPicker = new ColorPicker();
	m_colPicker->setPosition(5., 120.);
	m_colPicker->setSize(this->width - (m_colPicker->getPositionX() + 5.), 0.);
	this->addWidget(m_colPicker);

}


UIProperties::~UIProperties()
{
	delete m_lblMass;
	delete m_lblRadius;
	delete m_lblReopen;

	delete m_txtName;
	delete m_txtMass;
	delete m_txtRadius;

	delete m_colPicker;
}



const sf::String& UIProperties::retreiveName() const
{
	return m_txtName->getString();
}


double UIProperties::retreiveMass() const
{
	double mass = 5.;
	sscanf(m_txtMass->getString().toAnsiString().c_str(), "%le", &mass);

	return mass;
}


double UIProperties::retreiveRadius() const
{
	double radius = 5.;
	sscanf(m_txtRadius->getString().toAnsiString().c_str(), "%le", &radius);

	return radius;
}


bool UIProperties::retreiveFixed() const
{
	return m_chkFixed->isChecked();
}


sf::Color UIProperties::retreiveColor()
{
	return m_colPicker->getColor();
}
