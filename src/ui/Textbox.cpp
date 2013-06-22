#include <bec2/ui/Textbox.hpp>
#include <bec2/ui/TexRes.hpp>
#include <bec2/ui/FontRes.hpp>


Textbox::Textbox()
{
	m_str = L"";
	m_cursorPos = 0;
	m_cursorBlink = 0.;

	width = 3.;
	height = 20.;
	
	m_rectTextBox.setFillColor(sf::Color(16, 16, 16, 200));
//	m_rectTextBox.setFillColor(sf::Color(128, 16, 16, 100));
	m_rectTextBox.setOutlineThickness(-1.f);
	
	m_txtText.setCharacterSize(12);
	m_txtText.setFont(*FontRes::OpenSans);
	m_txtText.setColor(sf::Color(235, 235, 235));
	m_txtText.setPosition(2.f, 2.f);

	m_txtHint.setCharacterSize(12);
	m_txtHint.setFont(*FontRes::OpenSans);
	m_txtHint.setColor(sf::Color(128, 128, 128));
	m_txtHint.setPosition(2.f, 2.f);

	m_sfcursor.append(sf::Vertex(sf::Vector2f(0.f, 3.f),  sf::Color(230, 230, 230)));
	m_sfcursor.append(sf::Vertex(sf::Vector2f(0.f, 17.f), sf::Color(230, 230, 230)));
	m_sfcursor.setPrimitiveType(sf::Lines);
}


Textbox::~Textbox()
{

}



const sf::String& Textbox::getString() const
{
	return m_str;
}


void Textbox::setString(const sf::String& str)
{
	m_str = str;
	m_txtText.setString(m_str);

	m_cursorPos = m_str.getSize();
}


const sf::String& Textbox::getHint() const
{
	return m_hint;
}


void Textbox::setHint(const sf::String& str)
{
	m_hint = str;
	m_txtHint.setString(m_hint);
}



void Textbox::onUpdate(double dt)
{

	SFWidget::onUpdate(dt);

	m_cursorBlink += dt;
	if (m_cursorBlink >= 1.)
		m_cursorBlink -= 1.;

}


void Textbox::onDrawSF(sf::RenderWindow& rw)
{

	bool focused = this->isFocused();

	// Draw box.
	m_rectTextBox.setPosition(0.f, 0.f); /* I wish I knew why I have to do this every draw. */
	m_rectTextBox.setOutlineColor(focused ? sf::Color(128, 128, 128) : sf::Color(72, 72, 72));
	rw.draw(m_rectTextBox);
	
	// Draw text.
	if (m_str.getSize())
	{
		rw.draw(m_txtText);
	}
	else
	{
		if (!focused)
		{
			rw.draw(m_txtHint);
		}
	}

	// Draw cursor.
	if (focused && m_cursorBlink < 0.5)
	{
		sf::Vector2f charpos = m_txtText.findCharacterPos(m_cursorPos);
		m_sfcursor[0].position.x = charpos.x + 0.5f;
		m_sfcursor[1].position.x = charpos.x + 0.5f;
		rw.draw(m_sfcursor);
	}
	
}



void Textbox::onMouseDown(double x, double y, unsigned int b)
{
	SFWidget::onMouseDown(x, y, b);
}


void Textbox::onMouseUp(double x, double y, unsigned int b)
{
	SFWidget::onMouseUp(x, y, b);
}


void Textbox::onMouseWheel(double x, double y, int d)
{
	SFWidget::onMouseWheel(x, y, d);
}


void Textbox::onMouseMove(double x, double y, double dx, double dy)
{
	SFWidget::onMouseMove(x, y, dx, dy);
}


void Textbox::onKeyDown(int key)
{
	if (this->isHidden())
		return;

	SFWidget::onKeyDown(key);

	if (this->isFocused())
	{
		bool invalidate = false;

		switch (key)
		{
		case sf::Keyboard::Delete:
			if (m_cursorPos < m_str.getSize())
			{
				m_str.erase(m_cursorPos);
				m_cursorBlink = 0.;
				invalidate = true;
			}
			break;

		case sf::Keyboard::Left:
			if (m_cursorPos)
			{
				m_cursorPos--;
				m_cursorBlink = 0.;
			}
			break;

		case sf::Keyboard::Right:
			if (m_cursorPos < m_str.getSize())
			{
				m_cursorPos++;
				m_cursorBlink = 0.;
			}
			break;
		}

		if (invalidate)
		{
			m_txtText.setString(m_str);
		}
	}
}


void Textbox::onKeyUp(int key)
{
	SFWidget::onKeyUp(key);
}


void Textbox::onKeyText(unsigned int ch)
{
	if (this->isHidden())
		return;

	SFWidget::onKeyText(ch);

	if (this->isFocused())
	{
		bool invalidate = false;

	//	printf("text %d\n", ch);

		switch (ch)
		{

		// Backspace
		case 8:
			if (!m_str.getSize())
				break;
			m_str.erase(m_str.getSize()-1);
			m_cursorPos--;
			m_cursorBlink = 0.;
			invalidate = true;
			break;

		// Tab
		case 9:
		//	this->popFocus();
			goto _forceinsert;
		//	break;

		// Ctrl+V
		case 22:
			if (OpenClipboard(NULL))
			{
				HANDLE cb = GetClipboardData(CF_UNICODETEXT);
				CloseClipboard();
				if (cb)
				{
					sf::String cbtxt = (wchar_t*)cb;
					m_str.insert(m_cursorPos, cbtxt);
					m_cursorPos += cbtxt.getSize();
					m_cursorBlink = 0.;
					invalidate = true;
				}
			}
			break;

		default:
			if (isprint(ch))
			{
_forceinsert:
				// Text entered.
				m_str.insert(m_cursorPos, sf::String(ch));
				m_cursorPos++;
				m_cursorBlink = 0.;
				invalidate = true;
			}
			break;

		}

		if (invalidate)
		{
			m_txtText.setString(m_str);
		}
	}
}



void Textbox::onMove(double dx, double dy)
{
	m_rectTextBox.setPosition(static_cast<float>(x), static_cast<float>(y));
}


void Textbox::onResize()
{
	m_rectTextBox.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
}


void Textbox::onPress(double x, double y, unsigned int b)
{
	
}


void Textbox::onRelease(double x, double y, unsigned int b)
{

}


void Textbox::onClick(double x, double y, unsigned int b)
{
	
}


void Textbox::onFocusGained()
{
	m_cursorBlink = 0.;
}


void Textbox::onFocusLost()
{
	
}


void Textbox::onMouseEnter(double x, double y)
{

}


void Textbox::onMouseLeave(double x, double y)
{

}


void Textbox::onAdopt(Widget& child)
{

}


void Textbox::onDisown(Widget& child)
{

}


void Textbox::onAdopted(Widget& parent)
{

}


void Textbox::onDisowned(Widget& parent)
{

}
