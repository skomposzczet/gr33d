#include <iostream>
#include <ctime>
#include <ncurses.h>
#include <cstring>

#include "board.hpp"

int main(int argc, char *argv[])
{
    if (!term_test())
    {
        std::cout << "At least 22 x 80 terminal required" << std::endl;
        return 1;
    }

    srand(static_cast<unsigned>(time(NULL)));
    std::string name{""};
    bool hl = true;

    if (argc > 1)
    {
        for (int i = 1 ; i < argc ; i++)
        {
            char * temp = argv[i];
            int len = strlen(temp);

            if (strncmp(temp, "--name", len) == 0)
            {
                if (i+1 < argc)
                    name = argv[++i];
                else
                {
                    std::cout << "Invalid name";
                    return 1;
                }
            }
            else if (strncmp(temp, "--highlight=false", len) == 0)
                hl = false;
            else if (strncmp(temp, "help", len) == 0)
            {
                help();
                return 0;
            }
            else if (strncmp(temp, "-s", len) == 0)
            {
                scoreboard();
                return 0;
            }
        }
    }

    if (name.empty())
    {
        std::cout << "What's your name? ";
        std::cin >> name;
    }

    ncwrap nc;
    bool play = true;

    Board board(name, hl);
    while(play)
    {
        board.draw();
        play = board.move();
    }
    board.wait();
}