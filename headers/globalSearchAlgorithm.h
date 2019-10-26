#pragma once
#include<map>
#include<vector>
#include <algorithm>

class GSAlgorithm
{
    using Point = std::pair<double, double>;

    std::vector<Point> mainSequence;
    std::vector<Point> stepSequence;
    std::map<int, int> index;
    double r;
    double eps;
    double(*function)(double);
    double M;
    double m;
    double R;
    Point minimum;
    

public:
    GSAlgorithm(double (*_function)(double), double _xLeft, double _xRight, double _r, double _eps)
    {
        function = _function;
        if (_xLeft > _xRight) throw "xLeft > xRight";
        AddPoint(_xLeft);
        AddPoint(_xRight);
        minimum = mainSequence[0].second > mainSequence[1].second ? mainSequence[1] : mainSequence[0];
        r = _r;
        eps = _eps;
    }

    bool Step()
    {
        RefreshStepSequence();
        Calc_m();

        int position = GetPosition();
        AddPoint(Calc_nextX(position));
        if (IsMinimum()) minimum = mainSequence.back();
        return CheckOver(position);
    }

    Point GetCurrentMinimum()
    {
        return minimum;
    }

    Point GetLastPoint()
    {
        return mainSequence.back();
    }



private:
    void AddPoint(double x)
    {
        Point xz = {x, function(x)};
        mainSequence.push_back(xz);
    }

    void RefreshStepSequence()
    {
        for (int i = stepSequence.size(); i < mainSequence.size(); i++)
        {
            stepSequence.push_back(mainSequence[i]);
        }
        std::sort(stepSequence.begin(), stepSequence.end(),[](auto &left, auto &right){ return left.first < right.first; });
        
    }

    inline double Calc_M(Point pi, Point pj)
    {
        return abs((pi.second - pj.second) / (pi.first - pj.first));
    }

    void Calc_m()
    {
        M = 0.0;

        for (int i = 1; i < stepSequence.size(); i++)
        {
            double curM = Calc_M(stepSequence[i], stepSequence[i - 1]);
            if (M < curM) M = curM;
        }

        m = 1.0;

        if (M) m = r * M;
    }

    inline double Calc_curR(Point pi, Point pj)
    {
        return m * (pi.first - pj.first) + 
        ((pi.second - pj.second) * (pi.second - pj.second)) / (m * (pi.first - pj.first)) -
        2 * (pi.second + pj.second);
    }

    int GetPosition()
    {
        R = Calc_curR(stepSequence[1], stepSequence[0]);
        int position = 1;
        for (int i = 2; i < stepSequence.size(); i++)
        {
            double curR = Calc_curR(stepSequence[i], stepSequence[i - 1]);
            if (R < curR)
            {
                R = curR;
                position = i;
            }
        }

        return position;

    }

    inline double Calc_nextX(int position)
    {
        return (stepSequence[position].first + stepSequence[position - 1].first) / 2 - (stepSequence[position].second - stepSequence[position - 1].second) / (2 * m);
    }

    inline bool CheckOver(int position)
    {
        return stepSequence[position].first - stepSequence[position - 1].first <= eps;
    }

    inline bool IsMinimum()
    {
        return mainSequence.back().second < minimum.second ;
    }
};