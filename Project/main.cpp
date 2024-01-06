#include "utils/utils.h"
#include "stdlib.h"
#include "iostream"


using namespace std;
int main()
{
    system("clear");
    string command;
    
    while (true)
    {   

        display_prompt();       
        getline(cin, command);

        if (command.empty())
        {
            continue;
        }
        exeComplexCmds(command);
    }

    return 0;
}
