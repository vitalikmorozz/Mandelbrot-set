#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Mandelbrot.hpp"
#include "Menu.hpp"

class Application
{
public:
	Application();
	virtual ~Application();
	void run();

private:
	void start();
	void draw();
	void keyActions(bool);
	void updateText();

	//Window setup
	sf::RenderWindow window;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Image image;
	//Font
	sf::Font font;
	//Texts
	sf::Text info, menu;

	//Main settings
	const int W = 1366, H = 768, zoomValue = 5;
	int maxIteration;
	long long int zoom;
	double minRealCords, maxRealCords, minImCords, maxImCords;
	bool m, c;
	Mandelbrot Mandelbrote;
	Menu Menu;

protected:
};