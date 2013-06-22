#pragma once
#include "GameField.hpp"

class Game
{
private:
	bool m_running;
	GameField* field;

public:
	Game();
	virtual ~Game();

	bool initialize(Renderer& rdr);
	void tick(double dt);
	void render(Renderer& rdr);
	bool isRunning() const;
	
	void onMouseDown(int mx, int my, sf::Mouse::Button mb);
	void onMouseUp(int mx, int my, sf::Mouse::Button mb);
	void onMouseMove(int mx, int my, int mdx, int mdy);
	void onMouseWheel(int mx, int my, int md);
	void onKeyDown(sf::Keyboard::Key key, bool shift, bool ctrl, bool alt, bool sys);
	void onKeyUp(sf::Keyboard::Key key, bool shift, bool ctrl, bool alt, bool sys);
	void onType(unsigned unicode);

	void onWindowClose(Renderer& rdr);
	void onWindowResize(Renderer& rdr, int width, int height);
};
