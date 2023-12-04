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

        auto tlbEntry = find_if(tlb.begin(), tlb.end(), [pgNum](const auto &entry)
                                { return entry.pgNum == pgNum; });

        if (tlbEntry != tlb.end())
        {
            int physicalAddress = (tlbEntry->frameNum << 5) + offset;
            cout << "Physical Address (TLB search): " << bitset<8>(physicalAddress) << '\n';
        }
        else
        {
            auto pageTableEntry = find_if(pageTable.begin(), pageTable.end(), [pgNum](const auto &entry)
                                          { return entry.pgNum == pgNum; });

            if (pageTableEntry != pageTable.end())
            {
                int frameNum = pageTableEntry->frameNum;

                if (tlb.size() < 4)
                {
                    tlb.push_back({pgNum, frameNum});
                }
                else
                {
                    tlb.erase(tlb.begin());
                    tlb.push_back({pgNum, frameNum});
                }

                int physicalAddress = (frameNum << 5) + offset;
                cout << "Physical Address (page table search): " << bitset<8>(physicalAddress) << '\n';

                cout << "TLB has been changed!!\n";
                printTable("TLB", tlb);
            }
        }
        cout << "%%%%%%%%%%%%%%%%%\n";
    }

    return 0;
}
