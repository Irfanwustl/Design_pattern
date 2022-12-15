Answer to 1:
Name: Irfan Alahi

Answer to 2:
Before adding the constructor, I was getting error. After adding the constructor, the program outputs value 0 and 0 for the two variables. These values come from the
member initialization list.

Answer to 3:
If I change the declaration to class, I can not access the variables from main. But when I put public decaklaration, I can accesss the member variables.
After experimenting with public and private decaklarations with  both structure and class, I think the difference between structure and class is:
If I do not put anything, the structure assumes public but the class assumes private. That is why I can access class variable from amin without puclic declaration.


Answer to 4:
The original values were set by the constructor. And the non-const object's value is changed to 5 and 6. So the output is:

From non const object a=0 b=0
From const object a=0 b=0
From non const object after setting values a=5 b=6

Answer to 5:
compiler-supplied default constructor: It creates an  body of the class, that is, an empty object of the class.
compiler-supplied copy constructor: It simply duplictes the object.

Answer to 6:
The output is same to previous one. However, it seems with my own copy constructor I can manipulate the new object if necessary.

Answer to 7:
constructor is called when I initialize the object.
Copy contructor is called when I pass the object to the function. It is called both in pass by value and pass by reference.


Answer to 8:
If I declare default constructor private but do not define it, I can not create variables of that type. Compiler does not supply 
a default constructor.