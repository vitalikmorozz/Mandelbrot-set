#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

class Menu
{
private:
	sf::Text menuItems[3], nav, back, title;
	sf::Font font;
	sf::Texture backgroundTexture;
	sf::Sprite background;
	int selectedItem;
	float scaleX, scaleY;

public:
	Menu();
	~Menu();
	void MenuUp();
	void MenuDown();
	void navigation(sf::RenderWindow &window);
	int getSelectedItem()const;
	void draw(sf::RenderWindow &window);

protected:
};