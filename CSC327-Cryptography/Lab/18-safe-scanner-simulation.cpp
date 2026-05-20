// Lab 18: Demonstrate basic logic of malicious code by simulating a simple harmless scanner/replication behavior in a controlled way (no harm).
#include <bits/stdc++.h>
using namespace std;

bool hasSuspiciousExtension(string name)
{
    string exts[] = {".exe", ".bat", ".vbs", ".js", ".scr", ".com"};
    for (int i = 0; i < 6; i++)
        if (name.size() >= exts[i].size())
            if (name.substr(name.size() - exts[i].size()) == exts[i])
                return true;
    return false;
}

int main()
{
    int n;
    cout << "Enter number of sandbox file names : ";
    cin >> n;

    vector<string> files(n);
    cout << "Enter file names :" << endl;
    for (int i = 0; i < n; i++)
        cin >> files[i];
    cout << endl
         << "Scan Report :" << endl;
    for (int i = 0; i < n; i++)
        if (hasSuspiciousExtension(files[i]))
            cout << files[i] << " -> suspicious" << endl;
        else
            cout << files[i] << " -> normal" << endl;

    string agentName;
    int copies;

    cout << endl
         << "Enter agent name : ";
    cin >> agentName;
    cout << "Enter number of copies : ";
    cin >> copies;

    vector<string> sandboxCopies;
    for (int i = 1; i <= copies; i++)
        sandboxCopies.push_back("copy_" + to_string(i) + "_" + agentName);

    cout << endl
         << "Replication Log :" << endl;
    for (string s : sandboxCopies)
        cout << s << endl;

    cout << endl
         << "Simulation only.";

    return 0;
}