Name: Irfan Alahi
Lab:1

Errors:Luckily I did not get any error.
Warning: I get warning when I try to compare int with a vector size. The warning was "warning C4018: '<': signed/unsigned mismatch". It was because int can be 
negative. however vector size can not be. So I have used size_t instead of int.

Command lines:
The name of my executable is Lab1.exe.

Test case 1. Command: Lab1.exe
Output: usage: Lab1.exe <filename.txt>
So my program outputs correctly the usage message and returns 2 denoting wrong_number_of_argument.

Test case 2. Command: Lab1.exe input.txt a.txt
Output: usage: Lab1.exe <filename.txt>
Again wrong number of inputs and my program outputs correctly the usage message and returns 2 denoting wrong_number_of_argument.

Test case 3. Command: Lab1.exe a.txt
Output:  (None)
As a.txt is not found in the directory, my program output none and returns 1 denoting file_cannot_open

Test case 4: Command: Lab1.exe input.txt
Output: This time the input file name is correct and my program outputs file contents properly. I have conducted lots of 
test cases. For example empty file, file with only character string, with numbers, with number and character string together, etc.
Every time my program outputs properly. 



Extra Credit
Before using qlogin [irfan.alahi@shell ~]$. After qlogin [irfan.alahi@linuxlab011 ~]$

No Error or warning

Command lines:
The name of my executable is LinuxLab1. To get the return value I use  <echo $?> command.
Test case 1. Command: /LinuxLab1
Output: usage: ./LinuxLab1 <filename.txt> 
So my program outputs correctly the usage message and returns 2 denoting wrong_number_of_argument.

Test case 2. Command: ./LinuxLab1 input.txt a.txt
Output: usage: ./LinuxLab1 <filename.txt> 
Again wrong number of inputs and my program outputs correctly the usage message and returns 2 denoting wrong_number_of_argument.


Test case 3. Command:  ./LinuxLab1 a.txt
Output:  (None)
As a.txt is not found in the directory, my program output none and returns 1 denoting file_cannot_open


Test case 4: Command: ./LinuxLab1 input.txt
Output: This time the input file name is correct and my program outputs file contents properly. I have with all types of files as mentioned above for the windows part and 
my program outputs properly.

