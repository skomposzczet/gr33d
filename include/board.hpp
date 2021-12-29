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

    /// Sets color in @p window
    void set_color(WINDOW * window, int color);

    /// Resets last added color in @p window
    void undo_color(WINDOW * window) {wattroff(window, COLOR_PAIR(last));}

    enum colors{bw, red, green, yellow, blue, magenta, cyan};

private:
    /// Keeps index of last used color
    int last;

};


class Board
{
public:
    Board(const int _height, const int _width);

    /// Draws board
    void draw();

    // debug purpose
    void wait() const { wgetch(board_window); }
private:
    /// Board window
    WINDOW *board_window;

    /// Board
    std::vector< std::vector<int> > board;
    const int height;
    const int width;

    /// Current player
    Player player;

    /// For colors
    Colorizer colorizer;

    /// @return reference to element on board with coordinates held by @p p
    int & at(const Point p) {return board.at(p.y).at(p.x);}
    int & at(const int x, const int y) { return at(Point(x,y));}

    /// Prints symbol from board in proper way
    void print(const int x, const int y);

    /// @returns random int from @p min : @p max , default is 1:9
    static int rand(const int max = 9, const int min = 1) {return ::rand()%(max-min) + min;}
};

/// ncurses wmove but handles Point class
int wmove(WINDOW * win, Point xy);

#endif