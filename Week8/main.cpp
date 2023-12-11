/**
 * @author Nghiem Van Quang
 * '''g++ main.cpp -o main
    ./main'''
 * @github https://github.com/highquanglity/OS_course/tree/main/Week8
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

// Constants
const int Del_ta = 16;
const int num_of_page = 10;
const int bit_ref = 4;

vector<int> CheckWorkingSet(const vector<vector<int>> &Bitarr)
{
    vector<int> RowHasOne(num_of_page, 0);
    for (int row = 0; row < num_of_page; ++row)
    {
        if (any_of(Bitarr[row].begin(), Bitarr[row].end(), [](int bit) { return bit == 1; }))
        {
            RowHasOne[row] = true;
        }
    }
    return RowHasOne;
}

void UpdateWorkingSet(vector<vector<int>> &Bitarr, vector<int> &workingSet)
{
    vector<int> RowContainsOnes = CheckWorkingSet(Bitarr);

    for (int row = 0; row < num_of_page; ++row)
    {
        if (RowContainsOnes[row])
        {
            auto it = find(workingSet.begin(), workingSet.end(), row);
            if (it == workingSet.end())
                workingSet.push_back(row);
        }
        else
        {
            workingSet.erase(remove(workingSet.begin(), workingSet.end(), row), workingSet.end());
        }
    }
}

void PrintWorkingSet(const vector<int> &workingSet)
{
    cout << "Working set: ";
    for (int page : workingSet)
    {
        cout << page << " ";
    }
    cout << endl;
}

void PrintBitArray(const vector<vector<int>> &Bitarr)
{
    cout << "Reference Bits Array: " << endl;
    for (int col = 0; col < num_of_page; ++col)
    {
        cout << "Page " << col << ": ";
        for (int row = 0; row < bit_ref; ++row)
        {
            cout << Bitarr[col][row] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void UpdateReferenceBits(vector<vector<int>> &Bitarr, int runth, const vector<int> &pageReferenceList)
{
    for (int row = 0; row < num_of_page; ++row)
    {
        Bitarr[row][runth % bit_ref] = 0;
    }

    int startElement = runth * Del_ta;
    cout << "Working set Window: ";
    for (int i = startElement; i < startElement + Del_ta; ++i)
    {
        int num_of_page = pageReferenceList[i];
        cout << num_of_page << " ";
        Bitarr[num_of_page][runth % bit_ref] = 1;
    }
    cout << endl;
    PrintBitArray(Bitarr);
}

int main()
{
    int listSize = 96;
    vector<int> pageReferenceList(listSize, 0);

    cout << "Page list: ";
    for (int i = 0; i < listSize; ++i)
    {
        pageReferenceList[i] = rand() % num_of_page;
        cout << pageReferenceList[i] << " ";
    }
    cout << endl;

    int timesrun = listSize / Del_ta;
    vector<int> workingSet;

    vector<int> bitvector(bit_ref, 0);
    vector<vector<int>> referenceBits(num_of_page, bitvector);

    for (int runth = 0; runth < timesrun; ++runth)
    {
        cout << "%%%%%%%%%%%%%%%%%%%Round " << runth + 1 << "%%%%%%%%%%%%%%%%%%%" << endl;
        UpdateReferenceBits(referenceBits, runth, pageReferenceList);
        UpdateWorkingSet(referenceBits, workingSet);
        PrintWorkingSet(workingSet);
    }

    return 0;
}
