#include "Figure.h"
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <vector>
#include "genetic/util.h"

namespace Tetris
{
	Figure::Figure(int fieldWidth)
		: fieldWidth(fieldWidth)
	{
		srand(time(0));
    }

	void Figure::generate()
    {
        std::vector<int> figuresOrder = {0, 1, 2, 3, 4};
        static int id = 0;

        int curId = id++ % figuresOrder.size();
        //int curId = randAB(0, 5);

		for (int i = 0; i < figureSize; ++i)
			for (int j = 0; j < figureSize; ++j)
                matrix[i][j] = figures[curId][i][j];

		dx = fieldWidth/2 - figureSize/2;
		dy = -figureSize+1; //off screen by 1 step
	}

	void Figure::rotate()
	{
		bool rotated[figureSize][figureSize] = {0};

		for (int i = 0; i < figureSize; ++i)
			for (int j = 0; j < figureSize; ++j)
				rotated[i][j] = matrix[figureSize - j - 1][i];

		memcpy(matrix, rotated, figureSize*figureSize);
	}

	void Figure::rotateBack()
	{
		bool rotated[figureSize][figureSize] = {0};

		for (int i = 0; i < figureSize; ++i)
			for (int j = 0; j < figureSize; ++j)
				rotated[i][j] = matrix[j][figureSize - i - 1];

		memcpy(matrix, rotated, figureSize*figureSize);
	}

	bool Figure::collidesWith(int fi, int fj) const
	{
		if(dy == -figureSize) // are we out of screen?
			return false; 

		for (int i = 0; i < figureSize; ++i)
			for (int j = 0; j < figureSize; ++j)
				if(matrix[i][j] == 1 && i+dx == fi && j+dy == fj)
					return true;

		return false;
	}

	bool Figure::atInitialPos() const
	{
		return dy == -figureSize+1;
	}

    bool Figure::at(int i, int j) const {
		return matrix[i][j];
	}
}


