#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Fractal{
public:
	Fractal();
	virtual ~Fractal();
	void calculateFractal(const int, const int, const int, const double, const double, const double, const double, sf::Image &, const bool);
private:
	sf::Color colorInterpolate(const sf::Color &, const sf::Color &, double );

	std::vector<sf::Color> colors;

protected:
};