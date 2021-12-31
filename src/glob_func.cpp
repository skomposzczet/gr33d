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
    // std::cout << "Here will appear scoreboard" << std::endl;
    std::vector< std::pair<std::string, int> > scores;
    std::ifstream score_file(GR33D + SCORESFILE);
    if (score_file.is_open())
    {
        std::string stemp;
        std::string itemp;
        
        while(getline(score_file, stemp))
        {
            getline(score_file, itemp);
            scores.emplace_back(stemp, std::stoi(itemp));
        }

        score_file.close();
    }

    std::cout << "Scoreboard:\n";
    for (unsigned i = 0 ; i < scores.size() ; i++)
        std::cout << i+1 << ". " << scores.at(i).first << " " << scores.at(i).second << 100.0*scores.at(i).second/MAXPTS << std::endl;
}