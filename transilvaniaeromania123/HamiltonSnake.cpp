#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include "Header.h"


using namespace std;
#define SIZE 6


int graf[SIZE * SIZE + 2][SIZE * SIZE + 2];
int hamilton[SIZE * SIZE + 2];
int vizita[SIZE * SIZE + 2];
int movelist[SIZE * SIZE + 2];
int xmar;
int ymar;
int xmove , ymove;
int lsarpe , xcap , ycap ;
int xcoada[SIZE * SIZE + 2], ycoada[SIZE * SIZE + 2];
int k = 0;
int delta;

bool ok = true;
bool gameover = false;

void valoare()
{
	xmove = 0, ymove = 0;
	lsarpe = 1, xcap = SIZE / 2, ycap = SIZE / 2;
	xcoada[SIZE * SIZE + 2] = { 0 }, ycoada[SIZE * SIZE + 2] = { 0 };
	k = 0;
	ok = true;
	gameover = false;
}


void genGraf()
{
	/*
	SIZE=3
	1 2 3 4| 0 0 0	  i-SIZE
	5 6 6 | 0 0 0 i-1  i  i+1
	7 8 9 | 0 0 0	  i+SIZE

	1 2 3 4
	5 6 7 8
	9 10 11 12
	13 14 15 16

	0 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0
	1 0 1 0 0 1 0 0 0 0 0 0 0 0 0 0
	0 1 0 1 0 0 1 0 0 0 0 0 0 0 0 0
	0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0
	1 0 0 0 0 1 0 0 1 0 0 0 0 0 0 0
	0 1 0 0 1 0 1 0 0 1 0 0 0 0 0 0
	0 0 1 0 0 1 0 1 0 0 1 0 0 0 0 0
	0 0 0 1 0 0 1 0 0 0 0 1 0 0 0 0
	*/
	
	for (int i = 1; i <= SIZE * SIZE; i++)
	{
		if (i - SIZE > 0)
			graf[i][i - SIZE] = 1;
		if (i + SIZE <= SIZE * SIZE)
			graf[i][i + SIZE] = 1;
		if ((i - 1) % SIZE != 0)
			graf[i][i - 1] = 1;
		if ((i + 1) % SIZE != 1)
			graf[i][i + 1] = 1;
	}

}

void NextValue(int k) {
	do
	{
		hamilton[k] = (hamilton[k] + 1) % (SIZE * SIZE + 1);
		if (hamilton[k] == 0)
			return;
		if (graf[hamilton[k - 1]][hamilton[k]] != 0)
		{
			int i;
			for (i = 1; i <= k - 1; i++)
				if (hamilton[i] == hamilton[k])
					break;
			if (i == k)
				if ((k < SIZE * SIZE) || (k == SIZE * SIZE && graf[hamilton[k]][1]))
					return;

		}
	} while (true);
}

void Ham(int k) {
	do {
		NextValue(k);
		if (hamilton[k] == 0)
			return;
		if (k == SIZE * SIZE)
		{
			hamilton[SIZE * SIZE + 1] = hamilton[1];
			ok = false;
		}
		else
			Ham(k + 1);
	} while (ok);
}
void generateHamilton()
{
	genGraf();
	hamilton[1] = 1;
	Ham(2);
	int move = 0;
	for (int i = 1; i <= SIZE * SIZE; i++)
	{
		int h = hamilton[i] - hamilton[i + 1];
		switch (h)
		{
		case -1:
			movelist[move] = 1;
			break;
		case 1:
			movelist[move] = 3;
			break;
		case -SIZE:
			movelist[move] = 2;
			break;
		case SIZE:
			movelist[move] = 4;
			break;
		default:
			break;
		}
		move++;
		if (hamilton[i] == (SIZE * (SIZE / 2 - 1) + SIZE / 2))
			k = i - 1;
	}
}

