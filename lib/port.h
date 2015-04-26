#ifndef PORT_H
#define PORT_H

#include <chrono>
#include <termios.h>
#include <stdio.h>

static struct termios old, new_;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    new_ = old; /* make new settings same as old settings */
    new_.c_lflag &= ~ICANON; /* disable buffered i/o */
    new_.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &new_); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char _getch(void)
{
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
    return getch_(1);
}




// simulation of Windows GetTickCount()
unsigned long long GetTickCount()
{
    using namespace std::chrono;
    return (unsigned long long int) duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

// Clock built upon Windows GetTickCount()
struct TickCountClock
{
    typedef unsigned long long                       rep;
    typedef std::milli                               period;
    typedef std::chrono::duration<rep, period>       duration;
    typedef std::chrono::time_point<TickCountClock>  time_point;
    static const bool is_steady =                    true;

    static time_point now() noexcept
    {
        return time_point(duration(GetTickCount()));
    }
};


/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>
#include <asm-generic/ioctls.h>

int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

#endif //PORT_H
