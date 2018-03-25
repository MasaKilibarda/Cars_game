// Cars_game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>

using namespace sf;
int main()
{
		VideoMode vm(1920, 1080);
		RenderWindow window(vm, "carsss", Style::Fullscreen);
		
		Texture textureBakground;
		textureBakground.loadFromFile("graphics/put_veliki.png");
		Sprite spriteBackground;
		spriteBackground.setTexture(textureBakground);
		spriteBackground.setPosition(-300, -200);

		Texture texturePump;
		texturePump.loadFromFile("graphics/gas.png");
		Sprite spritePump;
		spritePump.setTexture(texturePump);
		spritePump.setPosition(570,150);

		while (window.isOpen()) {
			if (Keyboard::isKeyPressed(Keyboard::Escape))
					{
						window.close();
					}
			//window.clear();
			window.draw(spriteBackground);
			window.draw(spritePump);
			window.display();
		}
    return 0;
}

