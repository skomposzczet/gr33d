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

    // Point ppos;
    player.set_position(Point(Board::rand(width-1, 0), Board::rand(height-1, 0)) );
    at(player.pos()) = 0;
}

void Board::draw()
{
    box(board_window, 0 , 0);

    for (int y = 0 ; y < height ; y++)
        for (int x = 0 ; x < width ; x++)
            print(x, y);

    wmove(board_window, player.pos());
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
        colorizer.set_color(board_window, sym);
        wprintw(board_window, "%d", sym);
    }

    colorizer.undo_color(board_window);
}

Colorizer::Colorizer()
    : last{11}
{
    start_color(); 

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);

    init_pair(10, COLOR_BLACK, COLOR_WHITE);
}

void Colorizer::set_color(WINDOW * window, int color)
{
    if (color == bw)
        wattron(window, COLOR_PAIR(10));
    else
        wattron(window, COLOR_PAIR(color = color%cyan + 1));

    last = color;
}

int wmove(WINDOW * win, Point xy)
{
    wmove(win, xy.gety(), xy.getx());
}