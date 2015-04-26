//
// Created by igor on 26/04/15.
//

#ifndef TETRIS_DEPS_H
#define TETRIS_DEPS_H

#ifndef STMT_BEGIN
	#define STMT_BEGIN do
#endif

#ifndef STMT_END
	#define STMT_END while(false)
#endif

#if defined(__linux) || defined(__linux__) || defined(linux)
    #include "port.h"
	#include <stdio.h>

	#ifndef CLEAR_CONSOLE
		#define CLEAR_CONSOLE() STMT_BEGIN {  \
			printf("\033[2J\033[1;1H");       \
		} STMT_END
	#endif

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	#include <Windows.h>
	#include <conio.h>

	#ifndef CLEAR_CONSOLE
		#define CLEAR_CONSOLE() STMT_BEGIN {  \
			system("cls");                    \
		} STMT_END
	#endif
#endif

#endif //TETRIS_DEPS_H
