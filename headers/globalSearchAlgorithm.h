#pragma once
#include<set>
#include<vector>
#include <algorithm>

struct Trial
{
    double x;
    double y;
    int iteration;

    bool operator < (const Trial& trial)
    {
        if (this->x < trial.x)
        {
            return true;
        }
        return false;
    }
};

class GSAlgorithm
{
    std::vector<Trial> mainSequence;
    double r;
    double eps;
    double(*function)(double);
    double M;
    double m;
    double R;
    Trial minimum;
    unsigned int maxSteps;
    int curPosition;




public:
    GSAlgorithm(double (*_function)(double), double _xLeft, double _xRight, double _r, double _eps)
    {
        if (_xLeft > _xRight) throw "xLeft > xRight";
        function = _function;
        AddTrial(_xLeft);
        AddTrial(_xRight);
        minimum = mainSequence[0].y > mainSequence[1].y ? mainSequence[1] : mainSequence[0];
        r = _r;
        eps = _eps;
    }

    bool Step()
    {
        Calc_m();

        curPosition = GetPosition();
        AddTrial(CalcNextX(curPosition));
        return CheckOver(curPosition);
    }

    void Solve()
    {
        unsigned int step = 0;
        while(!CheckOver(curPosition) && ++step < maxSteps);
    }

    std::vector<Trial> GetmainSequence()
    {
        return mainSequence;
    }

    Trial GetCurrentMinimum()
    {
        return minimum;
    }

    Trial GetResult()
    {
        return minimum;
    }

    Trial GetLastTrial()
    {
        return mainSequence[curPosition];
    }

    void SetMaxSteps(unsigned int steps)
    {
        maxSteps = steps;
    }



private:
    void AddTrial(double x)
    {
        Trial curTrial = {x, function(x), mainSequence.size() + 1};
        auto IT = mainSequence.begin();
        for (; IT != mainSequence.end(); IT++)
        {
            if (curTrial.x < IT->x)
                break;
        }
        if (curTrial.y < minimum.y) minimum = curTrial;
        mainSequence.insert(IT, curTrial);
    }

    void Calc_m()
    {
        M = 0.0;
    
        for(int i = 1; i < mainSequence.size(); i++)
        {
            double curM = CalcM(mainSequence[i], mainSequence[i - 1]);
            if (M < curM) M = curM;
        }
    
        m = 1.0;
    
        if (M) m = r * M;
    }

    int GetPosition()
    {
        R = Calc_curR(mainSequence[1], mainSequence[0]);
        int position = 1;
        for (int i = 2; i < mainSequence.size(); i++)
        {
            double curR = Calc_curR(mainSequence[i], mainSequence[i - 1]);
            if (R < curR)
            {
                R = curR;
                position = i;
            }
        }

        return position;

    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    inline double CalcM(Trial pi, Trial pj)
    {
        return abs((pi.y - pj.y) / (pi.x - pj.x));
    }

    inline double Calc_curR(Trial pi, Trial pj)
    {
        return m * (pi.x - pj.x) +
            ((pi.y - pj.y) * (pi.y - pj.y)) / (m * (pi.x - pj.x)) -
            2 * (pi.y + pj.y);
    }

    inline double CalcNextX(int position)
    {
        return (mainSequence[position].x + mainSequence[position - 1].x) / 2 - (mainSequence[position].y - mainSequence[position - 1].y) / (2 * m);
    }

    inline bool CheckOver(int position)
    {
        return mainSequence[position].x - mainSequence[position - 1].x <= eps;
    }

};