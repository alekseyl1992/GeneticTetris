#ifndef TETRIS_IGAME_H
#define TETRIS_IGAME_H

namespace Tetris {
    class IGame {
    public:
        virtual bool input() = 0;
        virtual void render() = 0;
        virtual int begin() = 0;
    };
};

#endif //TETRIS_IGAME_H
