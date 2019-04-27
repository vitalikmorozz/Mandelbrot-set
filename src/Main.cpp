#include <iostream>
#include <string>
#include <math.h>
// SFML
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

const int W = 1366;
const int H = 768;

int maxIteration = 128;
int zoom = 1;
const int zoomValue = 5;
double minXcords = -2.5, maxXcords = 1;
double minYcords = -1, maxYcords = 1;
bool m = 1;

int main()
{
	sf::RenderWindow window(sf::VideoMode(W, H), "Mendelbrot Set", sf::Style::Fullscreen);
	sf::Image image;
	image.create(W, H);
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Font font;
	if (!font.loadFromFile("./arial.ttf"))
	{
		std::cout << "Font not loaded!!!";
	}

	sf::Text info, controls, menu;
	info.setFont(font);
	info.setColor(sf::Color::Blue);
	info.setCharacterSize(16);

	controls.setFont(font);
	controls.setColor(sf::Color::Blue);
	controls.setCharacterSize(16);
	controls.setPosition(0, H - 145);

	menu.setFont(font);
	menu.setColor(sf::Color::Blue);
	menu.setCharacterSize(16);
	menu.setPosition(0, H - 20);

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
			if (e.type == sf::Event::KeyPressed)
			{
				//Reset feature
				if (e.key.code == sf::Keyboard::Key::R)
				{
					minXcords = -2.5;
					maxXcords = 1;
					minYcords = -1;
					maxYcords = 1;
					zoom = 1;
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
				//Screenshot feature
				if (e.key.code == sf::Keyboard::Key::P)
				{
					image.saveToFile("./img.jpg");
				}
				if (e.key.code == sf::Keyboard::Key::M)
				{
					if(m) m = 0;
					else m = 1;
				}
			}
			//Increase Max Iterations
			if (e.type == sf::Event::MouseWheelScrolled)
			{
				if (e.MouseWheelScrolled)
				{

					if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
					{
						if (e.mouseWheelScroll.delta > 0)
						{
							maxIteration += 128;
						}

						else
						{
							if (maxIteration == 128)
								maxIteration = 128;
							else
								maxIteration -= 128;
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

					zoom *= 5;
				}

				//Right Click to ZoomOut
				if (e.mouseButton.button == sf::Mouse::Right)
				{
					//New max/min cords for x/y
					double tempMin = newCenterX - (maxXcords - minXcords) / 2 * zoomValue;
					maxXcords = newCenterX + (maxXcords - minXcords) / 2 * zoomValue;
					minXcords = tempMin;

					tempMin = newCenterY - (maxYcords - minYcords) / 2 * zoomValue;
					maxYcords = newCenterY + (maxYcords - minYcords) / 2 * zoomValue;
					minYcords = tempMin;

					if (minXcords <= -2.5 && maxXcords >= 1 && minYcords <= -1 && maxYcords >= 1)
					{
						minXcords = -2.5;
						maxXcords = 1;
						minYcords = -1;
						maxYcords = 1;
						zoom = 1;
					}

					zoom /= 5;
					if (zoom == 0)
					{
						zoom = 1;
					}
				}
			}
		}

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

				//Colouring
				//Total of 7 ranges of colors. 3 of them are in the red color zone, R moves from 0 to 255 and G and B are constantly 0.
				//The next 4 ranges are in the orange to yellow color zone, R is constantly 255, G moves from 0 to 255 and B is constantly 0.
				if (iteration == maxIteration)
				{
					sf::Color color(0, 0, 0);
					image.setPixel(x, y, color);
				}
				else if (iteration < (maxIteration / 8))
				{
					sf::Color color(iteration * 2, 0, 0);
					image.setPixel(x, y, color);
				}
				else if (iteration < (maxIteration / 7))
				{
					sf::Color color((((iteration - (maxIteration / 8)) * 128) / 126) + 128, 0, 0);
					image.setPixel(x, y, color);
				}
				else if (iteration < (maxIteration / 6))
				{
					sf::Color color((((iteration - (maxIteration / 7)) * 62) / 127) + 193, 0, 0);
					image.setPixel(x, y, color);
				}
				else if (iteration < (maxIteration / 5))
				{
					sf::Color color(255, (((iteration - (maxIteration / 6)) * 62) / 255) + 1, 0);
					image.setPixel(x, y, color);
				}
				else if (iteration < (maxIteration / 4))
				{
					sf::Color color(255, (((iteration - (maxIteration / 5)) * 63) / 511) + 64, 0);
					image.setPixel(x, y, color);
				}
				else if (iteration < (maxIteration / 3))
				{
					sf::Color color(255, (((iteration - (maxIteration / 4)) * 63) / 1023) + 128, 0);
					image.setPixel(x, y, color);
				}
				else if (iteration < (maxIteration / 2))
				{
					sf::Color color(255, (((iteration - (maxIteration / 3)) * 63) / 2047) + 192, 0);
					image.setPixel(x, y, color);
				}
				else
				{
					sf::Color color(255, 255, 0);
					image.setPixel(x, y, color);
				}
			}
		texture.loadFromImage(image);
		sprite.setTexture(texture);

		std::string infoText = "Current zoom : " + std::to_string(zoom) + "\nMax iterations : " + std::to_string(maxIteration);
		info.setString(infoText);

		std::string controlsText = "Navigation:\nMove: W/A/S/D\nZoom In: Left Click\nZoom Out: Right Click\nReset Zoom: R\nMake Screenshot: P\nIncrease Max Iteration: Scroll Up\nDecrease Max Iteration: Scroll Down";
		controls.setString(controlsText);

		std::string menuText = "Show menu: M";
		menu.setString(menuText);

		window.clear();

		window.draw(sprite);
		window.draw(info);
		if (m)
		{
			window.draw(menu);
		}
		else
			window.draw(controls);

		window.display();
	}

	return 0;
}