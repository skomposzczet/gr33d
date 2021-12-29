#include "player.hpp"

Player::Player(const std::string _name)
    : name{_name}, score{0} 
{
    comm_window = newwin(10, WIDTH+2, 0, 83);
    scoreboard = newwin(14, WIDTH+2, 10, 83);

    print_comm("here will be mean message");
    
    box(scoreboard, 0, 0);
    wrefresh(scoreboard);
}

void Player::print_comm(const std::string message) const
{
    box(comm_window, 0, 0);
    mvwprintw(comm_window, 1, 1, "username:\t%.*s", WIDTH, name.data());
    mvwprintw(comm_window, 3, 1, "score:\t\t%d", score);
    mvwprintw(comm_window, 4, 1, "      \t\t%.2lf%%", 100.0*score/1760);
    mvwprintw(comm_window, 6, 1, "%.*s", WIDTH, message.data());
    mvwprintw(comm_window, 8, 1, "press '?' for help");
    wrefresh(comm_window);
}