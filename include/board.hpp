#ifndef __BOARD_H__
#define __BOARD_H__

#include <ncurses.h>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "player.hpp"

/// Class handling colors in kindof easy way
class Colorizer
{
public:
    Colorizer();

    void set_window(WINDOW * win) {window = win;}

    /// Sets color in @p window
    void set_color(int color) const;

    /// Resets last added color in @p window
    void undo_color() const {wattroff(window, COLOR_PAIR(last));}

    enum colors{red=1, green, yellow, blue, magenta, cyan, bw=10};

private:
    /// Keeps index of last used color
    mutable int last;

    /// @param window window to work in
    WINDOW * window;

};


class Board
{
public:
    Board(const int _height, const int _width);

    /// Draws board
    void draw();

    /// Gets input from player and acts accordingly
    void move();

    // debug purpose
    void wait() const { wgetch(board_window); }
private:
    /// Board window
    WINDOW *board_window;

    /// Board
    std::vector< std::vector<int> > board;
    const int height;
    const int width;

    /// String containing all possible moves
    const std::string moves{"qweasdzc"};
    /// String containing all possible options to call during game
    const std::string options{"lhb?"};

    /// String containing all currently possible moves
    std::string possible_moves;

    /// Indicates if highlight is on, default is true
    bool should_highlight;

    /// Current player
    Player player;

    /// For colors
    Colorizer colorizer;

    /// @return reference to element on board with coordinates held by @p p
    int & at(const Point p) {return board.at(p.y).at(p.x);}
    int & at(const int x, const int y) { return at(Point(x,y));}
    int at(const Point p) const {return board.at(p.y).at(p.x);}
    int at(const int x, const int y) const { return at(Point(x,y));}

    /// Prints symbol from board in proper way
    /// @param bg If true point is printed as highlighted
    void print(const int x, const int y, bool bg = false) const;
    void print(const Point p, bool bg = false) const {print(p.x, p.y, bg);}

    /// Finds possible moves and saves them to possible_moves
    void check_moves();

    /// Highlights possible moves
    void highlight() const;

    /// @returns true if Point @p p is in range and not eaten
    bool valid(const Point p);

    /// Moves player in @p direction
    void player_move(const char direction);

    /// Makes vector that moves point in @p direction
    static Point make_vector(const char direction);

    /// @returns random int from @p min : @p max , default is 1:9
    static int rand(const int max = 9, const int min = 1) {return ::rand()%(max-min) + min;}

    /// @returns true if @p needle is in @p haystack
    static bool contains(const std::string haystack, const char needle); 
};

/// ncurses wmove but handles Point class
int wmove(WINDOW * win, Point xy);

#endif