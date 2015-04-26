#include "ConsoleGame.h"

#include <iostream>
#include "lib/deps.h"
using namespace std;

namespace Tetris
{
	ConsoleGame::ConsoleGame()
		: speedUp(false), gameOver(false)
	{

	}

	ConsoleGame::~ConsoleGame()
	{

	}

	int ConsoleGame::begin()
	{
		static time_t _time = GetTickCount();

		while(input())
		{	
			time_t _delay = 1000/(field.getScores()/7+1); // speed up every 7 scores
			if(speedUp)
				_delay /= 100;

			if(GetTickCount() - _time >= _delay)
			{
				if(!field.update()) // game over!
					gameOver = true;

				render();

				_time = GetTickCount();
			}
		}

		return 0;
	}

	bool ConsoleGame::input()
	{
		if(_kbhit())
		{
			char ch = (char) _getch();
			switch(ch)
			{
			case 80: //down arrow
				speedUp = true;
				return true; //avoid speedUp disabling below
				break;

			case 75: //left arrow
				field.moveLeft();
				break;

			case 77: //right arrow
				field.moveRight();
				break;

			case 72: // up arrow
				field.rotate();
				break;

			case 27: // escape
				return false;
				break;

			default:
				speedUp = false; // disable speedUp
				return true; // prevent from redundant redraw
			}

			render();
		}

		speedUp = false; // disable speedUp

		return true;
	}

	void ConsoleGame::render()
	{
		CLEAR_CONSOLE();

		cout << "----------" << endl;

		for(int j=0; j<Field::fieldHeight; ++j)
		{
			cout << '|';

			for(int i=0; i<Field::fieldWidth; ++i)
			{
				if(field.at(i, j))
					cout << "#";
				else
					cout << " ";
			}

			cout << '|' << endl;
		}

		cout << "----------" << endl;

		if(gameOver)
		{
			cout << endl;
			cout << "ConsoleGame Over!" << endl;
			cout << "Scores: " << field.getScores() << endl;
		}
	}
}