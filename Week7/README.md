# OS COURSE: HW WEEK 7 TLB
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
(base) quang@quang-HP-ProBook-430-G6:~/Desktop/OS_course/Week7$ ./main 
Page Table:
Page: 000 Frame: 111
Page: 001 Frame: 110
Page: 010 Frame: 001
Page: 011 Frame: 011
Page: 100 Frame: 001
Page: 101 Frame: 111
Page: 110 Frame: 010
Page: 111 Frame: 100
Enter 8 bits logical address: 11100010
Physical Address (page table search): 10000010
TLB has been changed!!
TLB:
Page: 111 Frame: 100
%%%%%%%%%%%%%%%%%
Enter 8 bits logical address: 
```
