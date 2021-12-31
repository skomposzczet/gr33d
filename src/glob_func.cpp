#include "../include/header.hpp"

int random(const int max, const int min) 
{
    return rand()%(max-min) + min;
}

bool term_test(int x, int y)
{
    ncwrap nc;
    return !(getmaxx(stdscr) < x || getmaxy(stdscr) < y);
}

void help()
{
    std::cout << "Here will appear help page." << std::endl;
}

void scoreboard()
{
    std::cout << "Here will appear scoreboard" << std::endl;
}