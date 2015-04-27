#include "GeneticGame.h"

#include <iostream>
#include <thread>
#include <chrono>

#include "lib/deps.h"

using namespace std;

namespace Tetris
{
    GeneticGame::GeneticGame(Genetic& genetic)
        : speedUp(false), gameOver(false),
          genetic(genetic)
	{

	}

	GeneticGame::~GeneticGame()
	{

	}

	int GeneticGame::begin()
	{
        time_t _time = GetTickCount();

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

    int GeneticGame::getStepsCount() const
    {
        return field.getStepsCount();
    }

	bool GeneticGame::input()
	{
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        Genetic::Button button = genetic.activate(field);

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
        emit fieldChanged(field);

//        for(int j = 0; j < Field::fieldHeight; ++j) {
//            for(int i = 0; i < Field::fieldWidth; ++i) {
//                auto item = tableModel->item(j, i);

//                if(field.at(i, j))
//                    item->setBackground(blockBrush);
//                else
//                    item->setBackground(emptyBrush);

//                //emit tableModel->itemChanged(item);
//            }
//        }

//		if(gameOver)
//		{
//			cout << endl;
//			cout << "GeneticGame Over!" << endl;
//			cout << "Scores: " << field.getScores() << endl;
//        }
	}
}
