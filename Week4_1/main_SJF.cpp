#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    string process_name;
    int arrival_time;
    int burst_time;
    int current_time = 0;  // Completion time
    int tunr_artime = 0; // Turnaround time
    int wait_pooling_time = 0;  // wait_pooling time
};

struct CmpBurstTime {
    bool operator()(const Process& a, const Process& b) {
        return a.burst_time > b.burst_time;
    }
};

void SJF_Scheduling(const vector<Process>& processes) {
    vector<Process> inputProcesses = processes;
    sort(inputProcesses.begin(), inputProcesses.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    int current_time = 0;
    priority_queue<Process, vector<Process>, CmpBurstTime> wait_pool;
    int totalTurnaroundTime = 0;
    int totalwait_poolingTime = 0;

    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        cout << "Input Processes:" << endl;
        cout << "Process id\tArrival time\tBurst time" << endl;
        outputFile << "Input Processes:" << endl;
        outputFile << "Process id\tArrival time\tBurst time" << endl;
        for (const auto& process : inputProcesses) {
            cout << "\t" << process.process_name << "\t\t" << process.arrival_time << "\t\t" << process.burst_time << endl;
            outputFile << "\t" << process.process_name << "\t\t" << process.arrival_time << "\t\t" << process.burst_time << endl;
        }

        cout << "\nProcess scheduling according to SJF is:" << endl;

        cout << "Process id\tArrival time\tBurst time\tCompletion time\tTurnaround time\twait_pooling time" << endl;
        outputFile << "\nProcess scheduling according to SJF is:" << endl;
        outputFile << "Process id\tArrival time\tBurst time\tCompletion time\tTurnaround time\twait_pooling time" << endl;
        while (!inputProcesses.empty() || !wait_pool.empty()) {
            while (!inputProcesses.empty() && inputProcesses[0].arrival_time <= current_time) {
                wait_pool.push(inputProcesses[0]);
                inputProcesses.erase(inputProcesses.begin());
            }

            if (!wait_pool.empty()) {
                auto process = wait_pool.top();
                wait_pool.pop();
                process.current_time = current_time + process.burst_time;
                process.tunr_artime = process.current_time - process.arrival_time;
                process.wait_pooling_time = process.tunr_artime - process.burst_time;

                cout << "\t" << process.process_name << "\t\t" << process.arrival_time << "\t\t" << process.burst_time << "\t\t" << process.current_time << "\t\t" << process.tunr_artime << "\t\t" << process.wait_pooling_time << endl;
                outputFile << "\t" << process.process_name << "\t\t" << process.arrival_time << "\t\t" << process.burst_time << "\t\t" << process.current_time << "\t\t" << process.tunr_artime << "\t\t" << process.wait_pooling_time << endl;
                totalTurnaroundTime += process.tunr_artime;
                totalwait_poolingTime += process.wait_pooling_time;

                current_time = process.current_time;
            } else if (!inputProcesses.empty()) {
                current_time = inputProcesses[0].arrival_time;
            }
        }

        double averageTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();
        double averagewait_poolingTime = static_cast<double>(totalwait_poolingTime) / processes.size();
        cout << "\nAverage Turnaround Time: " << averageTurnaroundTime << endl;
        cout << "Average wait_pooling Time: " << averagewait_poolingTime << endl;
        outputFile << "\nAverage Turnaround Time: " << averageTurnaroundTime << endl;
        outputFile << "Average wait_pooling Time: " << averagewait_poolingTime << endl;
        outputFile.close();
        cout << "Output written to output.txt" << endl;
    } else {
        cout << "Unable to open the output file." << endl;
    }
}

int main() {
    vector<Process> processes = {
        { "P1", 2, 6 },
        { "P2", 5, 2 },
        { "P3", 1, 8 },
        { "P4", 0, 3 },
        { "P5", 4, 4 }
    };

    SJF_Scheduling(processes);

    return 0;
}
