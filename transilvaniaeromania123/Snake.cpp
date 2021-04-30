#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include "Header.h"


using namespace std;
#define SIZE 14

int xapple;
int yapple;
int xmiscare , ymiscare;
int lungimesarpe , xhead , yhead;
int xstiva[101], ystiva[101];
int landa;

bool gg = false;
void value()
{
	xmiscare = 0;
	ymiscare = 0;
	lungimesarpe = 1;
	xhead = SIZE / 2 + 1;
	yhead = SIZE / 2 + 1;
	xstiva[101] = { 0 };
	ystiva[101] = { 0 };
	gg = false;
}

void eat()
{
	int auxx = xapple, auxy = yapple;
	bool ok = false;
	lungimesarpe++;
	if (lungimesarpe == SIZE * SIZE)
	{
		gg = true;
		ok = true;
	}
	while (!ok)
	{
		ok = true;
		xapple = rand() % SIZE + 1;
		yapple = rand() % SIZE + 1;
		if (xapple == auxx && yapple == auxy)
		{
			ok = false;
			break;
		}
		if (xapple == xhead && yapple == yhead)
		{
			ok = false;
			break;
		}
		for (int i = 0; i <= lungimesarpe; i++)
		{
			if (xapple == xstiva[i] && yapple == ystiva[i])
			{
				ok = false;
				break;
			}
		}
	}

}

void verificare()
{
	if (xhead == 0 || xhead == SIZE + 1 || yhead == 0 || yhead == SIZE + 1)
		gg = true;
	else
	{
		for (int i = 2; i <= lungimesarpe; i++)
			if (xhead == xstiva[i] && yhead == ystiva[i])
			{
				gg = true;
				break;
			}
	}
}

void movee()
{
	xhead += xmiscare;
	yhead += ymiscare;
	if (xhead == xapple && yhead == yapple)
		eat();
	for (int i = lungimesarpe; i > 1; i--)
	{
		xstiva[i] = xstiva[i - 1];
		ystiva[i] = ystiva[i - 1];
	}
	xstiva[1] = xhead;
	ystiva[1] = yhead;
	verificare();
}

void draw(sf::RenderWindow& window)
{
	window.clear();
	for (int i = 1; i <= SIZE; i++)
	{
		for (int j = 1; j <= SIZE; j++)
		{
			if (i == xapple && j == yapple)
			{
				sf::RectangleShape mar;
				mar.setSize(sf::Vector2f(30, 30));
				mar.setPosition(205 + (i - 1) * 30, 205 + (j - 1) * 30);
				mar.setFillColor(sf::Color(220, 20, 60));
				window.draw(mar);
			}
			else
			{
				bool a = false;
				for (int l = 1; l <= lungimesarpe; l++)
				{
					if (i == xstiva[l] && j == ystiva[l])
					{
						sf::RectangleShape snake;
						snake.setSize(sf::Vector2f(30, 30));
						snake.setPosition(205 + (i - 1) * 30, 205 + (j - 1) * 30);
						snake.setFillColor(sf::Color(0, 255, 0));
						window.draw(snake);
						a = true;
					}

				}
				if (!a)
				{
					sf::RectangleShape space;
					space.setSize(sf::Vector2f(30, 30));
					space.setPosition(205 + (i - 1) * 30, 205 + (j - 1) * 30);
					if ((i + j) % 2 == 0)
						space.setFillColor(sf::Color(128, 128, 128));
					else
						space.setFillColor(sf::Color(105, 105, 105));
					window.draw(space);
				}
			}
		}
	}
	window.display();
}

void presscheck(sf::RenderWindow& window)
{
	sf::Event apasare;
	if (window.pollEvent(apasare))
	{
		if (apasare.type == sf::Event::KeyReleased)
		{
			if (xmiscare == 0 ||lungimesarpe==1)
			{
				if (apasare.key.code == sf::Keyboard::A)
				{
					xmiscare = -1;
					ymiscare = 0;
				}
				if (apasare.key.code == sf::Keyboard::D)
				{
					xmiscare = 1;
					ymiscare = 0;
				}
			}
			if (ymiscare == 0||lungimesarpe==1)
			{
				if (apasare.key.code == sf::Keyboard::W)
				{
					xmiscare = 0;
					ymiscare = -1;
				}
				if (apasare.key.code == sf::Keyboard::S)
				{
					xmiscare = 0;
					ymiscare = 1;
				}
			}
		}
		else if (apasare.type == sf::Event::Closed)
		{
			window.close();
			gg=true;
		}
	}
	/*if (_kbhit)
	{
		char a;
		a = _getch();
		{
			if (xmiscare == 0)
			{
				if (a == 'w')
				{
					xmiscare = -1;
					ymiscare = 0;
				}
				else if (a == 's')
				{
					xmiscare = 1;
					ymiscare = 0;
				}
			}
			else if (ymiscare == 0)
			{
				if (a == 'a')
				{
					xmiscare = 0;
					ymiscare = -1;
				}
				else if (a == 'd')
				{
					xmiscare = 0;
					ymiscare = 1;
				}
			}
		}
	}*/


}

int runSelf(sf::RenderWindow& window)
{
	value();
	window.create(sf::VideoMode(838, 838), "SNAK", sf::Style::Close);
	srand(time(NULL));
	xapple = rand() % SIZE + 1;
	yapple = rand() % SIZE + 1;
	while (xapple == xhead && yapple == yhead)
	{
		xapple = rand() % SIZE + 1;
		yapple = rand() % SIZE + 1;
	}
	window.clear();
	window.display();
	xstiva[1] = xhead;
	ystiva[1] = yhead;
	draw(window);
	while (!gg)
	{
		landa++;
		presscheck(window);
		if (landa > 120000)
		{
			movee();
			draw(window);
			landa = 0;
		}
	}
	return 42;
}

















