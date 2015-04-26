#include <genetic/GeneticGame.h>

int run(Genetic& genetic);

int main()
{
	Genetic genetic(20);
	genetic.init();

	bool loop = true;
	while(loop) {
		int score = run(genetic);
		genetic.step(score);
	}

	return 0;
}

int run(Genetic& genetic) {
	Tetris::GeneticGame game(genetic);
	return game.begin();
}