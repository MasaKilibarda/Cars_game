// Cars_game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include<sstream>
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

		Clock gas;
		//Game start
		//Time dt 
		//Time bar
		RectangleShape timeBar;
		float timeBarStartWidth = 400;
		float timeBarHeight = 50;
		timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
		timeBar.setFillColor(Color::Green);
		timeBar.setPosition(40, 40);
		//timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
		Time gameTimeTotal;
		float timeRemaining = 6.0f;
		float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

		bool pause = true;

		//Draw some text
		int score = 0;
		sf::Text messageText;
		sf::Text scoreText;
		sf::Text gasText;
		//We need to chose a font
		Font font;
		font.loadFromFile("font/comic.ttf");
		//Set the font to our message
		messageText.setFont(font);
		scoreText.setFont(font);
		gasText.setFont(font);
		//Assign the actual message
		messageText.setString("Press Enter to start!");
		scoreText.setString("Score = 0");
		gasText.setString("Gas");
		//Make it really big
		messageText.setCharacterSize(90);
		scoreText.setCharacterSize(60);
		gasText.setCharacterSize(60);
		//Choose a color
		messageText.setFillColor(Color::White);
		scoreText.setFillColor(Color::White);
		gasText.setFillColor(Color::White);

		//Position the text
		FloatRect textRect = messageText.getLocalBounds();
		messageText.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		messageText.setPosition(1920 / 2.0f-200, 1080 / 2.0f-200);
		scoreText.setPosition(1050, 20);
		gasText.setPosition(40, 25);

		while (window.isOpen()) {

			/*
			**************************
			*Handle the players input*
			**************************
			*/

			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}
			//When a press Enter key, pause become false
			
			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				pause = false;
				//Reset the time and the score
				score = 0;
				timeRemaining = 5;
			}

			/*
			*****************
			Update the scene
			*****************
			*/

			if (!pause) {
				
				Time dt = gas.restart();
				timeRemaining -= dt.asSeconds();
				//Size up the time bar
				timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

				if (timeRemaining <= 0.0f) {
					pause = true;
					messageText.setString("Out of gas!");
					//Reposition the text based on its new size
					FloatRect textRect = messageText.getLocalBounds();
					messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				}
				//Update the score text
			    std::stringstream ss;
				ss << "Score = " << score;
			    scoreText.setString(ss.str());
			
			
			}//End if(!pause)


			/*			
			****************
			*Draw the scene*
			****************
			*/
			window.clear();
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
			//draw the score
			window.draw(timeBar);
			window.draw(gasText);
			window.draw(scoreText);
			
			if (pause) {
			//draw our message
			window.draw(messageText);
			}
			
			window.display();
			}
    return 0;
}

