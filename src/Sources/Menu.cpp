#include "Headers/Menu.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <iostream>

Menu::Menu()
{
	//Font for texts
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Font int menu, not loaded!!!";
	}
	//Main menu items text setup
	menuItems[0].setFont(font);
	menuItems[0].setString("Draw!");
	menuItems[1].setFont(font);
	menuItems[1].setString("Navigation");
	menuItems[2].setFont(font);
	menuItems[2].setString("Exit");

	selectedItem = 0;
	//Background image loading
	if (!backgroundTexture.loadFromFile("background.jpg"))
	{
		std::cerr << "Background not loaded!";
	}

	//Navigation info text
	nav.setFont(font);
	nav.setCharacterSize(40);
	nav.setOutlineThickness(2.0);
	nav.setFillColor(sf::Color::White);
	std::string controlsText = "Move Camera: W/A/S/D\nZoom In: Left Click\nZoom Out: Right Click\nReset Zoom: R\nMake Screenshot: P\nIncrease Max Iteration: Scroll Up\nDecrease Max Iteration: Scroll Down\nChange colouring: C";
	nav.setString(controlsText);
	//Back text
	back.setFont(font);
	back.setCharacterSize(40);
	back.setOutlineThickness(2.0);
	back.setFillColor(sf::Color::White);
	back.setString("Back to menu");
	//Title text
	title.setFont(font);
	title.setCharacterSize(60);
	title.setOutlineThickness(2.0);
	title.setFillColor(sf::Color::White);
	title.setString("Mandelbrot Set");
	title.setStyle(sf::Text::Bold);
}

Menu::~Menu() {}

//Main menu draw
void Menu::draw(sf::RenderWindow &window)
{
	window.clear();

	int with = window.getSize().x;
	int height = window.getSize().y;
	//Set background image and scale it to fit our window
	scaleX = (float)with / backgroundTexture.getSize().x;
	scaleY = (float)height / backgroundTexture.getSize().y;
	background.setTexture(backgroundTexture);
	background.setScale(scaleX, scaleY);
	window.draw(background);
	//Set possition for each menu item
	menuItems[0].setPosition(with / 2, height / 2 - 1 * 60);
	menuItems[1].setPosition(with / 2, height / 2 + 0 * 60);
	menuItems[2].setPosition(with / 2, height / 2 + 1 * 60);
	//Triger mouse hover each menu item
	if (sf::IntRect(with / 2 - 150, height / 2 - 1 * 60, 300, 40).contains(sf::Mouse::getPosition(window)))
		selectedItem = 0;
	if (sf::IntRect(with / 2 - 150, height / 2 + 0 * 60, 300, 40).contains(sf::Mouse::getPosition(window)))
		selectedItem = 1;
	if (sf::IntRect(with / 2 - 150, height / 2 + 1 * 60, 300, 40).contains(sf::Mouse::getPosition(window)))
		selectedItem = 2;
	//Response on our actions
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
	//"Mandelbrot Set" text in main menu
	title.setPosition(with / 2, 80);
	sf::FloatRect textRect = title.getLocalBounds();
	title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	window.draw(title);

	window.display();
}

//Navigation menu draw
void Menu::navigation(sf::RenderWindow &window)
{
	int with = window.getSize().x;
	int height = window.getSize().y;
	while (window.isOpen())
	{
		window.clear();

		sf::Event e;
		while (window.pollEvent(e))
		{
			//Exit to menu
			if (e.type == sf::Event::KeyPressed)
				if (e.key.code == sf::Keyboard::Key::Escape)
					return;
			if (e.type == sf::Event::MouseButtonPressed)
				if (e.mouseButton.button == sf::Mouse::Left)
					if (sf::IntRect(with / 2 - 150, height - 100, 300, 40).contains(sf::Mouse::getPosition(window)))
						return;
		}
		//Scale background image to fit our window
		scaleX = (float)with / backgroundTexture.getSize().x;
		scaleY = (float)height / backgroundTexture.getSize().y;
		background.setTexture(backgroundTexture);
		background.setScale(scaleX, scaleY);
		window.draw(background);
		//Main text setup
		nav.setPosition(with / 2, height / 2);
		sf::FloatRect textRect = nav.getLocalBounds();
		nav.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		//"Back to menu" text
		back.setPosition(with / 2, height - 80);
		textRect = back.getLocalBounds();
		back.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		//Triger mouse hover "Back to menu"
		if (sf::IntRect(with / 2 - 150, height - 100, 300, 40).contains(sf::Mouse::getPosition(window)))
		{
			back.setFillColor(sf::Color::Red);
			back.setStyle(sf::Text::Bold | sf::Text::Underlined);
		}
		else
		{
			back.setFillColor(sf::Color::White);
			back.setStyle(sf::Text::Bold);
		}
		//Draw all
		window.draw(back);
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