#include <iostream>
// SFML
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

const int W = 960;
const int H = 540;

int maxIteration = 100;
int zoom;
const int zoomValue = 5;
double minXcords = -2.5, maxXcords = 1;
double minYcords = -1, maxYcords = 1;

int main()
{
	sf::RenderWindow window(sf::VideoMode(W, H), "Mendelbrot Set");
	sf::Image image;
	image.create(W, H);
	sf::Texture texture;
	sf::Sprite sprite;

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
			if (e.type == sf::Event::KeyPressed)
			{
				if (e.key.code == sf::Keyboard::Key::R)
				{
					minXcords = -2.5;
					maxXcords = 1;
					minYcords = -1;
					maxYcords = 1;
				}
				double w = (maxXcords - minXcords) / 5;
				double h = (maxYcords - minYcords) / 5;
				if (e.key.code == sf::Keyboard::Key::W)
				{
					minYcords -= h;
					maxYcords -= h;
				}
				if (e.key.code == sf::Keyboard::Key::S)
				{
					minYcords += h;
					maxYcords += h;
				}
				if (e.key.code == sf::Keyboard::Key::A)
				{
					minXcords -= w;
					maxXcords -= w;
				}
				if (e.key.code == sf::Keyboard::Key::D)
				{
					minXcords += w;
					maxXcords += w;
				}
			}
			if (e.type == sf::Event::MouseWheelScrolled)
			{
				if (e.MouseWheelScrolled)
				{

					if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
					{
						if (e.mouseWheelScroll.delta > 0)
						{
							maxIteration += 100;
						}

						else
						{
							if (maxIteration == 100)
								maxIteration = 100;
							else
								maxIteration -= 100;
						}
					}
				}
			}
			if (e.type == sf::Event::MouseButtonPressed)
			{
				//Calculate new center in mouse point
				double newCenterX = minXcords + (maxXcords - minXcords) * e.mouseButton.x / W;
				double newCenterY = minYcords + (maxYcords - minYcords) * e.mouseButton.y / H;

				//Left Click to ZoomIn
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					//New max/min cords for x/y
					double tempMin = newCenterX - (maxXcords - minXcords) / zoomValue;
					maxXcords = newCenterX + (maxXcords - minXcords) / zoomValue;
					minXcords = tempMin;

					tempMin = newCenterY - (maxYcords - minYcords) / zoomValue;
					maxYcords = newCenterY + (maxYcords - minYcords) / zoomValue;
					minYcords = tempMin;

					zoom*=5;
				}

				//Right Click to ZoomOut
				if (e.mouseButton.button == sf::Mouse::Right)
				{
					//New max/min cords for x/y
					double tempMin = newCenterX - (maxXcords - minXcords) * zoomValue;
					maxXcords = newCenterX + (maxXcords - minXcords) * zoomValue;
					minXcords = tempMin;

					tempMin = newCenterY - (maxYcords - minYcords) * zoomValue;
					maxYcords = newCenterY + (maxYcords - minYcords) * zoomValue;
					minYcords = tempMin;

					zoom/=5;
				}
			}
		}
		window.clear();

		//Fractal img
		for (int y = 0; y < H; y++)
			for (int x = 0; x < W; x++)
			{
				double scaledX = minXcords + (maxXcords - minXcords) * x / W;
				double scaledY = minYcords + (maxYcords - minYcords) * y / H;
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
				int Red = 1.0 * (maxIteration - iteration) / maxIteration * 0xff;
				int Green = Red, Blue = Red;
				image.setPixel(x, y, sf::Color(Red, Green, Blue));
			}
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		window.draw(sprite);

		window.display();
	}

	return 0;
}