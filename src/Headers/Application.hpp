#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Headers/Fractal.hpp"

class Application
{
public:
	Application();
	virtual ~Application();
	void run();
private:
	void draw();
	void keyActions();
	void updateText();

	//Window setup
	sf::RenderWindow window;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Image image;
	//Font
	sf::Font font;
	//Texts
	sf::Text info, controls, menu;

	//Main settings
	const int W = 1366;
	const int H = 768;
	const int zoomValue = 5;
	int maxIteration = 128;
	int zoom = 1;
	double minRealCords = -2.5, maxRealCords = 1;
	double minImCords = -1, maxImCords = 1;
	bool m = 1, c = 1;
	Fractal Mandelbrote;
protected:
};