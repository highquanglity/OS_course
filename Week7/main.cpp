/**
 * @author Nghiem Van Quang
 * '''g++ main.cpp -o main
    ./main'''
 * @github https://github.com/highquanglity/OS_course/tree/main/Week7
 */
#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

struct TableLkup
{
    int pgNum;
    int frameNum;
};

void initializePageTable(vector<TableLkup> &pageTable)
{
    for (int i = 0; i < 8; i++)
    {
        pageTable.push_back({i, rand() % 8});
    }
}

void printTable(const string &tableName, const vector<TableLkup> &table)
{
    cout << tableName << ":\n";
    for (const auto &entry : table)
    {
        cout << "Page: " << bitset<3>(entry.pgNum) << " Frame: " << bitset<3>(entry.frameNum) << '\n';
    }
}

int calculatePhysicalAddress(const TableLkup &entry, int offset)
{
    return (entry.frameNum << 5) + offset;
}

TableLkup searchTable(const vector<TableLkup> &table, int pgNum)
{
    auto entry = find_if(table.begin(), table.end(), [pgNum](const auto &e)
                        { return e.pgNum == pgNum; });

    return (entry != table.end()) ? *entry : TableLkup{-1, -1};
}

void updateTLB(vector<TableLkup> &tlb, int pgNum, int frameNum)
{
    if (tlb.size() < 4)
    {
        tlb.push_back({pgNum, frameNum});
    }
    else
    {
        tlb.erase(tlb.begin());
        tlb.push_back({pgNum, frameNum});
    }
}

int main()
{
    vector<TableLkup> tlb, pageTable;
    pageTable.reserve(8);

    initializePageTable(pageTable);
    printTable("Page Table", pageTable);

    while (true)
    {
        string input;
        cout << "Enter 8 bits logical address: ";
        cin >> input;

        if (input.size() != 8)
        {
            cout << "Invalid input. Enter 8 bits, please\n";
            continue;
        }

        int logicalAddress = stoi(input, 0, 2);
        int pgNum = (logicalAddress & 0b11100000) >> 5;
        int offset = logicalAddress & 0b00011111;

        TableLkup tlbEntry = searchTable(tlb, pgNum);

        if (tlbEntry.pgNum != -1)
        {
            int physicalAddress = calculatePhysicalAddress(tlbEntry, offset);
            cout << "Physical Address (TLB search): " << bitset<8>(physicalAddress) << '\n';
        }
        else
        {
            TableLkup pageTableEntry = searchTable(pageTable, pgNum);

            if (pageTableEntry.pgNum != -1)
            {
                int frameNum = pageTableEntry.frameNum;
                updateTLB(tlb, pgNum, frameNum);

                int physicalAddress = calculatePhysicalAddress(pageTableEntry, offset);
                cout << "Physical Address (page table search): " << bitset<8>(physicalAddress) << '\n';

                cout << "TLB has been changed!!\n";
                printTable("TLB", tlb);
            }
        }
        cout << "%%%%%%%%%%%%%%%%%\n";
    }

    return 0;
}
