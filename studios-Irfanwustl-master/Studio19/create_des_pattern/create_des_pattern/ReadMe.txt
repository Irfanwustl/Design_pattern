Answer to 1:
Team membesrs: Irfan Alahi, Zhengliang Liu.

Answer to 2:
Creating an abstract base class to declare the interface of a builder enables to the client code that uses the builder to implement different types of complex objects.
For example, we can have different comnbinations of implementations of the calculator class because of this abstraction.

No, the client code that uses the Builder is not restricted to a single implementation of the Builder interface. It can use defferent combinations as mentioned above. 

Answer to 3:
The benefit is that an user can customize the functionality of the calculator. For example, if an user needs only two operations rather than four, he/she can easily implement
a calculator with only two ooperations using this separate method.
If a client only needs a calculator that supports addition, he can use this separate method to implement a calculator with only addition operator.

Answer to 4:
No. The main function does not know anything about the concrete objects which are used to create the calculator.
I have tested the calculator with various inputs and it is working correctly.

Answer to 5:
Yes, this implementation successfully limit our client to only a single calculator instance at a time. 
I have done all prescribed tests and the program runs as expected. For example, if I do not delete the calculator, the program does not create another calculator. However,
after deleting the calculator, another calculator can be created.