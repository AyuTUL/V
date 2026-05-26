// Lab 5: Write C program to simulate single server queuing system
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

float normalLike(float mean, float sd)
{
    float sum = 0.0f;
    for (int i = 1; i <= 12; ++i)
    {
        float x = rand() / 32768.0f;
        sum += x;
    }
    return mean + sd * (sum - 6.0f);
}

int main()
{
    int i, j, run;
    float iat, st, awt, pcu, wt = 0, it = 0;
    float mean, sd, mue, sigma;
    float sb = 0.0, se = 0.0, cit = 0, cat = 0, cwt = 0;

    cout << "Enter number of runs : ";
    if (!(cin >> run))
        return 1;
    cout << "Enter mean and sd for inter-arrival time : ";
    if (!(cin >> mean >> sd))
        return 1;
    cout << "Enter mean and sd for service time : ";
    if (!(cin >> mue >> sigma))
        return 1;

    cout << endl
         << "---Single Server Queuing System---" << endl;

    const char *line = "+--------+--------+--------+--------+--------+--------+--------+";
    cout << line << endl;
    cout << "|" << setw(8) << "IAT"
         << "|" << setw(8) << "CAT"
         << "|" << setw(8) << "SB"
         << "|" << setw(8) << "ST"
         << "|" << setw(8) << "SE"
         << "|" << setw(8) << "CWT"
         << "|" << setw(8) << "CIT" << "|" << endl;
    cout << line;

    cout << fixed << setprecision(2);
    for (j = 1; j <= run; ++j)
    {
        iat = normalLike(mean, sd);
        cat += iat;
        if (cat <= se)
        {
            sb = se;
            wt = se - cat;
            cwt += wt;
        }
        else
        {
            sb = cat;
            it = sb - se;
            cit += it;
        }
        st = normalLike(mue, sigma);
        se = sb + st;
        cout << endl
             << "|" << setw(8) << iat
             << "|" << setw(8) << cat
             << "|" << setw(8) << sb
             << "|" << setw(8) << st
             << "|" << setw(8) << se
             << "|" << setw(8) << cwt
             << "|" << setw(8) << cit << "|";
    }
    awt = cwt / run;
    pcu = ((cat - cit) * 100.0f) / cat;

    cout << endl
         << line << endl;
    cout << "Average waiting time =  " << awt << endl
         << "Percentage capacity utilization =  " << pcu;
    return 0;
}