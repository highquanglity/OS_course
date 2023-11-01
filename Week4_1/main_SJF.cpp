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
    int waiting_time = 0;  // Waiting time
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
    priority_queue<Process, vector<Process>, CmpBurstTime> wait;
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

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

        cout << "Process id\tArrival time\tBurst time\tCompletion time\tTurnaround time\tWaiting time" << endl;
        outputFile << "\nProcess scheduling according to SJF is:" << endl;
        outputFile << "Process id\tArrival time\tBurst time\tCompletion time\tTurnaround time\tWaiting time" << endl;
        while (!inputProcesses.empty() || !wait.empty()) {
            while (!inputProcesses.empty() && inputProcesses[0].arrival_time <= current_time) {
                wait.push(inputProcesses[0]);
                inputProcesses.erase(inputProcesses.begin());
            }

            if (!wait.empty()) {
                auto process = wait.top();
                wait.pop();
                process.current_time = current_time + process.burst_time;
                process.tunr_artime = process.current_time - process.arrival_time;
                process.waiting_time = process.tunr_artime - process.burst_time;

                cout << "\t" << process.process_name << "\t\t" << process.arrival_time << "\t\t" << process.burst_time << "\t\t" << process.current_time << "\t\t" << process.tunr_artime << "\t\t" << process.waiting_time << endl;
                outputFile << "\t" << process.process_name << "\t\t" << process.arrival_time << "\t\t" << process.burst_time << "\t\t" << process.current_time << "\t\t" << process.tunr_artime << "\t\t" << process.waiting_time << endl;
                totalTurnaroundTime += process.tunr_artime;
                totalWaitingTime += process.waiting_time;

                current_time = process.current_time;
            } else if (!inputProcesses.empty()) {
                current_time = inputProcesses[0].arrival_time;
            }
        }

        double averageTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();
        double averageWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
        cout << "\nAverage Turnaround Time: " << averageTurnaroundTime << endl;
        cout << "Average Waiting Time: " << averageWaitingTime << endl;
        outputFile << "\nAverage Turnaround Time: " << averageTurnaroundTime << endl;
        outputFile << "Average Waiting Time: " << averageWaitingTime << endl;
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
