#include "board.hpp"

Board::Board(const int _height, const int _width)
    : height{_height}, width{_width}
{
    // initializing board window
    board_window = newwin(height+2, width+2, 0, 0);
    keypad(board_window, true);

    // initializng board
    board.reserve(height);
    for (int y = 0 ; y < height ; y++)
    {
        std::vector<int> temp(width,0);

        for (int x = 0 ; x < width ; x++)
            temp.at(x) = Board::rand();
        
        board.push_back(temp);
    }

    Point ppos(Board::rand(width-1, 0), Board::rand(height-1, 0));
    // player.set_position(Point(Board::rand(0, width), Board::rand(0, height)) );
    at(ppos) = 0;
}

void Board::draw()
{
    box(board_window, 0 , 0);

    for (int y = 0 ; y < height ; y++)
        for (int x = 0 ; x < width ; x++)
            print(x, y);

    wrefresh(board_window);
}

void Board::print(const int x, const int y)
{
    wmove(board_window, y+1, x+1);
    int sym = at(x,y);

    if (sym == 0)
    {
        wprintw(board_window, "@");
    }
    else if (sym < 0)
        wprintw(board_window, " ");
    else if (sym > 0 && sym < 10)
    {
        wprintw(board_window, "%d", sym);
    }
}