void mancare()
{
	int auxx = xmar, auxy = ymar;
	bool ok = false;
	lsarpe++;
	if (lsarpe == SIZE * SIZE)
	{
		gameover = true;
		ok = true;
	}
	while (!ok)
	{
		ok = true;
		xmar = rand() % SIZE + 1;
		ymar = rand() % SIZE + 1;
		if (xmar == auxx && ymar == auxy)
		{
			ok = false;
			break;
		}
		if (xmar == xcap && ymar == ycap)
		{
			ok = false;
			break;
		}
		for (int i = 0; i <= lsarpe; i++)
		{
			if (xmar == xcoada[i] && ymar == ycoada[i])
			{
				ok = false;
				break;
			}
		}
	}
	
}



void failcheck()
{
	if (xcap == 0 || xcap == SIZE + 1 || ycap == 0 || ycap == SIZE + 1)
		gameover = true;
	else
	{
		for (int i = 2; i <= lsarpe; i++)
			if (xcap == xcoada[i] && ycap == ycoada[i])
			{
				gameover = true;
				break;
			}
	}
}


void show(sf::RenderWindow& window)
{
	window.clear();
	for (int i = 1; i <= SIZE; i++)
	{
		for (int j = 1; j <= SIZE; j++)
		{
			if (i == xmar && j == ymar)
			{
				sf::RectangleShape mar;
				mar.setSize(sf::Vector2f(30, 30));
				mar.setPosition(325 + (i - 1) * 30, 325 + (j - 1) * 30);
				mar.setFillColor(sf::Color(220, 20, 60));
				window.draw(mar);
			}
			else
			{
				bool a = false;
				for (int l = 1; l <= lsarpe; l++)
				{
					if (i == xcoada[l] && j == ycoada[l])
					{
						sf::RectangleShape snake;
						snake.setSize(sf::Vector2f(30, 30));
						snake.setPosition(325 + (i - 1) * 30, 325 + (j - 1) * 30);
						snake.setFillColor(sf::Color(0, 255, 0));
						window.draw(snake);
						a = true;
					}

				}
				if (!a)
				{
					sf::RectangleShape space;
					space.setSize(sf::Vector2f(30, 30));
					space.setPosition(325 + (i - 1) * 30, 325 + (j - 1) * 30);
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
void movechange()
{
	switch (movelist[k])
	{
	case 1:
		xmove = 0;
		ymove = 1;
		break;
	case 2:
		xmove = 1;
		ymove = 0;
		break;
	case 3:
		xmove = 0;
		ymove = -1;
		break;
	case 4:
		xmove = -1;
		ymove = 0;
		break;
	}
	k++;
	k = k % (SIZE * SIZE);
}

void miscare()
{
	movechange();
	xcap += xmove;
	ycap += ymove;
	if (xcap == xmar && ycap == ymar)
		mancare();
	for (int i = lsarpe; i > 1; i--)
	{
		xcoada[i] = xcoada[i - 1];
		ycoada[i] = ycoada[i - 1];
	}
	xcoada[1] = xcap;
	ycoada[1] = ycap;
	failcheck();
}



int runGame(sf::RenderWindow &window)
{
	valoare();
	window.create(sf::VideoMode(838, 838), "SNAK", sf::Style::Close);
	window.clear();
	window.display();
	srand(time(NULL));
	xmar = rand() % SIZE + 1;
	ymar = rand() % SIZE + 1;
	while (xmar == xcap && ymar == ycap)
	{
		xmar = rand() % SIZE + 1;
		ymar = rand() % SIZE + 1;
	}
	generateHamilton();
	xcoada[1] = xcap;
	ycoada[1] = ycap;
	show(window);
	while (!gameover)
	{
		delta++;
		sf::Event close;
		if (window.pollEvent(close))
		{
			if (close.type == sf::Event::Closed)
			{
				window.close();
				return 0;
			}
		}

		if (delta > 120000)
		{
			miscare();
			show(window);
			delta = 0;
		}
	}
	main();
	return 42;
}