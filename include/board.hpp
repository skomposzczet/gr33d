#ifndef __BOARD_H__
#define __BOARD_H__

#include <ncurses.h>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "player.hpp"

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

    /// @return reference to element on board with coordinates held by @p p
    int & at(const Point p) {return board.at(p.y).at(p.x);}
    int & at(const int x, const int y) { return at(Point(x,y));}

    void print(const int x, const int y);

    static int rand(const int max = 9, const int min = 1) {return ::rand()%(max-min) + min;}
};

#endif