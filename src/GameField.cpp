#include <bec2/GameField.hpp>



GameField::GameField()
{

	fps = 0.;
	tickms = 0.;

	m_gravity = 1.; /* These are not currently used. */
	m_gameSpeed = 1.; /* ^ */

	m_paused = false;
	m_showDebug = true;
	m_dragging = false;

	bodies.reserve(100);

	// Set up trajectory path.
	m_path.resize(256);
	m_path.setPrimitiveType(sf::LinesStrip);
	for (size_t i = m_path.getVertexCount(); i--;)
	{
		m_path[i].color = sf::Color::Black;
	}

	// Set up backdrop.
	m_backdrop.setFillColor(sf::Color::White);
	if (const sf::Texture* texBackdrop = TexRes::getTexture("backdrop"))
	{
		m_backdrop.setTexture(texBackdrop);
	}


	/* Set up debug text. */

	// Body count.
	m_txtBodyInfo = new sf::Text("", *FontRes::OpenSans_Light, 30);
	m_txtBodyInfo->setPosition(10., 8.);
	m_txtBodyInfo->setColor(sf::Color(96, 96, 96));

	// FPS.
	m_txtFPS = new sf::Text("", *FontRes::OpenSans, 15);
	m_txtFPS->setPosition(10.f, 40.f);
	m_txtFPS->setColor(sf::Color(128, 128, 128));

	// Tick clock.
	m_txtTick = new sf::Text("", *FontRes::OpenSans, 15);
	m_txtTick->setPosition(10.f, 55.f);
	m_txtTick->setColor(sf::Color(128, 128, 128));


	/* Set up instructions text. */
	
	m_txtInstructions = new sf::Text("[P]\tOpen Properties window\n[R]\tReset playing field\n[BkSpc]\tUndo last body\n\n[~]\tToggle debug + instructions\n[Space]\tPause", *FontRes::OpenSans, 11);
	m_txtInstructions->setOrigin(0., m_txtInstructions->getLocalBounds().height);
	m_txtInstructions->setColor(sf::Color(128, 128, 128));

	
	/* Set up interface. */

	// Properties window.
	m_properties = new UIProperties();
	m_properties->setPosition(20., 100.);
	this->addWidget(m_properties);

	// Dummy widget that does nothing. It's here to allow the user to defocus from other widgets on-screen.
	// Should be last added widget to make it focused by default.
	m_dummyWidget = new SFWidget();
	m_dummyWidget->hide(true);
	this->addWidget(m_dummyWidget);


	/* Start up bodies. Earth/Moon system. */
	
	// Earth.
	Body* earth = new Body();
	Vector& earthVec = earth->getVector();
	
	earth->setName("Earth");
	earth->setRadius(6.371); // 1000x KM
	earth->setMass(5.9736); // 10^24 KG
	earth->setColor(sf::Color(50, 150, 255, 150));

	earthVec.x = 400.;
	earthVec.y = 300.;

	bodies.push_back(earth);

	// Moon.
	Body* moon = new Body();
	Vector& moonVec = moon->getVector();
	
	moon->setName("Moon");
	moon->setRadius(1.7371); // 1000x KM
	moon->setMass(0.073477); // 10^24 KG
	moon->setColor(sf::Color(150, 150, 150, 150));

	moonVec.x = 400. + 384.399;
	moonVec.y = 300.;
	moonVec.vx = 0.;
	moonVec.vy = -((1.022/60.)*53.5)/2; // Approximated. I have no idea what the velocity of the moon is.
	
	bodies.push_back(moon);

	// Some debris circling Earth, because it's cool.
	for (int i = 0; i < 10; ++i)
	{
		Body* sat = new Body();
		Vector& satVec = sat->getVector();

		sat->setRadius(1.);
		sat->setMass(0.01); // 10^24 KG
		
		sat->setColor(sf::Color(200, 200, 200, 150));

		double s, c;
		s = rand()/(double)RAND_MAX * (3.141592653*2);
		c = cos(s);
		s = sin(s);

		satVec.x = 400. + (c * 100.);
		satVec.y = 300. + (s * 100.);

		satVec.vx = s * 2.5;
		satVec.vy = -c * 2.5;

		bodies.push_back(sat);
	}
	
}


GameField::~GameField()
{
	delete m_properties;
	delete m_dummyWidget;
}



