
#include "pch.h"
#include <iostream>
#include "../headers/globalSearchAlgorithm.h"
#include<math.h>


void Run(GSAlgorithm &gsa);
double Sin(double x);



int main()
{
    GSAlgorithm example(Sin, 0.0 , 12.28, 5.0, 0.01); 
    Run(example);
}

void Run(GSAlgorithm &gsa)
{
    for (int i = 1; i < 200; i++)
    {
        bool end = gsa.Step();
        auto mp = gsa.GetCurrentMinimum();
        auto lp = gsa.GetLastPoint();
        std::cout << "Step: " << i << "  Min: x = \t" << mp.first << "\ty = \t" << mp.second << "\t  Current: x = \t" << lp.first << "\ty = \t" << lp.second << " \t" << end << std::endl;
    }
}

double Sin(double x)
{
    return std::sin(x);
}

