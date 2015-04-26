#pragma once
#include "Field.h"
#include "IGame.h"

namespace Tetris
{
	class ConsoleGame : public IGame
	{
	private:
		Field field;
		bool speedUp;
		bool gameOver;

		bool input();
		void render();

	public:
		ConsoleGame();
		~ConsoleGame();

		int begin();
	};
}