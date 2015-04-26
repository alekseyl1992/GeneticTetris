#include "ConsoleGame.h"

#include "arduino_utils.h"

namespace Tetris
{
	ConsoleGame::ConsoleGame()
		: speedUp(false), gameOver(false)
	{
		m.init();
		m.setIntensity(15); // max density
	}

	ConsoleGame::~ConsoleGame()
	{

	}

	int ConsoleGame::begin()
	{
		static time_t _time = GetTickCount();

		while(input())
		{	
			time_t _delay = 1/(field.getScores()/7+1); // speed up every 7 scores
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
		if(readDebounced(leftButton))
			field.moveLeft();
		else if(readDebounced(rightButton))
			field.moveRight();
		else if(readDebounced(speedUpButton))
		{
			speedUp = true;
			return true; //avoid speedUp disabling below
		}
		else if(readDebounced(rotateButton))
			field.rotate();

		render();

		speedUp = false; // disable speedUp
		return true;
	}

	void ConsoleGame::render()
	{
		if(!gameOver)
		{
			for(int j=0; j<fieldHeight; ++j)		
				for(int i=0; i<fieldWidth; ++i)
					m.setDot(j, i, field.at(i, j));
		}	
		else
		{
			//binary output ;)
			int scores = field.getScores();
			m.setColumn(0, highByte(scores));
			m.setColumn(1, highByte(scores));
		}
	}
}