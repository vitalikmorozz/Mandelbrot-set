#include "Headers/Mandelbrot.hpp"

Mandelbrot::~Mandelbrot() {}

Mandelbrot::Mandelbrot() {}

void Mandelbrot::drawFractal(const int maxIteration, const int H, const int W, const double minRealCords, const double maxRealCords, const double minImCords, const double maxImCords, sf::Image &image, const bool c)
{
	calculateFractal(maxIteration, H, W, minRealCords, maxRealCords, minImCords, maxImCords, image, c);
}