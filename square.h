#pragma once
#ifndef SQUARE_H
#define SQUARE_H

#include "stdafx.h"

class Square
{
public:
    char zero_zero;
    char zero_one;
    char zero_two;
    char one_zero;
    char one_two;
    char two_zero;
    char two_one;
    char two_two;

    Square(int zz, int zo, int zt, int oz, int ot, int tz, int to, int tt);
};

#endif // SQUARE_H
