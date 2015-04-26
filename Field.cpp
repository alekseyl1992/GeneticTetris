#include "Field.h"
#include <iostream>

namespace Tetris
{
	Field::Field()
		: figure(fieldWidth), scores(0)
	{
		each(i, j)
			field[i][j] = 0;

		figure.generate();
	}

	Field::~Field()
	{

	}

	bool Field::update()
	{
		if(!tryStep())
		{
			if(!figure.atInitialPos())
			{
				freezeFigure();
                eraseLines();


                figure.generate();
			}
			else //unable to move even 1 step into screen
			{
				return false; //game over
			}
		}

		return true;
	}

	bool Field::tryStep()
	{
		figure.dy++;

        bool valid = validateFigurePos();

        std::cout << "Valid: " << valid << std::endl;

        if(!valid)
		{
			figure.dy--; // rollback
			return false;
		}

		return true;
	}

	bool Field::validateFigurePos()
	{
        if(figure.atInitialPos()) // we are above the screen
			return true;

		for(int i=0; i<figureSize; ++i)
			for(int j=0; j<figureSize; ++j)
				if(figure.matrix[i][j] == 1)
					if((j+figure.dy >= 0 && field[i+figure.dx][j+figure.dy] == 1) // collision?
						|| j+figure.dy >= fieldHeight // end of field reached?
						|| i+figure.dx < 0 || i+figure.dx >= fieldWidth) // out off screen to the left or right?
							return false;

		return true;
	}

	void Field::freezeFigure()
	{
        std::cout << "Freezing..." << std::endl;
		for(int i=0; i<figureSize; ++i)
			for(int j=0; j<figureSize; ++j)
				if(j+figure.dy >= 0) // it's possible when part of the figure is not exposed yet
					field[i+figure.dx][j+figure.dy] |= figure.matrix[i][j];

        std::cout << "Freezed" << std::endl;
	}

	bool Field::at(int i, int j) const
	{
		return field[i][j] || figure.collidesWith(i, j);
	}

	void Field::moveLeft()
	{
		if(!figure.atInitialPos())
		{
			figure.dx--;
            std::cout << "dx: " << figure.dx << " ";

            if(!validateFigurePos())
				figure.dx++;
            std::cout << figure.dx << std::endl;
		}				
	}

	void Field::moveRight()
	{
		if(!figure.atInitialPos())
		{
			figure.dx++;

			if(!validateFigurePos())
				figure.dx--;	
		}
	}

	void Field::rotate()
	{
		if(!figure.atInitialPos())
		{
			figure.rotate();

			if(!validateFigurePos())
				figure.rotateBack();
		}
	}

	void Field::eraseLines()
	{
		int clearedLines = 0;

		for(int j=0; j<fieldHeight; ++j)
		{
			bool lineFilled = true;

			for(int i=0; i<fieldWidth; ++i)
				if(!field[i][j])
				{
					lineFilled = false;
					break;
				}

			if(lineFilled)
			{
				// move all above tiles 1 line lower
				moveAboveLinesLower(j);
				clearedLines++;
			}
		}

		scores += clearedLines*3;
	}

	void Field::moveAboveLinesLower(int fromLine)
	{
		// copy from matrix to the next line
		for(int j=fromLine-1; j>0; --j)
			for(int i=0; i<fieldWidth; ++i)
				field[i][j+1] = field[i][j];

		// clear topmost line
		for(int i=0; i<fieldWidth; ++i)
			field[i][0] = 0;
	}

	int Field::getScores() const
	{
		return scores;
	}

	const Figure &Field::getFigure() const {
		return figure;
	}
}
