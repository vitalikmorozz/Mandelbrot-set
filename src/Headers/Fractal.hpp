#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Fractal
{
public:
	Fractal();
	virtual ~Fractal();
	virtual void drawFractal(const int H, const int W, sf::Image &image);

protected:
	virtual void calculateFractal(const int maxIteration, const int H, const int W, const double minRealCords, const double maxRealCords, const double minImCords, const double maxImCords, sf::Image &image, const bool c);
	virtual inline sf::Color colorInterpolate(const sf::Color &a, const sf::Color &b, double t);

	std::vector<sf::Color> colors;
};