void GameField::stepBodies()
{
	size_t i, j, sz = bodies.size();
	Body *b1, *b2;

	double dx, dy, fx, fy;
	double radii, distsqr, dir;

	// Calculate forces.
	for (i = 0; i < sz; ++i)
	{
		Vector& vec1 = (b1 = bodies[i])->getVector();

		for (j = i+1; j < sz; ++j)
		{
			Vector& vec2 = (b2 = bodies[j])->getVector();

			if (b1->isFixed() && b2->isFixed())
				continue;
			
			radii = b1->getRadius() + b2->getRadius();
			dx = vec1.x - vec2.x;
			dy = vec1.y - vec2.y;
			distsqr = (dx * dx) + (dy * dy);
			
			// Collision.
			if (radii*radii >= distsqr)
			{
				distsqr = radii*radii;
			}

			// Force.
			dir = atan2(dy, dx);
			distsqr = 1./distsqr;
			fx = cos(dir) * distsqr; // * m_gravity * m_gameSpeed;
			fy = sin(dir) * distsqr; // * m_gravity * m_gameSpeed;

			if (!b1->isFixed())
			{
				dx = b2->getMass() / b1->getMass();
				vec1.vx -= fx * dx;
				vec1.vy -= fy * dx;
			}
			
			if (!b2->isFixed())
			{
				dy = b1->getMass() / b2->getMass();
				vec2.vx += fx * dy;
				vec2.vy += fy * dy;
			}
		}
	}

	// Update bodies.
	for (i = 0; i < sz; ++i)
	{
		b1 = bodies[i];

		if (!b1->isFixed())
		{
			Vector& bv = b1->getVector();
			bv.x += bv.vx; // * m_gameSpeed;
			bv.y += bv.vy; // * m_gameSpeed;
		}

		// Currently not being used.
		//b1->update();
	}
}


void GameField::clearBodies()
{
	for (int i = 0, sz = bodies.size(); i < sz; ++i)
	{
		delete bodies[i];
	}
	bodies.clear();
}



void GameField::makeTrajectory(sf::VertexArray& buf, double x, double y, double vx, double vy, double trajectoryMass, double trajectoryRadius)
{
	Body *b;

	double dx, dy, fx, fy;
	double radii, distsqr, dir;

	for (size_t i = 0, sz = buf.getVertexCount(); i < sz; ++i)
	{
		sf::Vector2f& tv = buf[i].position;

		tv.x = static_cast<float>(x);
		tv.y = static_cast<float>(y);

		for (size_t j = bodies.size(); j--;)
		{
			Vector& bv = (b = bodies[j])->getVector();
			
			radii = b->getRadius() + trajectoryRadius;
			dx = x - bv.x;
			dy = y - bv.y;
			distsqr = (dx * dx) + (dy * dy);
			
			// Collision.
			if (radii*radii >= distsqr)
			{
				distsqr = radii*radii;
			}

			// Force.
			dir = atan2(dy, dx);
			distsqr = 1./distsqr;
			fx = cos(dir) * distsqr;
			fy = sin(dir) * distsqr;
			dx = b->getMass() / trajectoryMass;
			vx -= fx * dx;
			vy -= fy * dx;
		}

		x += vx;
		y += vy;
	}
}



void GameField::onUpdate(double dt)
{

	m_clkTick.restart();

	if (!m_paused)
	{
		this->stepBodies();
	}

	SFWidget::onUpdate(dt);

	tickms += m_clkTick.getElapsedTime().asMicroseconds() / 1000.;

}


