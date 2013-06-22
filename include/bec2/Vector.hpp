#pragma once
#include <math.h>

struct Vector
{
	double x, y;
	double vx, vy;

	inline void update()
	{
		x += vx;
		y += vy;
	}

	void applyForce(double force, double direction)
	{
		vx += cos(direction) * force;
		vy += sin(direction) * force;
	}

	inline double getDirection() const
	{
		return atan2(vy, vx);
	}

	inline double getForceSqr() const
	{
		return (vx*vx)+(vy*vy);
	}

	inline double getForce() const
	{
		return sqrt(getForceSqr());
	}

	inline void addVelocity(double velx, double vely)
	{
		vx += velx;
		vy += vely;
	}

	inline void setVelocity(double velx, double vely)
	{
		vx = velx;
		vy = vely;
	}

	inline void setPosition(double posx, double posy)
	{
		x = posx;
		y = posy;
	}
};
