#ifndef __PLAYER__H__
#define __PLAYER__H__

class Point
{
friend class Player;
friend class Board;

public:
    Point(const int _x = 0, const int _y = 0) : x{_x}, y{_y} {}

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
friend class Board;

public:

private:

};

#endif