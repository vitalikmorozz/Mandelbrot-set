#include <iostream>
#include <string>
#include <math.h>
// SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//Main settings
const int W = 1366;
const int H = 768;
const int zoomValue = 5;

int maxIteration = 128;
int zoom = 1;
double minRealCords = -2.5, maxRealCords = 1;
double minImCords = -1, maxImCords = 1;
bool m = 1, c = 1;

//Function that calculate color between two given colours a and b, depending on given number t (0 < t <= 1)
sf::Color colorInterpolate(sf::Color a, sf::Color b, double t)
{
	if (a.r < b.r && a.g < b.g && a.b < b.b)
		return {round(a.r + abs(b.r - a.r) * t), round(a.g + abs(b.g - a.g) * t), round(a.b + abs(b.b - a.b) * t)};
	else
		return {round(a.r - abs(b.r - a.r) * t), round(a.g - abs(b.g - a.g) * t), round(a.b - abs(b.b - a.b) * t)};
}

int main()
{
	//Window setup
	sf::RenderWindow window(sf::VideoMode(W, H), "Mendelbrot Set", sf::Style::Fullscreen);

	sf::Image image;
	image.create(W, H);
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Event e;
	//Font checking
	sf::Font font;
	if (!font.loadFromFile("./arial.ttf"))
	{
		std::cout << "Font not loaded!!!";
	}
	//Info text setup
	sf::Text info, controls, menu;
	info.setFont(font);
	info.setColor(sf::Color::Black);
	info.setCharacterSize(16);
	//Navigation text setup
	controls.setFont(font);
	controls.setColor(sf::Color::Black);
	controls.setCharacterSize(16);
	controls.setPosition(0, H - 185);
	//Menu text setup
	menu.setFont(font);
	menu.setColor(sf::Color::Black);
	menu.setCharacterSize(16);
	menu.setPosition(0, H - 20);
	//Main loop
	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
			if (e.type == sf::Event::KeyPressed)
			{
				//Reset feature
				if (e.key.code == sf::Keyboard::Key::R)
				{
					minRealCords = -2.5;
					maxRealCords = 1;
					minImCords = -1;
					maxImCords = 1;
					zoom = 1;
				}
				//Camera Move
				double w = (maxRealCords - minRealCords) / 5;
				double h = (maxImCords - minImCords) / 5;
				if (e.key.code == sf::Keyboard::Key::W)
				{
					minImCords -= h;
					maxImCords -= h;
				}
				if (e.key.code == sf::Keyboard::Key::S)
				{
					minImCords += h;
					maxImCords += h;
				}
				if (e.key.code == sf::Keyboard::Key::A)
				{
					minRealCords -= w;
					maxRealCords -= w;
				}
				if (e.key.code == sf::Keyboard::Key::D)
				{
					minRealCords += w;
					maxRealCords += w;
				}
				//Make screenshot
				if (e.key.code == sf::Keyboard::Key::P)
					image.saveToFile("./img.jpg");
				//Menu open/close
				if (e.key.code == sf::Keyboard::Key::M)
				{
					if (m)
						m = 0;
					else
						m = 1;
				}
				//Change colouring scheme
				if (e.key.code == sf::Keyboard::Key::C)
				{
					if (c)
					{
						c = 0;
						info.setColor(sf::Color::White);
						controls.setColor(sf::Color::White);
						menu.setColor(sf::Color::White);
					}
					else
					{
						c = 1;
						info.setColor(sf::Color::Black);
						controls.setColor(sf::Color::Black);
						menu.setColor(sf::Color::Black);
					}
				}
				//Close window
				if (e.key.code == sf::Keyboard::Key::Escape)
					window.close();
			}
			//Increase Max Iterations count
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
				double newCenterX = minRealCords + (maxRealCords - minRealCords) * e.mouseButton.x / W;
				double newCenterY = minImCords + (maxImCords - minImCords) * e.mouseButton.y / H;

				//Left Click to ZoomIn
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					//New max/min cords for Real/Im
					double tempMin = newCenterX - (maxRealCords - minRealCords) / zoomValue;
					maxRealCords = newCenterX + (maxRealCords - minRealCords) / zoomValue;
					minRealCords = tempMin;

					tempMin = newCenterY - (maxImCords - minImCords) / zoomValue;
					maxImCords = newCenterY + (maxImCords - minImCords) / zoomValue;
					minImCords = tempMin;

					zoom *= 5;
				}

				//Right Click to ZoomOut
				if (e.mouseButton.button == sf::Mouse::Right)
				{
					//New max/min cords for Real/Im
					double tempMin = newCenterX - (maxRealCords - minRealCords) / 2 * zoomValue;
					maxRealCords = newCenterX + (maxRealCords - minRealCords) / 2 * zoomValue;
					minRealCords = tempMin;

					tempMin = newCenterY - (maxImCords - minImCords) / 2 * zoomValue;
					maxImCords = newCenterY + (maxImCords - minImCords) / 2 * zoomValue;
					minImCords = tempMin;

					if (minRealCords <= -2.5 && maxRealCords >= 1 && minImCords <= -1 && maxImCords >= 1)
					{
						minRealCords = -2.5;
						maxRealCords = 1;
						minImCords = -1;
						maxImCords = 1;
						zoom = 1;
					}

					zoom /= 5;
					if (zoom == 0)
						zoom = 1;
				}
			}
		}

		//Fractal img
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
				//Colouring schemes
				std::vector<sf::Color> colors;
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

				//Calculate number t (0 < t <=1), depending on iterations
				double t;
				int colorSectionPix = maxIteration / (colors.size() - 1);
				if (iteration < colorSectionPix)
					t = (double)iteration / (double)colorSectionPix;
				else
					t = (double)(iteration % colorSectionPix) / (double)colorSectionPix;

				//Find necesary two colors for point
				int i = 0;
				sf::Color imgColor;
				while ((i + 1) * colorSectionPix <= iteration)
					i++;
				if (iteration == maxIteration)
					imgColor = {0, 0, 0};
				else
					imgColor = colorInterpolate(colors[i], colors[i + 1], t);
				//Colouring each pixel
				image.setPixel(x, y, sf::Color(imgColor));
			}
		//Transform our fractal image to texture and then to sprite
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//Zoom and Max Iteration info text
		std::string infoText = "Current zoom: x" + std::to_string(zoom) + "\nMax iterations: " + std::to_string(maxIteration);
		info.setString(infoText);
		//Navigation info text
		std::string controlsText = "Navigation:\nMove: W/A/S/D\nZoom In: Left Click\nZoom Out: Right Click\nReset Zoom: R\nMake Screenshot: P\nIncrease Max Iteration: Scroll Up\nDecrease Max Iteration: Scroll Down\nChange colouring: C\nClose: Escape";
		controls.setString(controlsText);
		//"Show menu" text
		std::string menuText = "Show menu: M";
		menu.setString(menuText);

		window.clear();
		//Drawing all texts and Mandelbro sprite
		window.draw(sprite);
		window.draw(info);
		if (m)
			window.draw(menu);
		else
			window.draw(controls);
		//Displaying result picture
		window.display();
	}
	return 0;
}