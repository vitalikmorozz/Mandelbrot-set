#include "Headers/Fractal.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

Fractal::Fractal() {}

Fractal::~Fractal() {}

//Function that calculate color between two given colors, depending on given number t (0 < t <= 1)
sf::Color Fractal::colorInterpolate(const sf::Color &a, const sf::Color &b, double t)
{
	const double d = 1 - t;
	return sf::Color(a.r * d + b.r * t, a.g * d + b.g * t, a.b * d + b.b * t);
}

//Function that calculate fractal, directly in given image
void Fractal::calculateFractal(const int maxIteration, const int H, const int W, const double minRealCords, const double maxRealCords, const double minImCords, const double maxImCords, sf::Image &image, const bool c)
{
	//Colouring schemes
	if (!c)
	{
		//Red colouring
		colors = {
			{0, 0, 0},
			{213, 67, 31},
			{251, 255, 121},
			{62, 223, 89},
			{43, 30, 218},
			{0, 255, 247}};
	}
	else
	{
		//Standart colouring
		colors = {
			{0, 7, 100},
			{32, 107, 203},
			{237, 255, 255},
			{255, 170, 0},
			{0, 2, 0}};
	}
	for (int y = 0; y < H; y++)
		for (int x = 0; x < W; x++)
		{
			double scaledX = minRealCords + (maxRealCords - minRealCords) * x / W;
			double scaledY = minImCords + (maxImCords - minImCords) * y / H;
			double a = 0, b = 0;
			int iteration;
			for (iteration = 0; iteration < maxIteration; iteration++)
			{
				double tempX = a * a - b * b + scaledX;
				b = 2 * a * b + scaledY;
				a = tempX;

				if (a * a + b * b > 2 * 2)
					break;
				;
			}
			//Calculate number t (0 < t <=1), depending on iterations
			double t;
			int itretionsPerSection = maxIteration / (colors.size() - 1);
			if (iteration < itretionsPerSection)
				t = (double)iteration / (double)itretionsPerSection;
			else
				t = (double)(iteration % itretionsPerSection) / (double)itretionsPerSection;
			//Find necesary two colors for point
			int i = 0;
			sf::Color imgColor;
			while ((i + 1) * itretionsPerSection <= iteration)
				i++;
			if (iteration == maxIteration)
				imgColor = {0, 0, 0};
			else
				imgColor = colorInterpolate(colors[i], colors[i + 1], t);
			//Colouring each pixel
			image.setPixel(x, y, sf::Color(imgColor));
		}
}