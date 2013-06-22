/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Widget.hpp                                                                       *
 *  Simple hierarchy-style UI widget system.                                         *
 *                                                                                   *
 *  Author(s): Nathan Cousins                                                        *
 *  Last Update: Jun 19, 2013                                                        *
 *                                                                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                   *
 *      Copyright © 2013 Nathan Cousins                                              *
 *                                                                                   *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy     *
 *  of this software and associated documentation files (the “Software”), to deal    *
 *  in the Software without restriction, including without limitation the rights     *
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
 *  copies of the Software, and to permit persons to whom the Software is            *
 *  furnished to do so, subject to the following conditions:                         *
 *                                                                                   *
 *  The above copyright notice and this permission notice shall be included in       *
 *  all copies or substantial portions of the Software.                              *
 *                                                                                   *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS          *
 *  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      *
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE      *
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER           *
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,    *
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN        *
 *  THE SOFTWARE.                                                                    *
 *                                                                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 
#ifndef _WIDGET_HPP_INCLUDED
#define _WIDGET_HPP_INCLUDED

#include <vector>


class Widget
{
private:
	
	// Widget UI internal variables.
	struct
	{
		std::vector<Widget*> widgets; /* Back-most widget is focused and/or top. */
		Widget* parent;

		bool down;
		unsigned int downBtn;
		bool mouseInsideChild;
		Widget* hover;
		
		bool hidden;

		double mouseX, mouseY;

	} m_internals;
	
protected:
	
	// These are protected so Widget classes can work with these internally.
	// Modifying these will not call onMove/onResize, you must call these events manually when appropriate.
	double x, y, width, height;
	
public:
	
	/* *** Contruction/Deconstruction *** */
	
	Widget()
	{
		x = 0.; y = 0.;
		width = 0.; height = 0.;
		
		m_internals.parent = NULL;
		m_internals.hover = NULL;
		
		m_internals.down = false;
		m_internals.downBtn = 0;
		m_internals.mouseInsideChild = false;
		
		m_internals.hidden = false;
		m_internals.mouseX = 0.;
		m_internals.mouseY = 0.;
	}
	
	
	virtual ~Widget()
	{
		
	}
	
	
	/* *** Transformation *** */
	
	void move(double movex, double movey)
	{
		x += movex;
		y += movey;
		
		this->onMove(movex, movey);
	}
	
	void setPosition(double posx, double posy)
	{
		double oldx = x, oldy = y;
		x = posx;
		y = posy;
		
		this->onMove(x - oldx, y - oldy);
	}
	
	inline void getPosition(double& out_x, double& out_y) const
	{
		out_x = x;
		out_y = y; 
	}
	
	inline double getPositionX() const
	{
		return x;
	}
	
	inline double getPositionY() const
	{
		return y;
	}
	
	
	void setSize(double sizewidth, double sizeheight)
	{
		width = sizewidth;
		height = sizeheight;
		
		this->onResize();
	}
	
	inline void getSize(double& out_width, double& out_height) const
	{
		out_width = width;
		out_height = height;
	}
	
	inline double getWidth() const
	{
		return width;
	}
	
	inline double getHeight() const
	{
		return height;
	}
	
	
	/* *** Visibility *** */
	
	// Check if we're hidden or if our parents are hidden.
	bool isHidden() const
	{
		const Widget* cur = this;
		
		// Check if we're hidden, or if our higher-level parents are hidden.
		do
		{
			if (cur->m_internals.hidden)
				return true;
			
			// Process the next parent.
			cur = cur->m_internals.parent;
		}
		while (cur);
		
		return false;
	}
	
	// Hide this widget and children.
	void hide(bool hidden = true)
	{
		m_internals.hidden = hidden;
	}
	
	
	/* *** Modify children *** */
	
	// Add a child widget to this widget.
	void addWidget(Widget* widget)
	{
		// Push the new child to the back. (It will become the focused widget)
		m_internals.widgets.push_back(widget);
		widget->m_internals.parent = this;
		
		// Call widget Adopt events.
		this->onAdopt(*widget);
		widget->onAdopted(*this);
	}
	
