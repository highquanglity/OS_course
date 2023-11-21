/**
 * @author Nghiem Van Quang
 * g++ main.cpp -o main
 * ./main
 * @source 
 */
#include <iostream>
#include <vector>

using namespace std;

void printTable(const vector<vector<int>> &alloc, const vector<vector<int>> &max, const vector<int> &avail, const vector<vector<int>> &need, const vector<int> &processes)
{
    cout << "Process | Allocation | Max | Available | Need" << endl;
    cout << "--------------------------------------------" << endl;
    int m = alloc[0].size();
    for (int i : processes)
    {
        cout << "   P" << i << "   |";

        // Print Allocation
        for (int j : alloc[i])
        {
            cout << " " << j << " ";
        }
        cout << "|";

        // Print Max
        for (int j : max[i])
        {
            cout << " " << j << " ";
        }
        cout << "|";

        // Print Available
        for (int j = 0; j < m; ++j)
        {
            if (i == 0)
            {
                cout << " " << avail[j] << " ";
            }
            else
            {
                cout << "   ";
            }
        }
        cout << "|";

        // Print Need
        for (int j : need[i])
        {
            cout << " " << j << " ";
        }

        cout << endl;
    }
}

vector<vector<int>> calculateNeed(const vector<vector<int>> &alloc, const vector<vector<int>> &max)
{
    int n = alloc.size();
    int m = alloc[0].size();

    vector<vector<int>> need(n, vector<int>(m));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    return need;
}

vector<int> findSafeSequence(const vector<vector<int>> &alloc, const vector<vector<int>> &max, vector<int> &avail, vector<vector<int>> &need)
{
    int n = alloc.size();
    int m = alloc[0].size();

    vector<int> ans, f(n, 0);

    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            if (f[i] == 0)
            {
                int flag = 0;
                for (int j = 0; j < m; ++j)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans.push_back(i);
                    for (int y = 0; y < m; ++y)
                    {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    return ans;
}

int main()
{
    vector<vector<int>> alloc = {{0, 1, 0},
                                 {2, 0, 0},
                                 {3, 0, 2},
                                 {2, 1, 1},
                                 {0, 0, 2}};
    vector<vector<int>> max = {{7, 5, 3},
                               {3, 2, 2},
                               {9, 0, 2},
                               {2, 2, 2},
                               {4, 3, 3}};
    vector<int> avail = {3, 3, 2};
    int n = alloc.size();
    int m = alloc[0].size();
    vector<int> process(n);
    for (int i = 0; i < n; i++)
    {
        process[i] = i;
    }

    vector<vector<int>> need = calculateNeed(alloc, max);
    printTable(alloc, max, avail, need, process);
    vector<int> safeSequence = findSafeSequence(alloc, max, avail, need);

    if (safeSequence.empty())
    {
        cout << "The given sequence is not safe" << endl;
    }
    else
    {
        cout << "Safe sequence is:" << endl;
        for (int i = 0; i < n - 1; ++i)
        {
            cout << " P" << safeSequence[i] << " ->";
        }
        cout << " P" << safeSequence[n - 1] << endl;
    }

    return 0;
}
