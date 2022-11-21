#ifndef RANDOM_H_
#define RANDOM_H_

#include <cstdlib>
#include <ctime>
#include <vector>


std::vector<int>& multi_random(std::vector<int>& ran, int max)
{
    srand((unsigned)time(NULL));
    for (int i = max; i > 0; i--)
    {
        ran.push_back(rand() % max);
    }
    return ran;
}


int random(int max)
{
    if (max != 0)
    {
        srand((unsigned)time(NULL));
        int n = rand() % max;
        if (n >= 0 && n < max)
        {
            return n;
        }
    }
    return 0;
}

#endif