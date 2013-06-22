#include <bec2/Bec2.hpp>
#include <bec2/Game.hpp>


Game::Game()
: m_running(true)
{
}


Game::~Game()
{
	FontRes::freeFonts();
	TexRes::freeAll();

	delete field;
}



bool Game::initialize(Renderer& rdr)
{
	wchar_t title[0xFF];
	swprintf(title, 0xFF, L"%s - Ver. %d.%d.%d", BEC2_TITLE, BEC2_VER_MAJOR, BEC2_VER_MINOR, BEC2_VER_PATCH);

	rdr->create(sf::VideoMode(800, 600), title, sf::Style::Close | sf::Style::Resize, sf::ContextSettings(16, 8, 4));
	srand(static_cast<unsigned int>(time(NULL)));


	/* Preload textures. */
	sf::Texture* tex;

	if (TexRes::preload("backdrop", &tex)) tex->setSmooth(true);
	TexRes::preload("ui/close");
	TexRes::preload("ui/check");
	if (TexRes::preload("ui/hue", &tex)) tex->setSmooth(true);


	// Load fonts.
	FontRes::initializeFonts();


	// Create game field.
	field = new GameField();
	field->setSize(static_cast<double>(rdr->getSize().x), static_cast<double>(rdr->getSize().y));

	/* // TODO: Widget system does not work as expected here.
	Window* wnd = new Window();
	wnd->setPosition(200., 200.);
	wnd->setSize(400., 400.);
	wnd->setTitle("Mini game");
	wnd->setClosable(true);
	wnd->setResizable(false);
	field->addWidget(wnd);

	GameField* minifield = new GameField();
	minifield->setPosition(2., 22.);
	minifield->setSize(396., 376.);
	wnd->addWidget(minifield);
	*/

	return rdr->isOpen();

}


void Game::tick(double dt)
{
	// Update UI.
	field->update(dt);
}


void Game::render(Renderer& rdr)
{
	field->draw(&(*rdr));
	rdr->display();
}


bool Game::isRunning() const
{
	return m_running;
}



void Game::onMouseDown(int mx, int my, sf::Mouse::Button mb)
{
	field->mouseDown(mx, my, mb);
}


void Game::onMouseUp(int mx, int my, sf::Mouse::Button mb)
{
	field->mouseUp(mx, my, mb);
}


void Game::onMouseMove(int mx, int my, int mdx, int mdy)
{
	field->mouseMove(mx, my, mdx, mdy);
}


void Game::onMouseWheel(int mx, int my, int md)
{
	field->mouseWheel(mx, my, md);
}


void Game::onKeyDown(sf::Keyboard::Key key, bool shift, bool ctrl, bool alt, bool sys)
{
	field->keyDown(key);
}


void Game::onKeyUp(sf::Keyboard::Key key, bool shift, bool ctrl, bool alt, bool sys)
{
	field->keyUp(key);
}


void Game::onType(unsigned unicode)
{
	field->keyText(unicode);
}



void Game::onWindowClose(Renderer& rdr)
{
	rdr->close();
	m_running = false;
}


void Game::onWindowResize(Renderer& rdr, int width, int height)
{

	static sf::View pview = rdr->getView();

	sf::View view = rdr->getView();
	view.move(-(pview.getSize().x - width)/2, -(pview.getSize().y - height)/2);
	view.setSize(static_cast<float>(width), static_cast<float>(height));
	rdr->setView(view);

	pview = view;

	field->setSize(static_cast<double>(width), static_cast<double>(height));

}
