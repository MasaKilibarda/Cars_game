// Cars_game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include<sstream>
using namespace sf;

void updateCars(int seed);
const int NUM_CARS = 6;
Sprite cars[NUM_CARS];
//enum for cars and player side
enum class side { LEFT, RIGHT, NONE };
side carsPositions[NUM_CARS];

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
		/*Sprite spriteCar1;
		spriteCar1.setTexture(textureCar1);
		spriteCar1.setPosition(460, 300);*/

		Texture textureCar2;
		textureCar2.loadFromFile("graphics/Auto2.png");
		/*Sprite spriteCar2;
		spriteCar2.setTexture(textureCar2);
		spriteCar2.setPosition(830, 80);*/


		Texture textureCar3;
		textureCar3.loadFromFile("graphics/Auto4.png");
		Texture textureCar4;
		textureCar4.loadFromFile("graphics/Auto5.png");
		Texture textureCar5;
		textureCar5.loadFromFile("graphics/Auto6.png");
		Texture textureCar6;
		textureCar6.loadFromFile("graphics/Auto7.png");
		

		cars[0].setTexture(textureCar1);
		cars[1].setTexture(textureCar2);
		cars[2].setTexture(textureCar3);
		cars[3].setTexture(textureCar4);
		cars[4].setTexture(textureCar5);
		cars[5].setTexture(textureCar6);


		for (int i=0; i < NUM_CARS; i++)
			cars[i].setPosition(-2000,-2000);


		Texture texturePlayer;
		texturePlayer.loadFromFile("graphics/Igrac.png");
		Sprite spritePlayer;
		spritePlayer.setTexture(texturePlayer);
		spritePlayer.setPosition(830, 550);

		//The player starts on the right
		side playerSide = side::RIGHT;

		//Prepare the Rip(can) :D
		Texture textureRIP;
		textureRIP.loadFromFile("graphics/Rip.png");
		Sprite spriteRIP;
		spriteRIP.setTexture(textureRIP);
		spriteRIP.setPosition(0, 200);
		//spriteRIP.setPosition(850, 650);

		//Prepare the can oil
		Texture textureOil;
		textureOil.loadFromFile("graphics/oil.png");
		Sprite spriteOil;
		spriteOil.setTexture(textureOil);
		spriteOil.setPosition(680,570);

		bool oilActive = false;
		float oilSpeedX = 1000;
		float oilSpeedY = -1500;

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

		updateCars(1);
		updateCars(2);
		updateCars(3);
		updateCars(4);
		updateCars(5);

		bool acceptInput = false;

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

				//Make all the cars disappear
				for (int l = 1; l < NUM_CARS; l++) 
					carsPositions[l] = side::NONE;
					spriteRIP.setPosition(675, 2000);
					spritePlayer.setPosition(830, 550);
					acceptInput = true;
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
			
				// update the cars sprites
				for (int i = 0; i < NUM_CARS; i++)
				{
					float height = (float)i * 100+80;
					if (carsPositions[i] == side::LEFT)
					{
						// Move the sprite to the left side
						cars[i].setPosition(460, height);
						// Flip the sprite round the other way
						cars[i].setRotation(0);
					}
					else if (carsPositions[i] == side::RIGHT)
					{
						// Move the sprite to the right side
						cars[i].setPosition(830, height);
						// Set the sprite rotation to normal
						cars[i].setRotation(0);
					}
					else
					{
						// Hide the branch
						cars[i].setPosition(3000, height);

					}
				}

				


			/*			
			****************
			*Draw the scene*
			****************
			*/
			window.clear();
			window.draw(spriteBackground);
			window.draw(spritePump);
			window.draw(spriteTunel);
			window.draw(spriteOil);
			window.draw(spriteRIP);
		
			for (int i = 0; i < NUM_CARS; i++)
			{
				window.draw(cars[i]);
			}
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

// Function definition
void updateCars(int seed)
{
	// Move all the branches down one place
	for (int j = NUM_CARS - 1; j > 0; j--)
	{
		carsPositions[j] = carsPositions[j - 1];
	}
	// Spawn a new branch at position 0
	// LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r)
	{
	case 0:
		carsPositions[0] = side::LEFT;
		break;
	case 1:
		carsPositions[0] = side::RIGHT;
		break;
	default:
		carsPositions[0] = side::NONE;
		break;
	}
}





