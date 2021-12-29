#include "board.hpp"

Board::Board(const int _height, const int _width)
    : height{_height}, width{_width}, should_highlight{true}
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

    check_moves();

    if(should_highlight)
        highlight();

    wmove(board_window, player.y()+1, player.x()+1);

    wrefresh(board_window);
}

void Board::check_moves()
{
    int deltax = 0;
    int deltay = 0;

    for (auto direction : moves)
    {
        Point vector{make_vector(direction)};

        // checking first point 
        Point walker{player.pos() + vector};
        if (!valid(walker))
            continue;

        // checking whole way
        int length = at(walker);
        possible_moves.push_back(direction);
        for (int i = 1 ; i < length ; i++)
        {
            walker = walker + vector;
            if (!valid(walker))
            {
                possible_moves.pop_back();
                break;
            }
        }
    }
}

void Board::highlight() const
{
    for (auto direction : possible_moves)
    {
        Point vector{make_vector(direction)};
        Point walker{player.pos()};
        int length = at(walker + vector);

        for (int i = 0 ; i < length ; i++)
        {
            walker = walker + vector;
            print(walker, true);
        }
    }
}

void Board::print(const int x, const int y, bool bg) const
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
        if (bg)
            colorizer.set_color(board_window, 0);
        else
            colorizer.set_color(board_window, sym);
        wprintw(board_window, "%d", sym);
    }

    colorizer.undo_color(board_window);
}

bool Board::valid(const Point p)
{
    // checking x axis
    if (p.getx() < 0 || p.getx() >= width)
        return false;

    // checking y axis
    if (p.gety() < 0 || p.gety() >= height)
        return false;

    // checking if point is eaten
    if (at(p) < 0)
        return false;

    return true;
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

void Colorizer::set_color(WINDOW * window, int color) const
{
    if (color == bw)
        wattron(window, COLOR_PAIR(10));
    else
        wattron(window, COLOR_PAIR(color = color%cyan + 1));

    last = color;
}

int wmove(WINDOW * win, Point xy)
{
    return wmove(win, xy.gety(), xy.getx());
}

bool Board::contains(const std::string haystack, const char needle)
{
    for (auto & c : haystack)
        if (c == needle)
            return true;

    return false;
}

Point Board::make_vector(const char direction)
{
    int deltax = 0;
    int deltay = 0;

    if (contains("qwe", direction))
        deltay = -1;
    else if (contains("zsc", direction))
        deltay = 1;

    if (contains("qaz", direction))
        deltax = -1;
    else if (contains("edc", direction))
        deltax = 1;

    return Point(deltax, deltay);
}
