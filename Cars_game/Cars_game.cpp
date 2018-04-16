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
        
		Texture textureTunel;
		textureTunel.loadFromFile("graphics/tunel_1.png");
		Sprite spriteTunel;
		spriteTunel.setTexture(textureTunel);
		spriteTunel.setPosition(-20,-270);

		Texture texturePump;
		texturePump.loadFromFile("graphics/pumpa.png");
		Sprite spritePump;
		spritePump.setTexture(texturePump);
		spritePump.setPosition(590,180);

		Clock gas;
		//Igrica krece
		bool pause = true;

		while (window.isOpen()) {

			/*
			**************************
			*Handle the players input*
			**************************
			*/

			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}
			//Kada pritisnemo Enter pause menja se na false
			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				pause = false;
			}

			/*
			******************
			*Update the scene*
			******************
			*/

			if (!pause) {
			
			}//End if(!pause)


			/*
			****************
			*Draw the scene*
			****************
			*/
			}
        
		Texture textureCar1;
		textureCar1.loadFromFile("graphics/Auto3.png");
		Sprite spriteCar1;
		spriteCar1.setTexture(textureCar1);
		spriteCar1.setPosition(460, 300);

		Texture textureCar2;
		textureCar2.loadFromFile("graphics/Auto2.png");
		Sprite spriteCar2;
		spriteCar2.setTexture(textureCar2);
		spriteCar2.setPosition(830, 80);

		
		Texture textureCar3;
		textureCar3.loadFromFile("graphics/Auto4.png");
		Sprite spriteCar3;
		spriteCar3.setTexture(textureCar3);
		spriteCar3.setPosition(830, 400);

		Texture textureCar4;
		textureCar4.loadFromFile("graphics/Auto5.png");
		Sprite spriteCar4;
		spriteCar4.setTexture(textureCar4);
		spriteCar4.setPosition(460, 100);

		Texture textureCar5;
		textureCar5.loadFromFile("graphics/Auto6.png");
		Sprite spriteCar5;
		spriteCar5.setTexture(textureCar5);
		spriteCar5.setPosition(830, 250);

		Texture textureCar6;
		textureCar6.loadFromFile("graphics/Auto7.png");
		Sprite spriteCar6;
		spriteCar6.setTexture(textureCar6);
		spriteCar6.setPosition(460, 450);


		Texture texturePlayer;
		texturePlayer.loadFromFile("graphics/Igrac.png");
		Sprite spritePlayer;
		spritePlayer.setTexture(texturePlayer);
		spritePlayer.setPosition(830, 550);

		while (window.isOpen()) {
			if (Keyboard::isKeyPressed(Keyboard::Escape))
					{
						window.close();
					}
			//window.clear();
			window.draw(spriteBackground);
			window.draw(spritePump);
			window.draw(spriteTunel);
			window.draw(spriteCar1);
			window.draw(spriteCar2);
			window.draw(spriteCar3);
			window.draw(spriteCar4);
			window.draw(spriteCar5);
			window.draw(spriteCar6);
			window.draw(spritePlayer);
			window.display();
		}
    return 0;
}

