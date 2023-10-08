# OS COURSE: HW WEEK 2
> by: **Van Quang Nghiem**
## Usage/Examples
* To run the test code, enter the following command in the terminal:
```shell
sh main.sh "PATH_TO_FOLDER"
```
* Example:
```shell
sh main.sh ./
```
or:
```shell
sh main.sh ./validation_dir/
```
or:
```shell
sh main.sh /home/quang/Desktop/OS_course/Week2
```
## Running Tests
Results when testing in validation_dir directory
```shell
(base) quang@quang-HP-ProBook-430-G6:~/Desktop/OS_course/Week2$ sh main.sh ./validation_dir/
Compiling menu.c...
Empty files:
         1. ./validation_dir/sub2/yolov7_tiny.yaml
         2. ./validation_dir/sub2/subsub1/efficientnetB0.cfg
         3. ./validation_dir/sub1/yolov4.cfg
         4. ./validation_dir/sub1/subsub1/yolov3.cfg
         5. ./validation_dir/sub1/subsub1/ex2_1.js
         6. ./validation_dir/sub1/subsub1/hello.yaml
         7. ./validation_dir/bend.php
         8. ./validation_dir/hello.cpp
------------------------------------
Wanna delete ./validation_dir/sub2/yolov7_tiny.yaml? 
Please choose delete or not: type '1': delete, other: not delete
0
------------------------------------
Kept ./validation_dir/sub2/yolov7_tiny.yaml.
------------------------------------
Wanna delete ./validation_dir/sub2/subsub1/efficientnetB0.cfg? 
Please choose delete or not: type '1': delete, other: not delete
1
===========
Deleted ./validation_dir/sub2/subsub1/efficientnetB0.cfg successfully.
------------------------------------
Wanna delete ./validation_dir/sub1/yolov4.cfg? 
Please choose delete or not: type '1': delete, other: not delete
0
------------------------------------
Kept ./validation_dir/sub1/yolov4.cfg.
------------------------------------
Wanna delete ./validation_dir/sub1/subsub1/yolov3.cfg? 
Please choose delete or not: type '1': delete, other: not delete
0
------------------------------------
Kept ./validation_dir/sub1/subsub1/yolov3.cfg.
------------------------------------
Wanna delete ./validation_dir/sub1/subsub1/ex2_1.js? 
Please choose delete or not: type '1': delete, other: not delete
0
------------------------------------
Kept ./validation_dir/sub1/subsub1/ex2_1.js.
------------------------------------
Wanna delete ./validation_dir/sub1/subsub1/hello.yaml? 
Please choose delete or not: type '1': delete, other: not delete
0
------------------------------------
Kept ./validation_dir/sub1/subsub1/hello.yaml.
------------------------------------
Wanna delete ./validation_dir/bend.php? 
Please choose delete or not: type '1': delete, other: not delete
0
------------------------------------
Kept ./validation_dir/bend.php.
------------------------------------
Wanna delete ./validation_dir/hello.cpp? 
Please choose delete or not: type '1': delete, other: not delete
0
------------------------------------
Kept ./validation_dir/hello.cpp.
-----------------------
Done. Exiting...
```