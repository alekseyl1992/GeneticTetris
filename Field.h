#pragma once
#include "Figure.h"

namespace Tetris
{

	class Field
	{
	public:
		static constexpr int fieldWidth = 8;
		static constexpr int fieldHeight = 16;

	private:
		#define each(i, j) for(int i=0; i<fieldWidth; ++i) for(int j=0; j<fieldHeight; ++j)

		bool field[fieldWidth][fieldHeight];
        int scores = 0;
        int stepsCount = 0;

		Figure figure;


		bool tryStep();
		void freezeFigure();
		bool validateFigurePos(); // test for any collisions

		void eraseLines();
		void moveAboveLinesLower(int fromLine);

	public:
		Field();
		~Field();

		bool update();

		bool at(int i, int j) const;

		// move the figure if that's possible
		void moveLeft();
		void moveRight();
		void rotate();

		const Figure& getFigure() const;

		int getScores() const;
        int getStepsCount() const;
	};

}
