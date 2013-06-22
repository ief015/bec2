#include <bec2/ui/SFWidget.hpp>


SFWidget::SFWidget()
{

}


SFWidget::~SFWidget()
{

}


void SFWidget::onDraw(double scrx, double scry, void* udata)
{

	sf::RenderWindow* rw = (sf::RenderWindow*)udata;
	//sf::Vector2u rwSize = rw->getSize();
	
	sf::View view = rw->getView();

	view.move(static_cast<float>(-scrx), static_cast<float>(-scry));
	rw->setView(view);

	/*
	glClear(GL_STENCIL_BUFFER_BIT);
	glEnable(GL_STENCIL_TEST);

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glStencilMask(0xFF);
	*/
	/*
	if (this->hasParent())
	{
		Widget* parent = this->getParent();

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);

		double scrxp, scryp;
		scrxp = (scrx - this->x) / rwSize.x * 2.;
		scryp = (scry - this->y) / rwSize.y * 2.;
		scrxp -= 1.;
		scryp -= 1.;

		glBegin(GL_QUADS);
			glVertex2d(scrxp, -scryp);
			glVertex2d(scrxp, -scryp - parent->height/rwSize.y * 2.);
			glVertex2d(scrxp + parent->width/rwSize.x * 2., -scryp - parent->height/rwSize.y * 2.);
			glVertex2d(scrxp + parent->width/rwSize.x * 2., -scryp);
		glEnd();
	}

	glStencilFunc(GL_NOTEQUAL, 0xFF, 1);
	glStencilMask(0xFF);
	*/
	/*
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	double scrxt, scryt;
	scrxt = scrx / rwSize.x * 2.;
	scryt = scry / rwSize.y * 2.;
	scrxt -= 1.;
	scryt -= 1.;
	glBegin(GL_QUADS);
		glVertex2d(scrxt, -scryt);
		glVertex2d(scrxt, -scryt - this->height/rwSize.y * 2.);
		glVertex2d(scrxt + this->width/rwSize.x * 2., -scryt - this->height/rwSize.y * 2.);
		glVertex2d(scrxt + this->width/rwSize.x * 2., -scryt);
	glEnd();
	
	glStencilFunc(GL_EQUAL, 1, 0xFF);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilMask(0x00);
	
	this->onDrawSF(*rw);
	
	glDisable(GL_STENCIL_TEST);
	*/

	this->onDrawSF(*rw);

	/*
	glEnable(GL_SCISSOR_TEST);
	glScissor(static_cast<GLint>(scrx), static_cast<GLint>(rw->getSize().y - (scry + this->height)), static_cast<GLint>(this->width), static_cast<GLint>(this->height));
	this->onDrawSF(*rw);
	glDisable(GL_SCISSOR_TEST);
	*/

	view.move(static_cast<float>(scrx), static_cast<float>(scry));
	rw->setView(view);

	Widget::onDraw(scrx, scry, udata);

}


void SFWidget::onDrawSF(sf::RenderWindow& rt)
{

}