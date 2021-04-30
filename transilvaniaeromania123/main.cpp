#include <SFML/Graphics.hpp>
#include <iostream>
#include "HamiltonSnake.h"
#include "Snake.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(838,838),"SNAK", sf::Style::Close);
	window.setFramerateLimit(60);
	while (window.isOpen()) {
		sf::Vector2f mp;
		mp.x = sf::Mouse::getPosition(window).x;
		mp.y = sf::Mouse::getPosition(window).y;
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			
			case sf::Event::MouseButtonPressed:
				if (mp.x > 50 && mp.x < 200 && mp.y>150 && mp.y < 200)
				{//snake.cpp
					runSelf(window);
				}
				if (mp.x > 50 && mp.x < 200 && mp.y>250 && mp.y < 300)
					//hamilton.cpp
					runGame(window);
				break;

				
			default:
				
				window.clear();
				sf::Texture backgroundImage;
				backgroundImage.loadFromFile("homescreen.png");
				sf::Sprite background(backgroundImage);
				
				window.draw(background);
				sf::RectangleShape button1, button2;
				button1.setSize(sf::Vector2f(150,50));
				button1.setPosition(50, 150);
				button1.setFillColor(sf::Color(160, 100, 100));
				button2.setSize(sf::Vector2f(150, 50));
				button2.setPosition(50, 250);
				button2.setFillColor(sf::Color(100, 160, 100));
				window.draw(button1);
				window.draw(button2);
				sf::Font font;
				font.loadFromFile("SAnS.ttf");
				sf::Text btext1("Play Yourself", font, 20);
				btext1.setPosition(60, 165);
				window.draw(btext1);
				sf::Text btext2("Watch it play", font, 20);
				btext2.setPosition(60, 265);
				window.draw(btext2);



				window.display();
				break;
			}
		}
	}
}