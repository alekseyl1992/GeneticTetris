#pragma once

namespace Tetris
{
	constexpr int figureSize = 3;
	#define figuresCount 5

	const bool figures[figuresCount][figureSize][figureSize] = 
	{
		{
			{0, 1, 0},
			{0, 1, 0},
			{1, 1, 0}
		},
		{
			{0, 0, 0},
			{0, 1, 0},
			{1, 1, 1}			
		},
		{
			{0, 0, 0},
			{1, 1, 0},
			{0, 1, 1}
		},
		{
			{0, 0, 0},
			{1, 1, 0},
			{1, 1, 0}
		},
		{
			{0, 1, 0},
			{0, 1, 0},
			{0, 1, 0}
		},
	};

	struct Figure
	{
		Figure(int fieldWidth);

		int dx, dy, fieldWidth;
		bool matrix[figureSize][figureSize];
		void generate();
		void rotate(); // +90deg
		void rotateBack(); // -90deg
		bool collidesWith(int fi, int fj) const; // fi, fj - field coordinates
		bool atInitialPos() const;

		const bool at(int i, int j) const;
	};
}

