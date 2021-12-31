#ifndef __HEAD_H__
#define __HEAD_H__

#include <cstdlib>
#include <ncurses.h>
#include <iostream>

/// @returns random int from @p min : @p max , default is 1:9
int random(const int max, const int min);

/// @return true if terminal is at least size @p x X @p y
bool term_test(int x = 119, int y = 24);

/// Prints info about game
void help();

/// Prints scoreboard (no curser)
void scoreboard();

class ncwrap
{
public:
    ncwrap(bool ec = true, bool cb = true) { 
        initscr(); 
        if (ec) noecho(); 
        if (cb) cbreak();
    }

    ~ncwrap() { endwin(); }
    void refresh() { ::refresh(); }
};

#endif