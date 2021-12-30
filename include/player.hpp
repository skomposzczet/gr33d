#ifndef __PLAYER__H__
#define __PLAYER__H__

#include <string>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <ncurses.h>

#include "header.hpp"

#define WIDTH (34)

class Point
{
friend class Player;
friend class Board;

public:
    explicit Point(const int _x = 0, const int _y = 0) : x{_x}, y{_y} {}

    Point operator+(const Point sec) const
    { 
        return Point(x+sec.x, y+sec.y); 
    }

    bool operator==(const Point comp) const
    {
        return (x==comp.x && y==comp.y);
    } 

    Point & move(int direction)
    {
        switch(direction)
        {
            case up:
                return mup();
            case down:
                return mdown();
            case left:
                return mleft();
            case right:
                return mright();
            default:
                return *this;
        }
    }

    int getx() const {return x;}
    int gety() const {return y;}

    enum dir{up, down, right, left};
private:
    int x;
    int y;

    Point & mup()
    {
        y--;
        return *this;
    }

    Point & mdown()
    {
        y++;
        return *this;
    }

    Point & mright()
    {
        x++;
        return *this;
    }

    Point & mleft()
    {
        x--;
        return *this;
    }
};

class Player
{
public:
    Player(const std::string _name);

    /// Sets new players position
    void set_position(const Point new_position) {position = new_position;}
    void set_position(const int x, const int y) {set_position(Point(x,y));}

    /// Adds @p pts to players score
    void add_score(const int pts) {score += pts; print_comm(mean_message(valid));}

    /// @returns players x coord
    int x() const {return position.getx();}

    /// @returns players y coord
    int y() const {return position.gety();}

    /// @returns point with players coords
    Point pos() const {return position;}

    //
    void end();

    /// Insults user after wrong move
    void wrong_move() const {print_comm(mean_message(invalid));}

private:
    /// Players current coords
    Point position;

    /// Players name
    std::string name;

    /// Players current score
    int score;

    /// Window displaying current players data and stuff
    WINDOW * comm_window;

    /// Window displaying current scoreboard
    WINDOW * scoreboard;

    /// Best total scores so far
    std::vector< std::pair<std::string, int> > top_scores;

    /// Users gr33d home directory
    const std::string GR33D{getenv("HOME") + std::string{"/.gr33d"}};
    /// Usernames history file
    const std::string NAMELIST{"/name_list.dat"};
    /// Best score file
    const std::string SCORESFILE{"/best_scores.dat"};

    /// Mean messages for valid moves
    static const std::vector<std::string> mean_val;
    /// Mean messages for invalid moves
    static const std::vector<std::string> mean_inv;
    /// Message types recognized by mean_message()
    /// @see mean_message()
    enum mess_type{invalid, valid};

    /// Prints comm window with @p message as message
    void print_comm(const std::string message) const;

    /// Prints scoreboard
    void print_scoreboard() const;

    ///@returns true if players username is used for the first time
    bool first_time() const;

    /// @returns mean message 
    /// @param type if true returns message for valid move, false for invalid move
    static std::string mean_message(const int type);

};

#endif