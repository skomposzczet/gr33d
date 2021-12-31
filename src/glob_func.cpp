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
    std::string h{"\t\t\t\t\tgr33d - greed but offensive\n\nDescription:\n\n\tWelcome to gr33d, game inspired by unix game greed. Goal of the game is to clear as much of screen\n\tas possible. Your position is marked with '@'. You can move using 'wsadqezc' (you can also use \n\tarrows).\n\n\t\t\t\t\t\tq w e   N N N\n\t\t\t\t\t\t \\|/     \\|/\n\t\t\t\t\t\ta-@-d   N-@-N\n\t\t\t\t\t\t /|\\    /|\\\n\t\t\t\t\t\tz s c   N N N\n\n\tYou move eating N squares, where N is first number in direction you choose to go. You can't move if\n\tmove will get you out of board or will cross already blank space. You can press 'h' to toogle\n\thighlighting possible ways or 'l' to quit. Good luck and have fun! Psst watch out for game host, he\n\tcan be mean sometimes!\n\nCommand line options:\n\n\t--name <un>\n\t\t\tsets username to un\n\t--highlight==false\n\t\t\ttoogles highlighting off\n\t-s\n\t\t\tprints top scores\n\thelp\n\t\t\tprints help page\n\t\t\t\nFiles:\n\n\t~/.gr33d/\n\t\tDefault location for gr33d files\n\t\t\nAuthors:\n\n\tskomposzczet (https://github.com/skomposzczet)."};
    std::cout << h << std::endl;
}

void scoreboard()
{
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