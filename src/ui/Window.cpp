#include <bec2/ui/Window.hpp>
#include <bec2/ui/TexRes.hpp>
#include <bec2/ui/FontRes.hpp>


Window::Window()
{
	m_txtTitle = new sf::Text("Window", *FontRes::OpenSans_Bold, 13);

	m_texIcon = NULL;

	m_sprIcon = new sf::Sprite();
	m_sprIcon->setPosition(3.f, 2.f);

	m_sprClose = new sf::Sprite();
	if (const sf::Texture* t = TexRes::getTexture("ui/close"))
		m_sprClose->setTexture(*t);
	m_sprClose->setTextureRect(sf::IntRect(0, 0, 16, 16));
	m_sprClose->setColor(sf::Color(200, 200, 200));

	m_lineTitle.append(sf::Vertex(sf::Vector2f(3.f, 19.5f),   sf::Color(128, 128, 128, 72)));
	m_lineTitle.append(sf::Vertex(sf::Vector2f(197.f, 19.5f), sf::Color(128, 128, 128, 72)));
	m_lineTitle.setPrimitiveType(sf::Lines);

	m_rectWindow.setSize(sf::Vector2f(200.f, 200.f));
	m_rectWindow.setFillColor(sf::Color(0, 0, 0, 220));
//	m_rectWindow.setFillColor(sf::Color(255, 150, 150, 220));
	m_rectWindow.setOutlineColor(sf::Color(0, 0, 0, 150));
	m_rectWindow.setOutlineThickness(-1.f);

	m_closable = true;
	m_closeBtnDown = false;
	
	m_dragging = false;
	m_iconReady = false;

	m_resizable = true;
	m_resizingLeft = false;
	m_resizingRight = false;
	m_resizingTop = false;
	m_resizingBottom = false;
}


Window::~Window()
{
	if (m_texIcon)
		delete m_texIcon;

	delete m_sprIcon;
	delete m_sprClose;

	delete m_txtTitle;
}


void Window::setTitle(const sf::String& title)
{
	m_txtTitle->setString(title);
}


const sf::String& Window::getTitle() const
{
	return m_txtTitle->getString();
}


bool Window::setIcon(const sf::Image& icon16)
{
	if (!m_texIcon)
	{
		m_texIcon = new sf::Texture();
		m_sprIcon->setTexture(*m_texIcon);
	}

	m_iconReady = m_texIcon->loadFromImage(icon16, sf::IntRect(0, 0, 16, 16));
	return m_iconReady;
}


bool Window::getResizable() const
{
	return this->m_resizable;
}


void Window::setResizable(bool canResize)
{
	this->m_resizable = canResize;
}


bool Window::getClosable() const
{
	return m_closable;
}


void Window::setClosable(bool canClose)
{
	m_closable = canClose;
}



void Window::onUpdate(double dt)
{
	SFWidget::onUpdate(dt);
}


void Window::onDrawSF(sf::RenderWindow& rw)
{
	m_rectWindow.setSize(sf::Vector2f(static_cast<float>(this->getWidth()), static_cast<float>(this->getHeight())));
	rw.draw(m_rectWindow);
	
	m_txtTitle->setPosition(m_iconReady ? 24.f : 4.f, 2.f);
	m_txtTitle->setColor(this->isFocused() ? sf::Color(235, 235, 235) : sf::Color(148, 148, 148));
	rw.draw(*m_txtTitle);

	m_lineTitle[1].position.x = static_cast<float>(this->getWidth() - 3.);
	rw.draw(m_lineTitle);

	if (m_closable)
	{
		m_sprClose->setPosition(static_cast<float>(this->getWidth() - 18.), m_closeBtnDown ? 3.f : 2.f);
		m_sprClose->setColor(this->isFocused() ? sf::Color(235, 235, 235) : sf::Color(148, 148, 148));
		rw.draw(*m_sprClose);
	}

	if (m_iconReady)
	{
		rw.draw(*m_sprIcon);
	}
}



void Window::onMouseDown(double x, double y, unsigned int b)
{
	SFWidget::onMouseDown(x, y, b);
}


void Window::onMouseUp(double x, double y, unsigned int b)
{
	SFWidget::onMouseUp(x, y, b);
}


