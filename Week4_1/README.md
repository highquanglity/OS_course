# OS COURSE: HW WEEK 4 SJF SCHEDULING
> by: **Van Quang Nghiem**
## Usage
* To run the test code, enter the following command in the terminal:
First, complie c file to exe file
```shell
g++ ./main_SJF.cpp -o ./main_SJF
```
after that, execute main.exe file:
```shell
./main_SJF
```
## Running Tests
Results after running:
```shell
(base) quang@quang-HP-ProBook-430-G6:~/Desktop/OS_course/Week4_1$ ./main_SJF
Input Processes:
Process id      Arrival time    Burst time
        P4              0               3
        P3              1               8
        P1              2               6
        P5              4               4
        P2              5               2

Process scheduling according to SJF is:
Process id      Arrival time    Burst time      Completion time Turnaround time Waiting time
        P4              0               3               3               3               0
        P1              2               6               9               7               1
        P2              5               2               11              6               4
        P5              4               4               15              11              7
        P3              1               8               23              22              14

Average Turnaround Time: 9.8
Average Waiting Time: 5.2
Output written to output.txt

```
