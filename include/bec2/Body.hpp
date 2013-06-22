#pragma once
#include "Renderer.hpp"
#include "Vector.hpp"
#include "ui/FontRes.hpp"

class Body
{
private:
	double m_mass, m_radius;
	Vector m_vec;
	bool m_fixed;

	bool m_hasname;
	sf::Text* m_name;

	sf::Color m_color;


public:

	Body()
	: m_mass(1.)
	, m_radius(1.)
	, m_fixed(false)
	, m_name(NULL)
	{
		 m_vec.x = 0.;
		 m_vec.y = 0.;
		 m_vec.vx = 0.;
		 m_vec.vy = 0.;

		 m_color = sf::Color(255,50,50,150);
	}


	virtual ~Body()
	{
		if (m_name)
			delete m_name;
	}


	void setName(const sf::String& name)
	{
		if (name.getSize())
		{
			if (!m_name)
			{
				m_name = new sf::Text(name, *FontRes::OpenSans, 12);
				m_name->setColor(sf::Color(64, 64, 64));
				m_name->setOrigin(0.f, 12.f);
			}
			m_name->setString(name);
		}
		else
		{
			if (m_name)
			{
				delete m_name;
				m_name = NULL;
			}
		}
	}
	

	void setColor(const sf::Color& col)
	{
		m_color = col;
	}
	

	virtual void update()
	{

	}


	virtual void render(sf::RenderTarget& rt)
	{
		static sf::CircleShape* s = NULL;
		if (!s)
		{
			s = new sf::CircleShape(1.f, 10);
			s->setOrigin(1.f, 1.f);
		//	s->setFillColor(sf::Color(100,100,255,100));
		//	s->setFillColor(sf::Color(255,50,50,100));
			s->setOutlineColor(sf::Color::Black);
			s->setOutlineThickness(-0.25f);
		}

		s->setFillColor(m_color);
		s->setPosition(static_cast<float>(m_vec.x), static_cast<float>(m_vec.y));
		s->setScale(static_cast<float>(m_radius), static_cast<float>(m_radius));
		rt.draw(*s);

		/*
		static sf::VertexArray* line = NULL;
		if (!line)
		{
			line = new sf::VertexArray(sf::Lines, 2);
			(*line)[0].color = sf::Color::Black;
			(*line)[1].color = sf::Color::Black;
		}
		(*line)[0].position = s->getPosition();
		(*line)[1].position = sf::Vector2f(s->getPosition().x + cosf(m_vec.getDirection()) * static_cast<float>(m_radius), s->getPosition().y + sinf(m_vec.getDirection()) * static_cast<float>(m_radius));
		glLineWidth(static_cast<float>(m_radius / 3.5));
		rt.draw(*line);
		*/

		if (m_name)
		{
			m_name->setPosition(static_cast<float>(floor(m_vec.x + m_radius)), static_cast<float>(floor(m_vec.y - m_radius)));
			rt.draw(*m_name);
		}
	}
	

	inline Vector& getVector() { return m_vec; }
	inline const Vector& getVector() const { return m_vec; }
	
	inline bool isFixed() const { return m_fixed; }
	inline void setFixed(bool fix) { m_fixed = fix; }

	inline double getDensity() const { return m_mass / m_radius; }
	inline double getMass() const { return m_mass; }
	inline double getRadius() const { return m_radius; }
	inline void setMass(double newMass) { m_mass = newMass; }
	inline void setRadius(double newRadius) { m_radius = newRadius; }
};
