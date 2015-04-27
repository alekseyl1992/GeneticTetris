#include <genetic/GeneticGame.h>

struct GameResult {
    int scores = 0;
    int stepsCount = 0;

    GameResult(int scores, int stepsCount)
        : scores(scores), stepsCount(stepsCount)
    { }
};

GameResult run(Genetic& genetic);

int main()
{
	Genetic genetic(20);
	genetic.init();

	bool loop = true;
	while(loop) {
        GameResult result = run(genetic);
        genetic.step(result.scores, result.stepsCount);
	}

	return 0;
}

GameResult run(Genetic& genetic) {
	Tetris::GeneticGame game(genetic);
    auto score = game.begin();
    auto gameStepsCount = game.getStepsCount();

    return {score, gameStepsCount};
}
