#ifndef __HEAD_H__
#define __HEAD_H__

#include <cstdlib>
#include <ncurses.h>
#include <iostream>

/// Users gr33d home directory
const std::string GR33D{getenv("HOME") + std::string{"/.gr33d"}};
/// Usernames history file
const std::string NAMELIST{"/name_list.dat"};
/// Best score file
const std::string SCORESFILE{"/best_scores.dat"};

/// @returns random int from @p min : @p max , default is 1:9
int random(const int max, const int min);

/// @return true if terminal is at least size @p x X @p y
bool term_test(int x = 119, int y = 24);

/// Prints info about game
void help();

/// Prints scoreboard (no curser)
void scoreboard();

/// ncurses wrapper
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