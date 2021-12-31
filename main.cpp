#include <iostream>
#include <ctime>
#include <ncurses.h>

#include "board.hpp"

int main(int argc, char *argv[])
{
    if (!term_test())
    {
        std::cout << "At least 22 x 80 terminal required" << std::endl;
        return 1;
    }

    srand(static_cast<unsigned>(time(NULL)));
    std::string name;
    // std::cout << "What's your name? ";
    // std::cin >> name;
    name = "titane";
    ncwrap nc;
    bool play = true;

    Board board(name);
    while(play)
    {
        board.draw();
        play = board.move();
    }
    board.wait();
}