#ifndef __HEAD_H__
#define __HEAD_H__

/// @returns random int from @p min : @p max , default is 1:9
int random(const int max, const int min) 
{
    return rand()%(max-min) + min;
}


#endif