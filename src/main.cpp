#include <bec2/Bec2.hpp>
#include <bec2/Game.hpp>


int main()
{

	Game* game = new Game();

	Renderer* renderer = new Renderer();
	sf::RenderWindow& rw = **renderer;

	if ( !game->initialize(*renderer) )
	{
		delete renderer;
		delete game;
		return 1;
	}
	const sf::Time TICKTIME = sf::seconds(static_cast<float>(1. / BEC2_TICKRATE));

	sf::Clock clk;
	sf::Time t;
	sf::Event event;

	clk.restart();

	while (game->isRunning())
	{

		while (rw.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				game->onWindowClose(*renderer);
				break;
			case sf::Event::Resized:
				game->onWindowResize(*renderer, event.size.width, event.size.height);
				break;
			case sf::Event::KeyPressed:
				game->onKeyDown(event.key.code, event.key.shift, event.key.control, event.key.alt, event.key.system);
				break;
			case sf::Event::KeyReleased:
				game->onKeyUp(event.key.code, event.key.shift, event.key.control, event.key.alt, event.key.system);
				break;
			case sf::Event::TextEntered:
				game->onType(event.text.unicode);
				break;
			case sf::Event::MouseButtonPressed:
				game->onMouseDown(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:
				game->onMouseUp(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button);
				break;
			case sf::Event::MouseMoved: {
				static int mx = 0, my = 0;
				game->onMouseMove(event.mouseMove.x, event.mouseMove.y, event.mouseMove.x - mx, event.mouseMove.y - my);
				mx = event.mouseMove.x;
				my = event.mouseMove.y;
				break; }
			case sf::Event::MouseWheelMoved:
				game->onMouseWheel(event.mouseWheel.x, event.mouseWheel.y, event.mouseWheel.delta);
				break;
			}
		}

		size_t maxticks = BEC2_MAXTICKS;
		while ((t += clk.restart()) >= TICKTIME && maxticks--)
		{
			t -= TICKTIME;
			game->tick(1. / BEC2_TICKRATE);
		}

		game->render(*renderer);

		sf::sleep(sf::milliseconds(5));

	}

	delete renderer;
	delete game;
	return 0;
}
