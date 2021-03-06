// Cars_game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include<sstream>
#include<SFML/Audio.hpp>
using namespace sf;


void updateCars(int seed);
const int NUM_CARS = 5;
Sprite cars[NUM_CARS];
//enum for cars and player side
enum class side { LEFT, RIGHT, NONE };
side carsPositions[NUM_CARS];

int RIGTH_PL = 830;
int LEFT_PL=400;
int LEFT_CARS = 460;
int HEIGHT_PL = 550;
float GAS_RM = 4;
float SCORE_ADD = 5;
int OUT_OF_SC = 2000;

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
	spriteTunel.setPosition(-20, -270);

	Texture texturePump;
	texturePump.loadFromFile("graphics/pumpa.png");
	Sprite spritePump;
	spritePump.setTexture(texturePump);
	spritePump.setPosition(590, 180);

	Texture textureSign;
	textureSign.loadFromFile("graphics/Road-Signs.png");
	Sprite spriteSign;
	spriteSign.setTexture(textureSign);
	spriteSign.setPosition(400,20);

	Texture textureStop;
	textureStop.loadFromFile("graphics/stop.png");

	Texture textureCar1;
	textureCar1.loadFromFile("graphics/Auto3.png");
	Texture textureCar2;
	textureCar2.loadFromFile("graphics/Auto2.png");
	Texture textureCar3;
	textureCar3.loadFromFile("graphics/Auto4.png");
	Texture textureCar4;
	textureCar4.loadFromFile("graphics/Auto5.png");
	Texture textureCar5;
	textureCar5.loadFromFile("graphics/Auto6.png");
	

	//pre side,default left=0
	static int preSide = 0;

	cars[0].setTexture(textureCar1);
	cars[1].setTexture(textureCar2);
	cars[2].setTexture(textureCar3);
	cars[3].setTexture(textureCar4);
	cars[4].setTexture(textureCar5);
	
	for (int i = 0; i < NUM_CARS; i++)
		cars[i].setPosition(OUT_OF_SC,OUT_OF_SC);


	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/Igrac.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(LEFT_PL,HEIGHT_PL);

	//The player starts on the left
	side playerSide = side::LEFT;

	//Prepare the Rip(can) 
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/Rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(OUT_OF_SC,OUT_OF_SC);
	

	//Prepare the can oil
	Texture textureOil;
	textureOil.loadFromFile("graphics/oil.png");
	Sprite spriteOil;
	spriteOil.setTexture(textureOil);
	spriteOil.setPosition(680, 570);

	bool oilActive = false;
	float oilSpeedX = 1000;
	float oilSpeedY = -1500;

	Clock gas;
	//Time dt 
	//Time bar
	RectangleShape gasBar;
	float gasBarWidth = 50;
	float gasBarStartHeight = 400;
	gasBar.setSize(Vector2f(gasBarWidth, gasBarStartHeight));
	gasBar.setFillColor(Color::Green);
	gasBar.setPosition(75,600);
	gasBar.setRotation(180);
	Time gameTimeTotal;
	float gasRemaining = GAS_RM;
	float gasBarHeigthPerSecond = gasBarStartHeight / gasRemaining;

	bool pause = true;

	//Draw some text
	int score = 0;
	Text messageText;
	Text scoreText;
	Text gasText;
	Text instructText;
	//We need to chose a font
	Font font;
	font.loadFromFile("font/comic.ttf");
	//Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);
	gasText.setFont(font);
	instructText.setFont(font);
	//Assign the actual message
	instructText.setString("  Instructions\n-Press left arrow to go left\n-Press right arrow to to right\n-Cross over pump to get gas");
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");
	gasText.setString("Gas");
	//Make it really big
	messageText.setCharacterSize(68);
	scoreText.setCharacterSize(60);
	gasText.setCharacterSize(60);
	instructText.setCharacterSize(45);
	//Choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);
	gasText.setFillColor(Color::White);
	instructText.setFillColor(Color::White);

	//Position the text
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	messageText.setPosition(750,570);
	scoreText.setPosition(1000, 20);
	gasText.setPosition(14, 600);
	gasText.setRotation(-90);
	instructText.setPosition(425,170);

	bool acceptInput = false;


	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	//out of time
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_gas.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);

	SoundBuffer bumpBuffer;
	bumpBuffer.loadFromFile("sound/bump.wav");
	Sound bump;
	bump.setBuffer(bumpBuffer);

	SoundBuffer raceBuffer;
	raceBuffer.loadFromFile("sound/race_track.wav");
	Sound race;
	race.setBuffer(raceBuffer);

	
	while (window.isOpen()) 
	{
		/*
		**************************
		*Handle the players input*
		**************************
		*/
		Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::KeyReleased && !pause) 
			{
				acceptInput = true;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) 
		{
			window.close();
		}
		//When a press Enter key, pause become false

		if (Keyboard::isKeyPressed(Keyboard::Return)) 
		{
			pause = false;
			//Reset the time and the score
			score = 0;
			gasRemaining = GAS_RM;// 8;

			for (int i = 0; i < NUM_CARS; i++)
			{
				carsPositions[i] = side::NONE;
			}
			outOfTime.stop();
			race.play();
			instructText.setPosition(OUT_OF_SC,OUT_OF_SC);
			spriteSign.setPosition(OUT_OF_SC,OUT_OF_SC);
			spriteRIP.setPosition(OUT_OF_SC,OUT_OF_SC);
			
			spritePlayer.setPosition(LEFT_PL,HEIGHT_PL);

			acceptInput = true;
		}

		if (acceptInput)
		{
			// First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				// Make sure the player is on the right
				playerSide = side::RIGHT;
				score +=SCORE_ADD;
				// Add to the amount of gas remaining
				if (preSide == 0)
				{
					gasRemaining += (2 / score) + .40;
					//rightSide=1
					preSide = 1;
                    // set the oil flying to the left
				   spriteOil.setPosition(680,570);
				   oilSpeedX = -5000;
				   oilActive = true;
				   bump.play();
				}
				spritePlayer.setPosition(RIGTH_PL,HEIGHT_PL);
				// update the cars
				updateCars(score);
				
				acceptInput = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				playerSide = side::LEFT;
				score +=SCORE_ADD;
				if (preSide == 1) {
					gasRemaining += (2 / score) + .40;
					//leftSide=0
					preSide = 0;
					//set the oil flying to the right
				    spriteOil.setPosition(680,570);
				    oilSpeedX = -5000;
				    oilActive = true;
					bump.play();
				}
				spritePlayer.setPosition(LEFT_PL,HEIGHT_PL);
				//update the cars
				updateCars(score);
				
				acceptInput = false;

			}

			
		}

		/*
		*****************
		Update the scene
		*****************
		*/

		if (!pause) 
		{

			Time dt = gas.restart();
			gasRemaining -= dt.asSeconds();
			//Size up the time bar
			gasBar.setSize(Vector2f(gasBarWidth , gasBarHeigthPerSecond * gasRemaining));

			if (gasRemaining < 0.0f) 
			{
				pause = true;
				messageText.setString("Out of gas!");
				//Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(640,250);
				race.stop();
				outOfTime.play();
				spriteSign.setTexture(textureStop);
				spriteSign.setPosition(390, 10);
			}
			//Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			// update the cars sprites
			for (int i = 0; i < NUM_CARS; i++)
			{
				float height = (float)i * 129 + 80;
				if (carsPositions[i] == side::LEFT)
				{
					// Move the sprite to the left side
					cars[i].setPosition(LEFT_CARS, height);
					// Flip the sprite round the other way
					cars[i].setRotation(0);
				}
				else if (carsPositions[i] == side::RIGHT)
				{
					// Move the sprite to the right side
					cars[i].setPosition(RIGTH_PL, height);
					// Set the sprite rotation to normal
					cars[i].setRotation(0);
				}
				else
				{
					// Hide the car
					cars[i].setPosition(OUT_OF_SC, height);
				}

			}

			// Handle a flying oil
			if (oilActive)
			{
				spriteOil.setPosition(
					spriteOil.getPosition().x +
					(oilSpeedX * dt.asSeconds()),
					spriteOil.getPosition().y +
					(oilSpeedY * dt.asSeconds()));
				//spriteOil.setPosition(50, 50);
				// Has the log reached the right hand edge?
				if (spriteOil.getPosition().x < -100 ||
					spriteOil.getPosition().x > 2000)
				{
					// Set it up ready to be a whole new log next frame
					oilActive = false;
					spriteOil.setPosition(680, 570);
				}
			}

			//Has the player been smashed by other car?
			if (carsPositions[4] == playerSide) 
			{
				pause = true;
				acceptInput = false;

				//draw the rip-can
				if(playerSide==side::LEFT)
				 spriteRIP.setPosition(LEFT_CARS,HEIGHT_PL);
				else
			     spriteRIP.setPosition(RIGTH_PL, HEIGHT_PL);
				
				spritePlayer.setPosition(OUT_OF_SC,OUT_OF_SC);

				for (int i = 0; i < NUM_CARS; i++)
				{
					cars[i].setPosition(OUT_OF_SC,OUT_OF_SC);
				}

				//TEXT MESSAGE
				messageText.setString("SMASHED!!\nGAME OVER");
				//centar it on the screen
				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left + textRect.width/2.0f,
					textRect.top + textRect.height/2.0f);

				messageText.setPosition(635,250);
				race.stop();
				death.play();
				spriteSign.setTexture(textureStop);
				spriteSign.setPosition(375,15);
			}

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
		window.draw(spriteOil);
		
		
		for (int i = 0; i < NUM_CARS; i++)
		{
			window.draw(cars[i]);
		}
        window.draw(spriteRIP);
		window.draw(spritePlayer);
        
		//draw the score
		window.draw(gasBar);
		window.draw(gasText);
		window.draw(scoreText);
		

		if (pause) 
		{
            window.draw(spriteSign);
			//draw our message
			window.draw(messageText);
		}
        window.draw(instructText);

		window.display();
	}
	return 0;
}

// Function definition
void updateCars(int seed)
{
	// Move all the cars down one place
	for (int j = NUM_CARS - 1; j > 0; j--)
	{
		carsPositions[j] = carsPositions[j - 1];
		Sprite tmp;
		tmp = cars[j - 1];
		cars[j-1] =cars[j];
		cars[j] = tmp;
	}
	// Spawn a new car at position 0
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