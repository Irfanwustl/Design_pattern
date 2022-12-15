Answer to 1:
Name: Irfan Alahi

Answer to 2:

There are more constructors and destructors for the base class(myclass). It is because when the derived class(Derived) is created, base class is also created again. 

output:
myclass myclass()
myclass myclass()
Derived  Derived()
Derived ~Derived()
myclass ~myclass()
myclass ~myclass()

Answer to 3:
The output is expected.
output:
call using myclass object
myclass void same()
call using myclass reference initialized using myclass object
myclass void same()
call using myclass reference initialized using Derived object
myclass void same()
call using Derived reference
Derived void same()


After using virtual keyword:
Output:
call using myclass object
myclass void same()
call using myclass reference initialized using myclass object
myclass void same()
call using myclass reference initialized using Derived object
Derived void same()
call using Derived reference
Derived void same()

When the function is called using myclass reference initialized using Derived object the output differs.
This time the function of the derived class is called. 
Because virtual keyword enables dynamic binding. So the implementation defined in the derived class is called as myclass reference was initialized using the derived object.
If the reference is of base (or derived) class and it is also initialized with base (or derived) class object, then the output remains same.


Answer to 4:
It acts like the calls made using the references. Because when a virtual function is called through a reference or pointer to a base class the call is resolved dynamically.
This is true for both  reference and pointer. 

Answer to 5:
Without virtual keyword all derived objects did not destruct because one derived object was created and assigned to a base class pointer. So when
delete is called for that pointer only the base class is deleted as there is no virtual keyword. When we use virtual keyword before the destructors, the
destructors are resolved dynamically. In that case the number of destructor and constructor becomes same.

Answer to 6:
The behavior matched with the original object, when we use pass by reference.
But if we use pass by value and the function expects a base type, derived class are sliced down.


