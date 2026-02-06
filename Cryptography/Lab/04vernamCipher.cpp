// Lab 4: Implement the Vernam cipher encryption and decryption program using XOR-based logic.
#include <bits/stdc++.h>
using namespace std;

string toBinary(unsigned char x)
{
    string s;
    for (int i = 7; i >= 0; i--)
        s += (x >> i & 1) + '0';
    return s;
}

void vernam(vector<int> &nums, string &res, const string &key, bool enc)
{
    cout << endl
         << "Step-by-step XOR :" << endl
         << endl;
    string border = enc ? "+---+----------+---+----------+-------+----------+"
                        : "+-------+----------+---+----------+---+----------+";
    cout << border << endl
         << (enc ? "| P |  P_bin   | K |  K_bin   | C_num |  C_bin   |"
                 : "| C_num |  C_bin   | K |  K_bin   | P |  P_bin   |")
         << endl
         << border << endl;

    for (int i = 0, n = enc ? res.size() : nums.size(); i < n; i++)
    {
        unsigned char T = enc ? res[i] : nums[i], K = key[i], R = T ^ K;

        if (enc)
            cout << "| " << T << " | " << toBinary(T) << " | " << K
                 << " | " << toBinary(K) << " |  " << setw(5) << left << (int)R
                 << "| " << toBinary(R) << " |" << endl,
                nums.push_back(R);
        else
            cout << "|  " << setw(5) << left << nums[i] << "| " << toBinary(T)
                 << " | " << K << " | " << toBinary(K) << " | " << R
                 << " | " << toBinary(R) << " |" << endl,
                res += (char)R;
    }
    cout << border << endl;
}

int main()
{
    int choice;
    string text, key;
    vector<int> nums;

    cout << "---Vernam Cipher---\n1. Encrypt\n2. Decrypt\nEnter your choice : ";
    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        cout << endl
             << "Enter text : ";
        getline(cin, text);
        cout << "Enter key (length " << text.size() << ") : ";
        getline(cin, key);

        if (text.empty() || key.size() != text.size())
            return cout << endl
                        << "Invalid input." << endl,
                   0;

        vernam(nums, text, key, true);

        cout << endl
             << "Ciphertext : ";
        for (int x : nums)
            cout << x << " ";
    }
    else if (choice == 2)
    {
        cout << endl
             << "Enter ciphertext (space-separated numbers) : ";
        getline(cin, text);

        stringstream ss(text);
        for (int x; ss >> x;)
            nums.push_back(x);

        cout << "Enter key (length " << nums.size() << ") : ";
        getline(cin, key);

        if (nums.empty() || key.size() != nums.size())
            return cout << endl
                        << "Invalid input." << endl,
                   0;

        text.clear();
        vernam(nums, text, key, false);

        cout << endl
             << "Plaintext : " << text;
    }
    else
        cout << endl
             << "Invalid choice.";

    return 0;
}