	// Remove a child widget from this widget.
	bool removeWidget(Widget* widget)
	{
		Widget* child;
		
		// Find widget.
		for (size_t i = m_internals.widgets.size(); i--;)
		{
			child = m_internals.widgets[i];
			if (child == widget)
			{
				// Remove it from children.
				child->m_internals.parent = NULL;
				m_internals.widgets.erase(m_internals.widgets.begin() + i);
				
				// Call widget Disown events.
				this->onDisown(*child);
				child->onDisowned(*this);
				
				return true;
			}
		}
		
		return false;
	}
	
	// Check if this widget parents a specific child widget.
	bool hasWidget(const Widget& widget) const
	{
		// Find widget.
		for (size_t i = m_internals.widgets.size(); i--;)
		{
			if (m_internals.widgets[i] == &widget)
				return true;
		}
		
		return false;
	}
	
	
	/* *** Widget parent *** */
	
	// Does this widget have a parent?
	bool hasParent() const
	{
		return m_internals.parent != NULL;
	}
	
	// Returns the parent widget. Returns NULL if no parent.
	Widget* getParent()
	{
		return m_internals.parent;
	}
	
	// Returns the parent widget. Returns NULL if no parent.
	const Widget* getParent() const
	{
		return m_internals.parent;
	}
	
	
	/* *** Widget children *** */
	
	// Does this widget contain children widgets?
	bool hasChildren() const
	{
		return m_internals.widgets.size() > 0;
	}
	
	// Get a child as specific index. Index must valid (in bounds).
	Widget* getChild(size_t idx)
	{
		return m_internals.widgets[idx];
	}
	
	// Get a child as specific index. Index must valid (in bounds).
	const Widget* getChild(size_t idx) const
	{
		return m_internals.widgets[idx];
	}
	
	// Get the number of children this widget parents.
	size_t getNumOfChildren() const
	{
		return m_internals.widgets.size();
	}
	
	
	/* *** Widget focus *** */
	
	// Force child at index to be the focused widget. This function does nothing if index is not valid (not in bounds).
	void setFocus(size_t idx)
	{
		Widget* widget;
		
		if (idx >= m_internals.widgets.size())
			return;
		
		widget = m_internals.widgets[idx];
		
		// Don't do anything if widget is already focused.
		if (widget->isFocusedChild())
			return;
		
		// Make it the focused object.
		m_internals.widgets.push_back(widget);
		m_internals.widgets.erase(m_internals.widgets.begin()+idx);
		
		// Call lost/gained focus events.
		m_internals.widgets[m_internals.widgets.size()-2]->onFocusLost();
		widget->onFocusGained();
	}
	
	// Force child to be the focused widget. The child must be a child of this widget, else this function does nothing.
	void setFocus(const Widget* child)
	{
		Widget* widget;
		
		// Find child.
		for (size_t i = m_internals.widgets.size(); i--;)
		{
			widget = m_internals.widgets[i];
			
			if (widget == child)
			{
				// Don't do anything if widget is already focused.
				if (widget->isFocused())
					return;
				
				// Make it the focused object.
				m_internals.widgets.push_back(widget);
				m_internals.widgets.erase(m_internals.widgets.begin()+i);
				
				// Call lost/gained focus events.
				m_internals.widgets[m_internals.widgets.size()-2]->onFocusLost();
				widget->onFocusGained();
			}
		}
	}
	
	// Get the focused child. Returns NULL if no children are present.
	Widget* getFocused()
	{
		// Return NULL if empty.
		if (m_internals.widgets.empty())
			return NULL;
		
		// The back widget is the focused component.
		return m_internals.widgets.back();
	}
	
	// Get the focused child. Returns NULL if no children are present.
	const Widget* getFocused() const
	{
		// Return NULL if empty.
		if (m_internals.widgets.empty())
			return NULL;
		
		// The back widget is the focused component.
		return m_internals.widgets.back();
	}
	
	// Is this widget the focused widget of the parent? Always returns true if no parent is present.
	bool isFocused() const
	{
		const Widget* cur = this;
		
		do
		{
			if (cur->isFocusedChild())
			{
				// Process the parent if this is the focused child.
				cur = cur->m_internals.parent;
			}
			else
			{
				// Always return false if this is not the focused child.
				return false;
			}
		}
		while (cur);
		
		// Always return true if there's no parent.
		return true;
	}
	
	// Is this widget the focused widget of the parent? Always returns true if no parent is present.
	bool isFocusedChild() const
	{
		// Check if we're the parent's focused child.
		if (m_internals.parent)
			return m_internals.parent->getFocused() == this;
		
		// Always return true if no parent.
		return true;
	}
	
