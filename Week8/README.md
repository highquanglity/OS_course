# OS COURSE: HW WEEK 8 WS
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
(base) quang@quang-HP-ProBook-430-G6:~/Desktop/OS_course/Week8$ ./main
Page list: 3 6 7 5 3 5 6 2 9 1 2 7 0 9 3 6 0 6 2 6 1 8 7 9 2 0 2 3 7 5 9 2 2 8 9 7 3 6 1 2 9 3 1 9 4 7 8 4 5 0 3 6 1 0 6 3 2 0 6 1 5 5 4 7 6 5 6 9 3 7 4 5 2 5 4 7 4 4 3 0 7 8 6 8 8 4 3 1 4 9 2 0 6 8 9 2 
%%%%%%%%%%%%%%%%%%%Round 1%%%%%%%%%%%%%%%%%%%
Working set Window: 3 6 7 5 3 5 6 2 9 1 2 7 0 9 3 6 
Reference Bits Array: 
Page 0: 1 0 0 0 
Page 1: 1 0 0 0 
Page 2: 1 0 0 0 
Page 3: 1 0 0 0 
Page 4: 0 0 0 0 
Page 5: 1 0 0 0 
Page 6: 1 0 0 0 
Page 7: 1 0 0 0 
Page 8: 0 0 0 0 
Page 9: 1 0 0 0 

Working set: 0 1 2 3 5 6 7 9 
%%%%%%%%%%%%%%%%%%%Round 2%%%%%%%%%%%%%%%%%%%
Working set Window: 0 6 2 6 1 8 7 9 2 0 2 3 7 5 9 2 
Reference Bits Array: 
Page 0: 1 1 0 0 
Page 1: 1 1 0 0 
Page 2: 1 1 0 0 
Page 3: 1 1 0 0 
Page 4: 0 0 0 0 
Page 5: 1 1 0 0 
Page 6: 1 1 0 0 
Page 7: 1 1 0 0 
Page 8: 0 1 0 0 
Page 9: 1 1 0 0 

Working set: 0 1 2 3 5 6 7 9 8 
%%%%%%%%%%%%%%%%%%%Round 3%%%%%%%%%%%%%%%%%%%
Working set Window: 2 8 9 7 3 6 1 2 9 3 1 9 4 7 8 4 
Reference Bits Array: 
Page 0: 1 1 0 0 
Page 1: 1 1 1 0 
Page 2: 1 1 1 0 
Page 3: 1 1 1 0 
Page 4: 0 0 1 0 
Page 5: 1 1 0 0 
Page 6: 1 1 1 0 
Page 7: 1 1 1 0 
Page 8: 0 1 1 0 
Page 9: 1 1 1 0 

Working set: 0 1 2 3 5 6 7 9 8 4 
%%%%%%%%%%%%%%%%%%%Round 4%%%%%%%%%%%%%%%%%%%
Working set Window: 5 0 3 6 1 0 6 3 2 0 6 1 5 5 4 7 
Reference Bits Array: 
Page 0: 1 1 0 1 
Page 1: 1 1 1 1 
Page 2: 1 1 1 1 
Page 3: 1 1 1 1 
Page 4: 0 0 1 1 
Page 5: 1 1 0 1 
Page 6: 1 1 1 1 
Page 7: 1 1 1 1 
Page 8: 0 1 1 0 
Page 9: 1 1 1 0 

Working set: 0 1 2 3 5 6 7 9 8 4 
%%%%%%%%%%%%%%%%%%%Round 5%%%%%%%%%%%%%%%%%%%
Working set Window: 6 5 6 9 3 7 4 5 2 5 4 7 4 4 3 0 
Reference Bits Array: 
Page 0: 1 1 0 1 
Page 1: 0 1 1 1 
Page 2: 1 1 1 1 
Page 3: 1 1 1 1 
Page 4: 1 0 1 1 
Page 5: 1 1 0 1 
Page 6: 1 1 1 1 
Page 7: 1 1 1 1 
Page 8: 0 1 1 0 
Page 9: 1 1 1 0 

Working set: 0 1 2 3 5 6 7 9 8 4 
%%%%%%%%%%%%%%%%%%%Round 6%%%%%%%%%%%%%%%%%%%
Working set Window: 7 8 6 8 8 4 3 1 4 9 2 0 6 8 9 2 
Reference Bits Array: 
Page 0: 1 1 0 1 
Page 1: 0 1 1 1 
Page 2: 1 1 1 1 
Page 3: 1 1 1 1 
Page 4: 1 1 1 1 
Page 5: 1 0 0 1 
Page 6: 1 1 1 1 
Page 7: 1 1 1 1 
Page 8: 0 1 1 0 
Page 9: 1 1 1 0 

Working set: 0 1 2 3 5 6 7 9 8 4 
```
