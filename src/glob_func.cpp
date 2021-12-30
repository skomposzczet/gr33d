#include "../include/header.hpp"

int random(const int max, const int min) 
{
    return rand()%(max-min) + min;
}