#include "Headers/Application.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

Application::Application()
{
	//Window setup
	window.create(sf::VideoMode(W, H), "Mendelbrot Set", sf::Style::Fullscreen);
	image.create(W, H);
	//Font checking
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Font not loaded!!!";
	}
	//Info text setup
	info.setFont(font);
	info.setFillColor(sf::Color::White);
	info.setCharacterSize(16);
	//Menu text setup
	menu.setFont(font);
	menu.setFillColor(sf::Color::White);
	menu.setCharacterSize(16);
	menu.setPosition(0, H - 20);
	//Setting setup
	maxIteration = 128;
	zoom = 1;
	minRealCords = -2.5, maxRealCords = 1;
	minImCords = -1, maxImCords = 1;
	c = 1;
}

Application::~Application() {}

void Application::run()
{
	while (window.isOpen())
	{
		Menu.draw(window);
		menuKeyActions();
	}
}

void Application::start()
{
	minRealCords = -2.5, maxRealCords = 1;
	minImCords = -1, maxImCords = 1;
	while (window.isOpen())
	{
		draw();
		keyActions();
	}
}

void Application::draw()
{
	updateText();
	//Calculate and draw fractal
	Mandelbrote.drawFractal(maxIteration, H, W, minRealCords, maxRealCords, minImCords, maxImCords, image, c);
	//Transform our fractal image to texture and then to sprite
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	window.clear();
	//Drawing all texts and Fractal sprite
	window.draw(sprite);
	window.draw(info);
	window.draw(menu);
	//Displaying result picture
	window.display();
}

void Application::updateText()
{
	std::string infoText = "Current zoom: x" + std::to_string(zoom) + "\nMax iterations: " + std::to_string(maxIteration);
	info.setString(infoText);
	//"Show menu" text
	std::string menuText = "Exit to menu: Escape";
	menu.setString(menuText);
}

void Application::keyActions()
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
				image.saveToFile("./screenshot.jpg");
			//Change colouring scheme
			if (e.key.code == sf::Keyboard::Key::C)
			{
				if (c)
				{
					c = 0;
				}
				else
				{
					c = 1;
				}
			}
			//Exit to menu
			if (e.key.code == sf::Keyboard::Key::Escape)
				run();
		}
		//Increase Max Iterations count
		if (e.type == sf::Event::MouseWheelScrolled)
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
}

void Application::menuKeyActions()
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			window.close();
		if (e.type == sf::Event::MouseButtonPressed)
			if (e.mouseButton.button == sf::Mouse::Left)
				switch (Menu.getSelectedItem())
				{
				case 0:
					start();
					break;
				case 1:
					Menu.navigation(window);
					break;
				case 2:
					window.close();
					break;

				default:
					break;
				}

		if (e.type == sf::Event::KeyPressed)
		{
			//Exit
			if (e.key.code == sf::Keyboard::Key::Escape)
				window.close();
			//Select up menu item
			if (e.key.code == sf::Keyboard::Key::Up)
			{
				Menu.MenuUp();
			}
			//Select down menu item
			if (e.key.code == sf::Keyboard::Key::Down)
			{
				Menu.MenuDown();
			}
			if (e.key.code == sf::Keyboard::Key::Return)
			{
				switch (Menu.getSelectedItem())
				{
				case 0:
					start();
					break;
				case 1:
					Menu.navigation(window);
					break;
				case 2:
					window.close();
					break;

				default:
					break;
				}
			}
		}
	}
}