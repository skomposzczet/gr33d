#include "board.hpp"

Board::Board(const std::string name, const bool hl, const int _height, const int _width)
    : height{_height}, width{_width}, should_highlight{hl}, player{name}
{
    // initializing board window
    board_window = newwin(height+2, width+2, 0, 0);
    keypad(board_window, true);

    colorizer.set_window(board_window);

    // initializng board
    board.reserve(height);
    for (int y = 0 ; y < height ; y++)
    {
        std::vector<int> temp(width,0);

        for (int x = 0 ; x < width ; x++)
            temp.at(x) = random(9, 1);
        
        board.push_back(temp);
    }

    player.set_position(Point(random(width-1, 0), random(height-1, 0)) );
    at(player.pos()) = 0;
}

void Board::draw()
{
    wclear(board_window);
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
    possible_moves = "";
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
        wprintw(board_window, "@");
    else if (sym < 0)
        wprintw(board_window, " ");
    else if (sym > 0 && sym < 10)
    {
        if (bg)
            colorizer.set_color(10);
        else
            colorizer.set_color(sym);
        wprintw(board_window, "%d", sym);
    }

    colorizer.undo_color();
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

bool Board::move()
{
    if (possible_moves.empty())
    {
        end();
        return false;
    }
    std::string available{possible_moves+options};
    int c;
    while (1)
    {
        c = wgetch(board_window);
        if (c == KEY_UP)
            c = 'w';
        else if (c == KEY_DOWN)
            c = 's';
        else if (c == KEY_LEFT)
            c = 'a';
        else if (c == KEY_RIGHT)
            c = 'd';
        
        if (!contains(available, c))
        {
            player.wrong_move();
            wmove(board_window, player.pos()+Point(1,1));
            continue;
        }

        if (c == 'h')
        {
            should_highlight = (should_highlight ? false : true);
            draw();
            continue;
        }
        else if (c == '?')
        {
            player.message("too dumb to figure out yourself?");
            help();
            player.message("enlightened?");
            draw();
            continue;
        }
        else if (c == 'l')
        {
            if (player.confirm())
            {
                end();
                return false;
            }
            
            player.message("so close...");
        }

        player_move(c);
        break;
    }

    return true;
}

void Board::player_move(const char direction)
{
    Point vector{make_vector(direction)};
    Point walker{player.pos()};
    int length = at(walker+vector);

    for (int i = 0 ; i < length ; i++)
    {
        at(walker) = -1;
        walker = walker + vector;
    }

    at(walker) = 0;
    player.set_position(walker);
    player.add_score(length);
}

void Board::end()
{
    player.end(); 
    wmove(board_window, player.pos()+Point(1,1));
}

void Board::help() const
{
    WINDOW * help_window = newwin(14, 62, 5, 10);
    std::vector<std::string> help_text{"                gr33d - greed but offensive","","Welcome to gr33d, game inspired by unix game greed.  Goal of", "the game is to clear as  much of  screen as  possible.  Your", "position is marked with '@'. You can  move using  'wsadqezc'", "(you can also use arrows).  You move eating N squares, where", "N is first number  in direction you choose to go.  You can't", "move if move will get you out of board or will cross already", "blank  space.  You  can  press  'h'  to  toogle highlighting", "possible ways or 'l' to quit.  Good luck and have fun!  Psst", "watch out for game host, he can be mean sometimes!"};

    box(help_window, 0, 0);
    for (unsigned i = 0 ; i < help_text.size() ; i++)
        mvwprintw(help_window, 1+i, 1, "%s", help_text.at(i).data());
    wrefresh(help_window);

    wait();

    wclear(help_window);
    delwin(help_window);
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

void Colorizer::set_color(int color) const
{
    if (color == bw)
        wattron(window, COLOR_PAIR(color));
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
