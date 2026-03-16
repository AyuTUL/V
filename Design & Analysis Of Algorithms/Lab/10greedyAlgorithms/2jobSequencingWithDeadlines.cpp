// Lab 10.2: Job Sequencing with Deadlines (Greedy)
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

bool compareByProfit(const Job &a, const Job &b)
{
    return a.profit > b.profit;
}

void border(bool wide)
{
    cout << (wide
                 ? "+------+----------+----------+----------+\n"
                 : "+------+----------+----------+\n");
}

void printRow(const Job &j)
{
    cout << "| " << left << setw(4) << ("J" + to_string(j.id))
         << " | " << setw(8) << j.deadline
         << " | " << setw(8) << j.profit
         << " |" << endl;
    border(false);
}

void printScheduleBorder(int maxDeadline, int cellWidth)
{
    cout << "+";
    for (int t = 1; t <= maxDeadline; t++)
        cout << string(cellWidth, '-') << "+";
    cout << endl;
}

void printScheduleRow(const vector<int> &slot, const vector<Job> &jobs, int maxDeadline, int cellWidth)
{
    cout << "|";
    for (int t = 1; t <= maxDeadline; t++)
        if (slot[t] != -1)
            cout << left << setw(cellWidth) << ("J" + to_string(jobs[slot[t]].id)) << "|";
        else
            cout << left << setw(cellWidth) << "" << "|";
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Number of jobs must be greater than 0." << endl;
        return 0;
    }

    vector<Job> jobs(n);

    cout << "Enter deadline and profit for each job:" << endl;
    for (int i = 0; i < n; i++)
    {
        jobs[i].id = i + 1;
        cout << "Job " << jobs[i].id << ": ";
        cin >> jobs[i].deadline >> jobs[i].profit;

        if (jobs[i].deadline <= 0)
        {
            cout << "Deadline must be greater than 0." << endl;
            return 0;
        }
    }

    sort(jobs.begin(), jobs.end(), compareByProfit);

    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
        maxDeadline = max(maxDeadline, jobs[i].deadline);

    vector<int> slot(maxDeadline + 1, -1);
    int totalProfit = 0;

    for (int i = 0; i < n; i++)
        for (int t = min(maxDeadline, jobs[i].deadline); t >= 1; t--)
            if (slot[t] == -1)
            {
                slot[t] = i;
                totalProfit += jobs[i].profit;
                break;
            }

    const int cellWidth = 8;

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

    printScheduleBorder(maxDeadline, cellWidth);
    printScheduleRow(slot, jobs, maxDeadline, cellWidth);
    printScheduleBorder(maxDeadline, cellWidth);

    for (int t = 0; t <= maxDeadline; t++)
        cout << left << setw(cellWidth + 1) << t;
    cout << endl
         << endl
         << "Maximum Profit = " << totalProfit;
    return 0;
}