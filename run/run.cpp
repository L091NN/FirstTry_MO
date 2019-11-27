
#include "pch.h"
#include <iostream>
#include "../headers/globalSearchAlgorithm.h"
#include<math.h>


void Run(GSAlgorithm &gsa);
double Sin(double x);



int main()
{
    GSAlgorithm example1(Sin, 0.0 , 12.28, 2.0, 0.005);
    auto sett = example1.GetmainSequence();
    Run(example1);
    GSAlgorithm example2(Sin, 0.0, 12.28, 2.0, 0.005);
    example2.Solve();
    auto result = example2.GetResult();


}

void Run(GSAlgorithm &gsa)
{
    for (int i = 1; i < 200; i++)
    {
        bool end = gsa.Step();
        auto mp = gsa.GetCurrentMinimum();
        auto lp = gsa.GetLastTrial();
        std::cout << "Step: " << i << "  Min: x = \t" << mp.x << "\ty = \t" << mp.y << "\t  Current: x = \t" <<lp.x << "\ty = \t" << lp.y << " \t" << end << std::endl;
    }
}

double Sin(double x)
{
    return std::sin(x);
}

double SummSin(double x)
{   
    auto CalcA = [&](int iter) -> double
    {
        
    };
    for (i)
}

