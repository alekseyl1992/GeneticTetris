#pragma once
#include "Genetic.h"
#include "IGame.h"
#include "Field.h"

namespace Tetris
{
	class GeneticGame : public IGame
	{
	private:
		Genetic& genetic;

		Field field;
		bool speedUp;
		bool gameOver;

		bool input();
		void render();

	public:
		GeneticGame(Genetic& genetic);
		~GeneticGame();

		int begin();
	};
}