	// Try to pop this widget out of focus and make the next sibling widget in focus instead.
	void popFocus()
	{
		// This should be the focused child.
		if (!this->isFocusedChild())
			return;
		
		// Can't pop if there is no parent.
		if (!m_internals.parent)
			return;
		
		// Can't pop if this is the only child.
		if (m_internals.parent->m_internals.widgets.size() < 2)
			return;
		
		// Set the second child into focus.
		m_internals.parent->setFocus(m_internals.parent->m_internals.widgets.size()-2);
	}
	
	
	/* *** Mouse interactivity *** */
	
	// Is the mouse holding this widget? Optionally, it will return which mouse button is holding the widget down via `btn'.
	bool isHeldDown(unsigned int* btn = NULL) const
	{
		if (m_internals.down)
		{
			*btn = m_internals.downBtn;
			return true;
		}
		return false;
	}
	
	// Is the mouse hovering over this widget?
	bool isMouseHovering() const
	{
		// Check if the hovering component is this widget.
		if (m_internals.parent)
			return m_internals.parent->m_internals.hover == this;
		
		// Always return false if no m_internals.parent.
		return false;
	}
	
	// Get the relative mouse position.
	double getRelativeMouseX() const
	{
		return m_internals.mouseX;
	}
	
	// Get the relative mouse position.
	double getRelativeMouseY() const
	{
		return m_internals.mouseY;
	}
	
	// Get relative mouse position.
	void getRelatieMousePos(double& x, double& y) const
	{
		x = m_internals.mouseX;
		y = m_internals.mouseY;
	}
	
	
	/* *** Invoke events *** */
	
	// Update this and child widgets.
	void update(double dt)
	{
		this->onUpdate(dt);
	}
	
	// Render this and child widgets.
	void draw(void* udata = NULL)
	{
		this->onDraw(this->x, this->y, udata);
	}
	
	// Call this to invoke Mouse-Down related events.
	// Mouse positions [x, y] here must be relative to the position of the parent widget (if any.)
	// ie. Use global/screen/window mouse positions if this is the root widget.
	void mouseDown(double x, double y, unsigned int b)
	{
		if (m_internals.hidden)
			return;
		
		this->onMouseDown(x, y, b);
		
		if (m_internals.mouseInsideChild)
			return;
		
		if (x >= this->x && x < this->x + this->width &&
			y >= this->y && y < this->y + this->height )
		{
			// This widget is being held down.
			if (!m_internals.down)
			{
				m_internals.down = true;
				m_internals.downBtn = b;
			}
			
			// Mouse pressed.
			this->onPress(x - this->x,  y - this->y, b);
		}
	}
	
	// Call this to invoke Mouse-Up related events.
	// Mouse positions [x, y] here must be relative to the position of the parent widget (if any.)
	// ie. Use global/screen/window mouse positions if this is the root widget.
	void mouseUp(double x, double y, unsigned int b)
	{
		if (m_internals.hidden)
			return;
		
		this->onMouseUp(x, y, b);
		
		if (m_internals.down && m_internals.downBtn == b)
		{
			// No longer held down.
			m_internals.down = false;
			
			// Mouse released this widget.
			this->onRelease(x - this->x, y - this->y, b);
			
			if (m_internals.mouseInsideChild)
				return;
			
			// Check if mouse was inside.
			if (x >= this->x && x < this->x + this->width &&
				y >= this->y && y < this->y + this->height )
			{
				// Widget was clicked.
				this->onClick(x - this->x, y - this->y, b);
			}
		}
	}
	
	// Call this to invoke Mouse-Wheel related events.
	// Mouse positions [x, y] here must be relative to the position of the parent widget (if any.)
	// ie. Use global/screen/window mouse positions if this is the root widget.
	void mouseWheel(double x, double y, int d)
	{
		this->onMouseWheel(x, y, d);
	}
	
	// Call this to invoke Mouse-Move related events.
	// Mouse positions [x, y] here must be relative to the position of the parent widget (if any.)
	// ie. Use global/screen/window mouse positions if this is the root widget.
	void mouseMove(double x, double y, double dx, double dy)
	{
		this->onMouseMove(x, y, dx, dy);
	}
	
	
	// Call this to invoke Key-Down related events.
	void keyDown(int key)
	{
		this->onKeyDown(key);
	}
	
