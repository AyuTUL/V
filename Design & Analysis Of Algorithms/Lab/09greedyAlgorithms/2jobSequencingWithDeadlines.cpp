// Lab 9.2: WAP to implement job sequencing with deadlines.
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Job
{
    int id, deadline, profit;
};

const int CW = 8;

void border(bool wide)
{
    cout << (wide ? "+------+----------+----------+----------+"
                  : "+------+----------+----------+")
         << endl;
}

void printRow(const Job &j)
{
    cout << "|  " << left << setw(3) << ("J" + to_string(j.id))
         << " |  " << setw(7) << j.deadline
         << " |  " << setw(7) << j.profit << " |" << endl;
    border(false);
}

void scheduleBorder(int maxD)
{
    cout << "+";
    for (int t = 1; t <= maxD; t++)
        cout << string(CW, '-') << "+";
    cout << endl;
}

void scheduleRow(const vector<int> &slot, const vector<Job> &jobs, int maxD)
{
    cout << "|";
    for (int t = 1; t <= maxD; t++)
        cout << left << setw(CW) << (slot[t] != -1 ? "   J" + to_string(jobs[slot[t]].id) : "") << "|";
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter number of jobs : ";
    cin >> n;
    if (n <= 0)
        return cout << "Number of jobs must be greater than 0." << endl, 0;

    vector<Job> jobs(n);
    cout << "Enter deadline and profit for each job :" << endl;
    for (int i = 0; i < n; i++)
    {
        jobs[i].id = i + 1;
        cout << "Job " << jobs[i].id << ": ";
        cin >> jobs[i].deadline >> jobs[i].profit;
        if (jobs[i].deadline <= 0)
            return cout << "Deadline must be greater than 0." << endl, 0;
    }

    sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b)
         { return a.profit > b.profit; });

    int maxD = 0, totalProfit = 0;
    for (int i = 0; i < n; i++)
        maxD = max(maxD, jobs[i].deadline);

    vector<int> slot(maxD + 1, -1);
    for (int i = 0; i < n; i++)
        for (int t = min(maxD, jobs[i].deadline); t >= 1; t--)
            if (slot[t] == -1)
            {
                slot[t] = i;
                totalProfit += jobs[i].profit;
                break;
            }

    cout << endl
         << "---Job Sequencing with Deadlines---" << endl
         << endl
         << "Jobs Sorted by Profit :" << endl;
    border(false);
    cout << "| Job  | Deadline | Profit   |" << endl;
    border(false);
    for (int i = 0; i < n; i++)
        printRow(jobs[i]);

    cout << endl
         << "Job Schedule :" << endl;
    scheduleBorder(maxD);
    scheduleRow(slot, jobs, maxD);
    scheduleBorder(maxD);

    for (int t = 0; t <= maxD; t++)
        cout << left << setw(CW + 1) << t;
    cout << endl
         << endl
         << "Maximum Profit = " << totalProfit;
    return 0;
}