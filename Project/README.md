# OS COURSE: Shell Simulator using C/C++
> by: **Nghiem Van Quang, Nguyen Tuan Anh, Nguyen Pham Trung Hieu, Ha Dinh Dat**

> Github: ** https://github.com/highquanglity/OS_course/tree/main/Project **

### Mục lục
[I. Mở đầu](#Modau)

[II. Phân công công việc](#Phancong)

[III. Requirements](#yeucau)

[IV. Usage](#sudung)

[V. Tests](#kiemthu)

<a name="Modau"></a>

## Mở đầu
Repo này là bài tập lớn môn Hệ Điều Hành (ET4291) của nhóm 5, bao gồm các sinh viên:
- Nghiêm Văn Quang (20203547)
- Nguyễn Phạm Trung Hiếu (20203706)
- Nguyễn Tuấn Anh (20200038)
- Hà Đình Đạt (20203355)

Trong bài tập lớn này, các chức năng và câu lệnh của một Linux shell cơ bản sẽ được nhóm mô phỏng sử dụng ngôn ngữ lập trình C++.


<a name="Phancong"></a>

## Phân công công việc
MSSV| Thành viên | Công việc |
----|------------|-----------|
20200038| Nguyễn Tuấn Anh | Tìm hiểu về external command, exeExternalCmd(), handle_cd(), find_special_character(), expand_wcard(), expandWildcardTokens(), find_and_erase(), IsInsideQuotes(), làm báo cáo.| 
20203355| Hà Đình Đạt | Tìm hiểu về internal command, get_current_dir(), display_promt, handle_pwd(), handle_help(), trim(),wcard_check(), handle_redirect_check(), InItalicCmd_check(), exeCmdOutput()| 
20203706| Nguyễn Phạm Trung Hiếu | Viết test case, handle_cat(), exeInternalCmd(), SplitCmd_char(),get_delimeter_positions(), exeCmdOutput(), SplitCmd_pos(), README.md, làm báo cáo.| 
20203547| Nghiêm Văn Quang |Chia module, viết test case, doc cho hàm, ghép chương trình, single_cmd_process(), handle_redirection(), exeBackgndCmd(), exePipeCmd(), exeComplexCmds(), GetItalicCommaCommandOutput(), README.md |

<a name="yeucau"></a>

## Requirements:
- C++ 11, C++ 14, C++17.
- g++/gcc.
- Ubuntu > 16.04.

<a name="sudung"></a>

## Usage
* Đầu tiên, git clone toàn bộ Project từ dùng git: 
```shell
git clone https://github.com/highquanglity/OS_course.git
cd Project
```

Cấu trúc thư mục Project:
```shell
├── main
├── main.cpp
├── README.md
├── run.sh
├── tests
├── test_env
└── utils
    ├── external_cmd.cpp
    ├── external_cmd.h
    ├── internal_cmd.cpp
    ├── internal_cmd.h
    ├── utils.cpp
    └── utils.h

```
run.sh là bash script để chạy biên dịch toàn chương trình, sau đó chạy ./main để vào chương trình. Các file phụ trợ header file và source file nằm trong thư mục utils. Folder tests chứa các chương trình C++ để kiểm tra chức năng từng hàm. Folder test_env là thư mục riêng biệt chứa các file và folder được tạo ra để test chương trình hoạt động như thế nào, không gây ảnh hưởng đến các folder khác.

Khi đã trong folder Project, thực hiện bash script sau để biên dịch và chạy chương trình cho lần đầu hoặc có chỉnh sửa source:
```shell
sh run.sh
```

Từ lần sau đó, không cần biên dịch lại nữa, chỉ cần chạy chương trình:
```shell
./main
```

Sau đó thao tác như thao tác với shell bình thường, chú ý hiện tại chư thể sử dụng các arrow keys trong terminal.

<a name="kiemthu"></a>

## Tests
| Case | Đầu ra trên Ubuntu terminal | Kết quả chương trình|
|--------------|-------|------|
| ```cd test_env``` | Chuyển thành công vào test_env| Chuyển thành công vào test_env|
| ```pwd``` | /home/quang/Desktop/OS_course/Project/test_env | /home/quang/Desktop/OS_course/Project/test_env |
| ```echo date``` | date | date |
| ```cat hehe.py``` | print("dung roi ne") | print("dung roi ne") |
| ```ls *.ipynb``` | bed_11.ipynb  bed_21.ipynb  mnist_1_core.ipynb  mnist_5_core.ipynb  mobile_ss.ipynb | bed_11.ipynb  bed_21.ipynb  mnist_1_core.ipynb  mnist_5_core.ipynb  mobile_ss.ipynb  |
| ```ls bed*.ipynb``` | bed_11.ipynb  bed_21.ipynb | bed_11.ipynb  bed_21.ipynb |
| ```mkdir "quang'hieu"``` | Tạo thành công thư mục có tên quang'hieu | Tạo thành công thư mục có tên quang'hieu |
| ```mkdir "quang'dat'"``` | Tạo thành công thư mục có tên quang'dat' | Tạo thành công thư mục có tên quang'dat' |
| ```mkdir 'quang"tanh' ```| Tạo thành công thư mục có tên quang"tanh" | Tạo thành công thư mục có tên quang'tanh' |
| ```mkdir "quang'linh''"``` | Tạo thành công thư mục có tên quang'linh''| Tạo thành công thư mục có tên quang'linh''|
| ``` mkdir "quang"'" ``` | shell vào chế độ đợi lệnh kép tiếp theo | Invalid command, chương trình bị break |
| Vào trong thư mục yolo, thực hiện: <code>ls &#124; head -3 <code>| yolo3.yaml yolov4.yaml yolov5.yaml | yolo3.yaml yolov4.yaml yolov5.yaml|
| Vào trong thư mục yolo, thực hiện: <code>ls &#124; head -3 &#124; tail -1 <code> | yolov5.yaml | yolov5.yaml |
| ```echo `date` ``` | Thứ bảy, 06 Tháng 1 năm 2024 18:47:44 +07| Thứ bảy, 06 Tháng 1 năm 2024 18:47:44 +07 |
| ```ls >> file.txt ``` | Ghi thành công output khi thực hiện câu lệnh ls vào file.txt| Ghi thành công output khi thực hiện câu lệnh ls vào file.txt |
| ```pwd > file.txt ``` | Xóa toàn bộ nội dung file.txt đã có và ghi vào file này output của câu lệnh pwd| Xóa toàn bộ nội dung file.txt đã có và ghi vào file này output của câu lệnh pwd |
| ```mkdir "hello&&world" && pwd ``` | Tạo thành công thư mục có tên "hello&&world" đồng thơi thực hiện câu lệnh pwd và in ra terminal| Tạo thành công thư mục có tên "hello&&world" đồng thơi thực hiện câu lệnh pwd và in ra terminal |
| ```ls & pwd & echo hi ``` | Chạy ngầm và in ra pid của ls, pwd. echo hi chạy xong đầu tiên, tiếp theo là pwd và cuối cùng là ls|Chạy ngầm và in ra pid của ls, pwd. echo hi chạy xong đầu tiên, tiếp theo là pwd và cuối cùng là ls|
| ```cat hehe.txt > o.txt ``` | Ghi thành công nội dung của file hehe.txt vào file o.txt|Ghi thành công nội dung của file hehe.txt vào file o.txt|