	// Call this to invoke Key-Up related events.
	void keyUp(int key)
	{
		this->onKeyUp(key);
	}
	
	// Call this to invoke Key-Text related events.
	void keyText(unsigned int ch)
	{
		this->onKeyText(ch);
	}
	
protected:
	
	
	/* *** Widget events *** */
	
	// When the widget updates.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onUpdate(double dt)
	{
		Widget* widget;
		
		// Check for mouse entering/leaving.
		bool hovering = false;
		for (size_t i = m_internals.widgets.size(); i--;)
		{
			widget = m_internals.widgets[i];
			
			if (m_internals.mouseX >= widget->x && m_internals.mouseX < widget->x + widget->width &&
				m_internals.mouseY >= widget->y && m_internals.mouseY < widget->y + widget->height )
			{
				hovering = true;
				
				// If mouse is already hovering, no need to do anything.
				if (m_internals.hover == widget)
					break;
				
				// Change mouse hover to new widget.
				Widget* oldHover = m_internals.hover;
				m_internals.hover = widget;
				
				// Call widget events.
				if (oldHover)
					oldHover->onMouseLeave(m_internals.mouseX, m_internals.mouseY);
				
				widget->onMouseEnter(m_internals.mouseX, m_internals.mouseY);
				
				break;
			}
		}
		
		// If not hovering over anything, leave old hover widget (if any.)
		if (!hovering && this->m_internals.hover)
		{
			m_internals.hover->onMouseLeave(m_internals.mouseX, m_internals.mouseY);
			m_internals.hover = NULL;
		}
		
		// Update all children.
		for (size_t i = 0, sz = m_internals.widgets.size(); i < sz; ++i)
			m_internals.widgets[i]->onUpdate(dt);
	}
	
	// When the widget is supposed to be rendered.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onDraw(double scrx, double scry, void* udata = NULL)
	{
		if (m_internals.hidden)
			return;
		
		Widget* widget;
		
		// Draw all children.
		for (size_t i = 0, sz = m_internals.widgets.size(); i < sz; ++i)
		{
			widget = m_internals.widgets[i];
			
			if (!widget->m_internals.hidden)
				widget->onDraw(widget->x + scrx, widget->y + scry, udata);
		}
	}
	
	// When a mouse button is down.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onMouseDown(double x, double y, unsigned int b)
	{
		if (m_internals.hidden)
			return;
		
		Widget* widget;
		
		m_internals.mouseInsideChild = false;
		
		// Send mouse-down signal to all children.
		for (size_t i = m_internals.widgets.size(); i--;)
		{
			widget = m_internals.widgets[i];
			widget->onMouseDown(x - widget->x, y - widget->y, b);
		}
		
		// If the mouse is inside this widget.
		if (x >= 0. && x < this->width &&
			y >= 0. && y < this->height )
		{
			
			// Check for any mouse-downs inside of a child widget.
			// When found, push to the back, making it the focused widget.
			for (size_t i = m_internals.widgets.size(); i--;)
			{
				widget = m_internals.widgets[i];
				
				if (widget->m_internals.hidden)
					continue;
				
				if (x >= widget->x && x < widget->x + widget->width &&
					y >= widget->y && y < widget->y + widget->height )
				{
					m_internals.mouseInsideChild = true;
					
					// Widget is being held down.
					if (!widget->m_internals.down)
					{
						widget->m_internals.down = true;
						widget->m_internals.downBtn = b;
					}
					
					// Make this widget the focused child.
					this->setFocus(i);
					
					if (!widget->m_internals.mouseInsideChild)
					{
						// Mouse pressed.
						widget->onPress(x - widget->x,  y - widget->y, b);
					}
					
					break;
				}
			}
			
		}
	}
	
