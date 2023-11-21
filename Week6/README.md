# OS COURSE: HW WEEK 6 Banker's Algorithm
> by: **Van Quang Nghiem**
## Usage
* To run the test code, enter the following command in the terminal:
First, complie cpp file to exe file
```shell
g++ main.cpp -o main
```
after that, execute main file:
```shell
./main
```
## Running Tests
Results after running:
```shell
(base) quang@quang-HP-ProBook-430-G6:~/Desktop/OS_course/Week6$ ./main
Process | Allocation | Max | Available | Need
--------------------------------------------
   P0   | 0  1  0 | 7  5  3 | 3  3  2 | 7  4  3 
   P1   | 2  0  0 | 3  2  2 |         | 1  2  2 
   P2   | 3  0  2 | 9  0  2 |         | 6  0  0 
   P3   | 2  1  1 | 2  2  2 |         | 0  1  1 
   P4   | 0  0  2 | 4  3  3 |         | 4  3  1 
Safe sequence is:
 P1 -> P3 -> P4 -> P0 -> P2

```