void Window::onMouseWheel(double x, double y, int d)
{
	SFWidget::onMouseWheel(x, y, d);
}


void Window::onMouseMove(double x, double y, double dx, double dy)
{
	SFWidget::onMouseMove(x, y, dx, dy);

	bool resized = false;
	
	double movex = 0.;
	double movey = 0.;

	if (m_resizingLeft)
	{
		if (dx > 0)
		{
			if (x > 2)
			{
				movex += dx;
				this->width -= dx;
				resized = true;
			}
		}
		else if (dx < 0)
		{
			if (x < 2)
			{
				movex += dx;
				this->width -= dx;
				resized = true;
			}
		}
	}
	else if (m_resizingRight)
	{
		if (dx > 0)
		{
			if (x > this->width-2)
			{
				this->width += dx;
				resized = true;
			}
		}
		else if (dx < 0)
		{
			if (x < this->width-2)
			{
				this->width += dx;
				resized = true;
			}
		}
	}
	if (m_resizingTop)
	{
		if (dy > 0)
		{
			if (y > 2)
			{
				movey += dy;
				this->height -= dy;
				resized = true;
			}
		}
		else if (dy < 0)
		{
			if (y < 2)
			{
				movey += dy;
				this->height -= dy;
				resized = true;
			}
		}
	}
	else if (m_resizingBottom)
	{
		if (dy > 0)
		{
			if (y > this->height-2)
			{
				this->height += dy;
				resized = true;
			}
		}
		else if (dy < 0)
		{
			if (y < this->height-2)
			{
				this->height += dy;
				resized = true;
			}
		}
	}

	if (resized)
	{
		if (width < 100)
		{
			if (m_resizingLeft)
				movex -= 100-width;
			width = 100;
		}
		if (height < 22)
		{
			if (m_resizingTop)
				movey -= 22-height;
			height = 22;
		}

		this->onResize();
	}

	if (m_dragging || movex != 0. || movey != 0.)
	{
		if (m_dragging)
		{
			movex += dx;
			movey += dy;
		}

		this->x += movex;
		this->y += movey;

		this->onMove(dx, dy);
	}

}


void Window::onKeyDown(int key)
{
	SFWidget::onKeyDown(key);
}


void Window::onKeyUp(int key)
{
	SFWidget::onKeyUp(key);
}


void Window::onKeyText(unsigned int ch)
{
	SFWidget::onKeyText(ch);
}



void Window::onMove(double dx, double dy)
{

}


void Window::onResize()
{
	
}


void Window::onPress(double x, double y, unsigned int b)
{
	if (b == sf::Mouse::Left)
	{
		if (m_resizable)
		{
			if (x < 4)
			{
				m_resizingLeft = true;
			}
			else if (x > this->width - 4)
			{
				m_resizingRight = true;
			}
			if (y < 4)
			{
				m_resizingTop = true;
			}
			else if (y > this->height - 4)
			{
				m_resizingBottom = true;
			}
		}

		if (y < 22 && !(m_resizingLeft || m_resizingRight || m_resizingTop || m_resizingBottom))
		{
			if (!m_closable || x < this->width - 22.)
			{
				m_dragging = true;
			}
			else
			{
				m_closeBtnDown = true;
			}
		}
	}
}


void Window::onRelease(double x, double y, unsigned int b)
{
	m_closeBtnDown = false;
	m_dragging = false;
	m_resizingLeft = false;
	m_resizingRight = false;
	m_resizingTop = false;
	m_resizingBottom = false;
}


void Window::onClick(double x, double y, unsigned int b)
{
	if (b == sf::Mouse::Left)
	{
		if (m_closable && y < 22 && !(m_resizingLeft || m_resizingRight || m_resizingTop || m_resizingBottom))
		{
			if (x >= this->width - 22.)
			{
				this->hide();
				this->popFocus();
			}
		}
	}
}


void Window::onFocusGained()
{
	
}


void Window::onFocusLost()
{
	
}


void Window::onMouseEnter(double x, double y)
{

}


void Window::onMouseLeave(double x, double y)
{

}


void Window::onAdopt(Widget& child)
{

}


void Window::onDisown(Widget& child)
{

}


void Window::onAdopted(Widget& parent)
{

}


void Window::onDisowned(Widget& parent)
{

}
