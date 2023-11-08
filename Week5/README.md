# OS COURSE: HW WEEK 5 MUTEX
> by: **Van Quang Nghiem**
## Usage
* To run the test code, enter the following command in the terminal:
First, complie c file to exe file
```shell
g++ -pthread main.cpp -o main
```
after that, execute main.exe file:
```shell
./main
```
## Running Tests
Results after running:
```shell
(base) quang@quang-HP-ProBook-430-G6:~/Desktop/OS_course/Week5$ ./main
[23:48:31] [INFO]: Parent Working
x = 6
y = 8
[23:48:33] [INFO]: Parent Terminating
[23:48:33] [INFO]: Child Working
[23:48:33] [INFO]: Finished Calculation
[23:48:33] [INFO]: Child Terminating
[23:48:33] [INFO]: Parent Working
z = 14
[23:48:33] [INFO]: Parent Terminating

```