void GameField::onDrawSF(sf::RenderWindow& rw)
{

	fps = 1000. / (m_clkFPS.restart().asMicroseconds() / 1000.);


	// Draw backdrop.
	if (m_paused)
	{
		// Paused outlines.
		m_backdrop.setOutlineColor(sf::Color(255, 50, 25));
		m_backdrop.setOutlineThickness(-5.f);
	}
	else
	{
		m_backdrop.setOutlineThickness(0.f);
	}
	rw.draw(m_backdrop);

	// Draw debug text.
	char buf[32];

	sprintf(buf, "bodies - %d", bodies.size());
	m_txtBodyInfo->setString(buf);
	
	rw.draw(*m_txtBodyInfo);

	if (m_showDebug)
	{
		sprintf(buf, "fps - %.2f", fps);
		m_txtFPS->setString(buf);

		sprintf(buf, "ms - %.2f", tickms);
		m_txtTick->setString(buf);

		rw.draw(*m_txtFPS);
		rw.draw(*m_txtTick);

		// Draw instructions text.
		m_txtInstructions->setPosition(10.f, rw.getSize().y - 10.f);
		rw.draw(*m_txtInstructions);
	}

	if (m_dragging)
	{
		// Draw dragging line.
		sf::VertexArray line;
		line.append(sf::Vertex(sf::Vector2f(
				static_cast<float>(this->getRelativeMouseX()), static_cast<float>(this->getRelativeMouseY())),
				sf::Color(64, 64, 255)));
		line.append(sf::Vertex(sf::Vector2f(
				static_cast<float>(m_draggingPos.x), static_cast<float>(m_draggingPos.y)),
				sf::Color(128, 128, 255)));
		line.setPrimitiveType(sf::Lines);
		rw.draw(line);

		// Draw trajectory path.
		this->makeTrajectory( m_path, m_draggingPos.x, m_draggingPos.y,
				(m_draggingPos.x - this->getRelativeMouseX()) / 20., (m_draggingPos.y - this->getRelativeMouseY()) / 20.,
				m_properties->retreiveMass(), m_properties->retreiveRadius() );

		rw.draw(m_path);
	}

	// Draw bodies.
	for (size_t i = 0, sz = bodies.size(); i < sz; ++i)
	{
		bodies[i]->render(rw);
	}

	tickms = 0.;

}



void GameField::onMouseDown(double x, double y, unsigned int btn)
{
	SFWidget::onMouseDown(x, y, btn);
}


void GameField::onMouseUp(double x, double y, unsigned int btn)
{
	SFWidget::onMouseUp(x, y, btn);
}


void GameField::onMouseWheel(double x, double y, int d)
{
	SFWidget::onMouseWheel(x, y, d);
}


void GameField::onMouseMove(double x, double y, double dx, double dy)
{
	SFWidget::onMouseMove(x, y, dx, dy);
}


void GameField::onKeyDown(int key)
{

	SFWidget::onKeyDown(key);

	if (m_dummyWidget->isFocused())
	{

		switch (key)
		{
		case sf::Keyboard::R:
			this->clearBodies();
			break;

		case sf::Keyboard::BackSpace:
			if (bodies.size())
			{
				delete bodies[bodies.size()-1];
				bodies.pop_back();
			}
			break;

		case sf::Keyboard::Space:
			m_paused = !m_paused;
			break;

		case sf::Keyboard::Tilde:
			m_showDebug = !m_showDebug;
			break;
		}

	}

}


void GameField::onKeyUp(int key)
{

	SFWidget::onKeyUp(key);

	if (m_dummyWidget->isFocused())
	{

		switch (key)
		{
		case sf::Keyboard::P:
			m_properties->hide(false);
			this->setFocus(m_properties);
			break;
		}

	}

}


void GameField::onKeyText(unsigned int ch)
{
	SFWidget::onKeyText(ch);
}



void GameField::onMove(double dx, double dy)
{

}


void GameField::onResize()
{

	m_backdrop.setSize(sf::Vector2f(static_cast<float>(this->width), static_cast<float>(this->height)));

}


void GameField::onPress(double x, double y, unsigned int btn)
{

	switch (btn)
	{
	case sf::Mouse::Left:

		m_dragging = true;
		m_draggingPos.setPosition(x, y);

		break;
	}

	this->setFocus(m_dummyWidget);
	
}


void GameField::onRelease(double x, double y, unsigned int btn)
{

	switch (btn)
	{
	case sf::Mouse::Left: {

		m_dragging = false;

		Body* b = new Body();

		b->getVector().setPosition(m_draggingPos.x, m_draggingPos.y);
		b->getVector().setVelocity((m_draggingPos.x - x)/20., (m_draggingPos.y - y)/20.);
		b->setMass(m_properties->retreiveMass());
		b->setRadius(m_properties->retreiveRadius());
		b->setName(m_properties->retreiveName());

		b->setFixed(m_properties->retreiveFixed());

		sf::Color col = m_properties->retreiveColor();
		col.a = 150;
		b->setColor(col);

		bodies.push_back(b);

		break; }
	}

}


void GameField::onClick(double x, double y, unsigned int btn)
{
}


void GameField::onFocusGained()
{
}


void GameField::onFocusLost()
{
}


void GameField::onMouseEnter(double x, double y)
{
}


void GameField::onMouseLeave(double x, double y)
{
}


void GameField::onAdopt(Widget& child)
{
}


void GameField::onDisown(Widget& child)
{
}


void GameField::onAdopted(Widget& parent)
{
}


void GameField::onDisowned(Widget& parent)
{
}

