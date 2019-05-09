#include "Headers/Menu.hpp"
#include <iostream>

Menu::Menu()
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Font int menu, not loaded!!!";
	}
	menuItems[0].setFont(font);
	menuItems[0].setString("Draw!");

	menuItems[1].setFont(font);
	menuItems[1].setString("Navigation");

	menuItems[2].setFont(font);
	menuItems[2].setString("Exit");

	selectedItem = 0;

	if (!backgroundTexture.loadFromFile("background.jpg"))
	{
		std::cerr << "Background not loaded!";
	}

	//Navigation info text
	nav.setFont(font);
	nav.setCharacterSize(40);
	nav.setOutlineThickness(2.0);
	nav.setFillColor(sf::Color::White);
	std::string controlsText = "Move Camera: W/A/S/D\nZoom In: Left Click\nZoom Out: Right Click\nReset Zoom: R\nMake Screenshot: P\nIncrease Max Iteration: Scroll Up\nDecrease Max Iteration: Scroll Down\nChange colouring: C\nReturn to menu: Escape";
	nav.setString(controlsText);
}

Menu::~Menu() {}

void Menu::draw(sf::RenderWindow &window)
{

		window.clear();

		int with = window.getSize().x;
		int height = window.getSize().y;

		scaleX = (float)with / backgroundTexture.getSize().x;
		scaleY = (float)height / backgroundTexture.getSize().y;
		background.setTexture(backgroundTexture);
		background.setScale(scaleX, scaleY);
		window.draw(background);

		menuItems[0].setPosition(with / 2, height / 2 - 1 * 60);
		menuItems[1].setPosition(with / 2, height / 2 + 0 * 60);
		menuItems[2].setPosition(with / 2, height / 2 + 1 * 60);
		for (int i = 0; i < 3; i++)
		{
			if (i == selectedItem)
			{
				menuItems[i].setFillColor(sf::Color::Red);
				menuItems[i].setStyle(sf::Text::Bold | sf::Text::Underlined);
			}
			else
			{
				menuItems[i].setFillColor(sf::Color::White);
				menuItems[i].setStyle(sf::Text::Bold);
			}

			sf::FloatRect textRect = menuItems[i].getLocalBounds();
			menuItems[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			menuItems[i].setCharacterSize(40);
			menuItems[i].setOutlineThickness(2.0);

			window.draw(menuItems[i]);
		}
		window.display();

}

void Menu::navigation(sf::RenderWindow &window)
{
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::KeyPressed)
			{
				//Exit to menu
				if (e.key.code == sf::Keyboard::Key::Escape)
					return;
			}
		}
		window.clear();

		int with = window.getSize().x;
		int height = window.getSize().y;

		scaleX = (float)with / backgroundTexture.getSize().x;
		scaleY = (float)height / backgroundTexture.getSize().y;
		background.setTexture(backgroundTexture);
		background.setScale(scaleX, scaleY);
		window.draw(background);

		nav.setPosition(with / 2, height / 2);

		sf::FloatRect textRect = nav.getLocalBounds();
		nav.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		window.draw(nav);

		window.display();
	}
}

void Menu::MenuUp()
{
	if (selectedItem > 0)
		selectedItem--;
}

void Menu::MenuDown()
{
	if (selectedItem < 2)
		selectedItem++;
}

int Menu::getSelectedItem() const
{
	return selectedItem;
}