	// When a mouse button is up.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onMouseUp(double x, double y, unsigned int b)
	{
		if (m_internals.hidden)
			return;
		
		Widget* widget;
		
		m_internals.mouseInsideChild = false;
		
		// Send mouse-up signal to all children.
		for (size_t i = m_internals.widgets.size(); i--;)
		{
			widget = m_internals.widgets[i];
			widget->onMouseUp(x - widget->x, y - widget->y, b);
		}
		
		bool mouseInsideThis = ( x >= 0. && x < this->width && y >= 0. && y < this->height );
		
		// Check for any mouse-ups inside of a child widget.
		for (size_t i = m_internals.widgets.size(); i--;)
		{
			widget = m_internals.widgets[i];
			
			if (!m_internals.mouseInsideChild)
			{
				m_internals.mouseInsideChild = (
					x >= widget->x && x < widget->x + widget->width &&
					y >= widget->y && y < widget->y + widget->height );
			}
			
			if (widget->m_internals.down && widget->m_internals.downBtn == b)
			{
				// No longer held down.
				widget->m_internals.down = false;
				
				if (widget->m_internals.hidden)
					continue;
				
				// Mouse released this widget.
				widget->onRelease(x - widget->x, y - widget->y, b);
					
				if (mouseInsideThis && !widget->m_internals.mouseInsideChild)
				{
					// Check if mouse was inside.
					if (x >= widget->x && x < widget->x + widget->width &&
						y >= widget->y && y < widget->y + widget->height )
					{
						// Widget was clicked.
						widget->onClick(x - widget->x, y - widget->y, b);
					}
				}
			}
		}
	}
	
	// When the mouse wheel moves.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onMouseWheel(double x, double y, int d)
	{
		Widget* widget;
		
		// Send mouse-wheel signal to all children.
		for (size_t i = 0, sz = m_internals.widgets.size(); i < sz; ++i)
		{
			widget = m_internals.widgets[i];
			widget->onMouseWheel(x - widget->x, y - widget->y, d);
		}
	}
	
	// When the mouse moves.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onMouseMove(double x, double y, double dx, double dy)
	{
		Widget* widget;
		
		// Update mouse positions.
		m_internals.mouseX = x;
		m_internals.mouseY = y;
		
		// Send mouse-move signal to all children.
		for (size_t i = 0, sz = m_internals.widgets.size(); i < sz; ++i)
		{
			widget = m_internals.widgets[i];
			widget->onMouseMove(x - widget->x, y - widget->y, dx, dy);
		}
	}
	
	// When a keyboard key is down.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onKeyDown(int key)
	{
		// Send key-down signal to all children.
		for (size_t i = 0, sz = m_internals.widgets.size(); i < sz; ++i)
			m_internals.widgets[i]->onKeyDown(key);
	}
	
	// When a keyboard key is up.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onKeyUp(int key)
	{
		// Send key-up signal to all children.
		for (size_t i = 0, sz = m_internals.widgets.size(); i < sz; ++i)
			m_internals.widgets[i]->onKeyUp(key);
	}
	
	// When a character is entered. (Useful for widgets like textboxes)
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onKeyText(unsigned int ch)
	{
		// Send text signal to all children.
		for (size_t i = 0, sz = m_internals.widgets.size(); i < sz; ++i)
			m_internals.widgets[i]->onKeyText(ch);
	}
	
	
	// When this widget has moved.
	virtual void onMove(double dx, double dy)
	{
		
	}
	
	// When the widget is resized.
	virtual void onResize()
	{
		
	}
	
	// When the mouse presses inside this widget.
	virtual void onPress(double x, double y, unsigned int b)
	{
		
	}
	
	// When the mouse releases.
	virtual void onRelease(double x, double y, unsigned int b)
	{
		
	}
	
	// When the mouse clicks this widget. (Useful for widgets like buttons)
	// (When the mouse has pressed this widget and released with the mouse inside.)
	virtual void onClick(double x, double y, unsigned int b)
	{
		
	}
	
	// When the user focuses on this widget.
	virtual void onFocusGained()
	{
		
	}
	
	// When the user defocuses from this widget.
	virtual void onFocusLost()
	{
		
	}
	
	// When the mouse entered inside the widget.
	virtual void onMouseEnter(double x, double y)
	{
		
	}
	
	// When the mouse left outside the widget.
	virtual void onMouseLeave(double x, double y)
	{
		
	}
	
	// When this widget adopts a child widget.
	virtual void onAdopt(Widget& child)
	{
		
	}
	
	// When this widget disowns a child widget.
	virtual void onDisown(Widget& child)
	{
		
	}
	
	// When this widget has been adopted.
	virtual void onAdopted(Widget& parent)
	{
		
	}
	
	// When this widget has been disowned.
	virtual void onDisowned(Widget& parent)
	{
		
	}
	
};

#endif