Answer to 1:
Team membesrs: Irfan Alahi, Zhengliang Liu.

Answer to 2:
Done successfully.

Answer to 3:
A leaf node has no child. Functionality implemented for managing children in DisplayableComponent class is implemented for the case when there is no children and task 
inherits   DisplayableComponent class. So we do not need to override the  functionality for managing children.

Answer to 4:
b(iv): This method is creating object based on the user input which can not be anticipated by DisplayableComponent class. We know factory method does the same thing.
So this is a factory method.

Output: First the name of the to do list is printed and then the tasks' names are printed. For example, below is a complete output starting from the promptint the user
and the name of the to do list is testtodo:

Enter the name of a Task:tast1
Enter the name of a Task:task2
Enter the name of a Task:task3
testtodo
tast1
task2
task3



Answer to 5:
Participants:
Component: interface for objects. Subclass of this interface will be decorated.
Concrete Component: Implementation of the Component. Objects of this class will be decorated.
Decorator: defines an interface similar to Component's interface. This is the interface for the concrete decorator.
Concrete Decorator: Decorates the component.


Answer to 6:
Done successfully.

Answer to 7:
Done successfully.

Answer to 8:
Done successfully.

Answer to 9:
Prioritizing the same task twice gives the same task two (*).
Marking a prioritized task as complete, attaches -complete after the star (*) symbol.

How the decorator pattern work: Decorator pattern defines similar interface to the interface to be decorated. If decoration is necessary, decorator pattern's
object (which is similar to  the interface to be decorated) is used (after decoration) instead of the actual object. 