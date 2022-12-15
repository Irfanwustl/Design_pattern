Answer to 1:
Name: Irfan Alahi

Answer to 2:
Values:a=5 and b=6

Answer to 3:
The output is swapped  for both integer variables and poniters. a=6 and b=5.

Answer to 4:
Expectation: I think the value of the integer variables will not be swapped but differenced values of the  pointers will be swapped.
It will differ from the last time because now the values of the integer variables are not swapped, but the values of the integer
pointers are swapped. So the ponter that pointid to value 5 previously, is pointing to value 6 now. This is true for both pointers. 

Real Output: As expected.


Answer to 5:
The integer values can be swapped because it is not constant.

5.1:
The compiler will unambiguously determine. It will call the version of argument (int * &). 
The output is matched. The version of argument (int * &)

5.2
Now the version of argument (int* const) will be called.
The output is matched.


Answer to 6:
The arguments should be passed by reference becausing we are changing the value of the integers. And the return type should be void.

6.1:
I have implemented the function and tested it with different values. The output is as expected. 
To tell if the vales are changed can be implemented as following. If both integers are divisible by a common factor(except 1) we can record this fact. To record we can use boolean 
value. If both are divisible, the value will be true otherwise false. 

6.2:
The method is implemented and tested.


