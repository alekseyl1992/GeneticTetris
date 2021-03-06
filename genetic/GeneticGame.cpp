#include "GeneticGame.h"

#include <iostream>
#include <thread>
#include <chrono>

#include "lib/deps.h"

using namespace std;

namespace Tetris
{
    GeneticGame::GeneticGame(Genetic& genetic)
        : genetic(genetic),
          speedUp(false), gameOver(false)
	{

	}

	GeneticGame::~GeneticGame()
	{

	}

    int GeneticGame::begin()
    {
        while(!gameOver) {
            for (int i = 0; i < 5; ++i)
                input();

            gameOver = !field.update();

            if (field.getScores() != 0 && genetic.getCurrentChromosomeId() == 0)
                render();
        }

        return field.getScores();
    }

    int GeneticGame::getStepsCount() const
    {
        return field.getStepsCount();
    }

	bool GeneticGame::input()
    {
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
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

		speedUp = false; // disable speedUp

		return true;
	}

	void GeneticGame::render()
	{
        emit fieldChanged(field);
	}

    const Field& GeneticGame::getField() const {
        return field;
    }
}
