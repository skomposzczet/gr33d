#include "player.hpp"

const std::vector<std::string> Player::mean_val{"Great fxxkin move idiot.", "You're real genius.", "Bravo.", "Wow.", "You are doing great. Not.", "Finally.", "Monkey would do better.", "You're a lost cause.", "You really thought it's good idea.", "LMAO", "XDDDDDDDDDD", "You're gonna fxxk it up"};
const std::vector<std::string> Player::mean_inv{"You can't go there idiot.", "Wrong way. Obviously.", "HAHA!", "Really?", "XDDDDDDDDDD"};

Player::Player(const std::string _name)
    : name{_name}, score{0}
{
    std::filesystem::create_directory(GR33D);
    comm_window = newwin(10, WIDTH+2, 0, 83);
    scoreboard = newwin(14, WIDTH+2, 10, 83);

    std::string message = (first_time() ? "new retard on the block" : "this fuxxer again");

    print_comm(message);

    std::ifstream score_file(GR33D + SCORESFILE);
    if (score_file.is_open())
    {
        std::string stemp;
        std::string itemp;

        while(getline(score_file, stemp))
        {
            getline(score_file, itemp);
            top_scores.emplace_back(stemp, std::stoi(itemp));
        }

        score_file.close();
    }
    
    print_scoreboard();
}

void Player::print_comm(const std::string message) const
{
    wclear(comm_window);
    box(comm_window, 0, 0);
    mvwprintw(comm_window, 1, 1, "username:\t%.19s", name.data());
    mvwprintw(comm_window, 3, 1, "score:\t\t%d", score);
    mvwprintw(comm_window, 4, 1, "      \t\t%.2lf%%", 100.0*score/MAXPTS);
    mvwprintw(comm_window, 6, 1, "%.*s", WIDTH, message.data());
    mvwprintw(comm_window, 8, 1, "press '?' for help");
    wrefresh(comm_window);
}

void Player::print_scoreboard() const
{
    wclear(scoreboard);
    box(scoreboard, 0, 0);
    mvwprintw(scoreboard, 1, 1, "       S C O R E B O A R D");
    mvwprintw(scoreboard, 2, 1, "##################################");
    for (unsigned i = 0 ; i < top_scores.size() ; i++)
        mvwprintw(scoreboard, 3+i, 1, "%2d. %17.17s  %4d %5.2lf%%", i+1, top_scores.at(i).first.data(), top_scores.at(i).second, 100.0*top_scores.at(i).second/MAXPTS);
    wrefresh(scoreboard);
}

bool Player::first_time() const
{
    std::ifstream name_list(GR33D + NAMELIST);
    if (name_list.is_open())
    {
        std::string temp_un;

        while(getline(name_list, temp_un))
        {
            if (temp_un == name)
            {
                return false;
                break;
            }
        }

        name_list.close();
    }

    return true;
}

void Player::end()
{
    // save to best scores if fits
    top_scores.emplace_back(name, score);
    std::sort(top_scores.begin(), top_scores.end(), [](auto & p1, auto & p2){return (p1.second > p2.second);});
    if (top_scores.size() > 10)
        top_scores.pop_back();

    std::ofstream scores_file(GR33D + SCORESFILE);

    if (scores_file.is_open())
    {
        for (auto & p : top_scores)
        {   
            scores_file << p.first << std::endl;
            scores_file << p.second << std::endl;
        }  

        scores_file.close();
    }
    
    print_scoreboard();
    print_comm("finally you fxxk off");

    // saving unsername to history
    std::fstream name_list(GR33D + NAMELIST, std::fstream::app);
    if (name_list.is_open())
    {
        name_list << name << std::endl;
        name_list.close();
    }
}

std::string Player::mean_message(const int type)
{
    auto & vec = ( type ? mean_val : mean_inv );
    const int size = vec.size();
    return vec.at(random(size-1, 0));
}

bool Player::confirm(std::string mess)
{
    mess += " y/[n]";
    print_comm(mess);
    wmove(comm_window, 6, mess.size() + 2);
    keypad(comm_window, true);
    int c = wgetch(comm_window);
    keypad(comm_window, false);
    
    return (c == 'y' || c == 'Y');
}