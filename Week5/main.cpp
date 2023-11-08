// ***by Nghiem Van Quang***
// g++ -pthread main.cpp -o main

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

struct Data
{
    int x, y, z;
    mutex ready1, ready2;
};

void logMessage(const char *tag, const char *message)
{
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20]; // Buffer to store formatted timestamp
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%H:%M:%S", timeinfo);
    printf("[%s] [%s]: %s\n", timestamp, tag, message);
}

void childThread(Data &data)
{

    lock_guard<mutex> lock(data.ready1);
    logMessage("INFO", "Child Working");
    data.z = data.x + data.y;
    logMessage("INFO", "Finished Calculation");
    data.ready2.unlock();
    logMessage("INFO", "Child Terminating");
}

int main()
{
    Data data;
    thread child;
    {
        lock_guard<mutex> lock(data.ready1);
        logMessage("INFO", "Parent Working");

        child = thread(childThread, ref(data));

        cout << "x = ";
        cin >> data.x;

        cout << "y = ";
        cin >> data.y;
        logMessage("INFO", "Parent Terminating");
    } // lock goes out of scope, releasing the lock

    data.ready2.lock();
    {
        lock_guard<mutex> lock(data.ready2);

        logMessage("INFO", "Parent Working");

        cout << "z = " << data.z << endl;

    }
    child.join();
    return 0;
}
