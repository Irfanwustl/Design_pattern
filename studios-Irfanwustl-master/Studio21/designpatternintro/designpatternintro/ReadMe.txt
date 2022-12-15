Behavioral Patterns Studio:

answers and discussion:
1. Group members: Irfan Alahi


2.Difference between Strategy pattern and Template Method pattern: If many related classes only differ in their behaviors, we use Strategy pattern. On the other hand, if
many classes differs only some part of the algorithm, we use Template Method pattern.
Similarity betwwen Strategy pattern and Template Method pattern: Both are bahavioral pattern. Both allows users to modify the behavior at run-time.


Yes. The program behaves as expected.

Factory method is used when a class can not anticipate the objects it create, but the class wants the subclass to specify the objects it creates.
Here the abstract class CalculatorBase has a method addOperation which must be defined by its derived classes. When the subclass of the CalculatorBase
defines this method they decide which calculatable object should be created. Hence the  addOperation method is the factory method and the pattern is the
factory method pattern. It has the benefit that when PrecedenceCalculator defines addOperation, PrecedenceCalculator can create  calculatable objects based on 
its needs.



3.Participants: 
Handler: Interface to manage the requests.
Concrete Handler: If the request is handleable by a concrete handler, it handles the request. Otherwise, forwards the request to its successor.
Client: Starts the request.




4. Tested successfully. It is working.