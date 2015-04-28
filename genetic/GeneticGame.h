#pragma once
#include <QObject>
#include <QStandardItemModel>
#include "Genetic.h"
#include "IGame.h"
#include "Field.h"

namespace Tetris
{
    class GeneticGame : public QObject, public IGame
	{
        Q_OBJECT

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
        int getStepsCount() const;
        const Field& getField() const;

    signals:
        void fieldChanged(const Field& field);
	};
}
