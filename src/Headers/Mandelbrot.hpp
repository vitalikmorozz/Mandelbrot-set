#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Headers/Fractal.hpp"

class Mandelbrot: Fractal{
public:
	Mandelbrot();
	virtual ~Mandelbrot();
	virtual void drawFractal(const int maxIteration, const int H, const int W, const double minRealCords, const double maxRealCords, const double minImCords, const double maxImCords, sf::Image &image, const bool c);
private:
protected:
};