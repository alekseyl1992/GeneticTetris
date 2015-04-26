#include "GeneticGame.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>
using namespace std;

namespace Tetris
{
	GeneticGame::GeneticGame(Genetic& genetic)
		: speedUp(false), gameOver(false), genetic(genetic)
	{

	}

	GeneticGame::~GeneticGame()
	{

	}

	int GeneticGame::begin()
	{
		static time_t _time = GetTickCount();

		while(input() && !gameOver)
		{	
			time_t _delay = 10/(field.getScores()/7+1); // speed up every 7 scores
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

		return field.getScores();
	}

	bool GeneticGame::input()
	{
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        Genetic::Button button = Genetic::Button::LEFT; //genetic.activate(field);

		switch(button)
		{
		case Genetic::Button::LEFT: //left arrow
			field.moveLeft();
			break;

		case Genetic::Button::RIGHT: //right arrow
			field.moveRight();
			break;

		case Genetic::Button::ROTATE: // up arrow
			field.rotate();
			break;

		case Genetic::Button::NONE:
			speedUp = false; // disable speedUp
			return true; // prevent from redundant redraw
			break;
		}

        render();

		speedUp = false; // disable speedUp

		return true;
	}

	void GeneticGame::render()
	{
		system("cls");

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
			cout << "GeneticGame Over!" << endl;
			cout << "Scores: " << field.getScores() << endl;
		}
	}
}
