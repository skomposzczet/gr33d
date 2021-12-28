#include <iostream>
#include <ncurses.h>

#include "board.hpp"


class ncwrap
{
public:
    ncwrap(bool ec = true, bool cb = true) { 
        initscr(); 
        if (ec) noecho(); 
        if (cb) cbreak();
    }

    ~ncwrap() { endwin(); }
    void ref() { ::refresh(); }
};

int main()
{
    ncwrap nc;

    
}