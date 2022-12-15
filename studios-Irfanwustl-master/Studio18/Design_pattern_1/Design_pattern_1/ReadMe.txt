Answer to 1:
Name: Irfan Alahi

Answer to 2:
Benefits of Separation of concerns: It helps modular development. If different concerns are separated or indepenedent, the program becomes much more flexible. 
A feature of a concern can be modified wirhout affecting other concerns' implementations.
Different concerns in our calculator: We can separate the functionalities of our calculator into input/output(user interface), input processing, actual calculation. 
The user interface should deal with taking input from the user and displaying it after calculation. If we separate this concern, we can change this interface without bothering
actual calculation. Second, for input  processing we should define an intermediate represntation of the input. This intermediate represntation will be the input of
actual calculation function. Whatever input is provided by the user, we should convert it to the intermediate represntation. Finally, the  actual calculation concern will
calculate the intermediate representation.

Answer to 3:
We can use an abstract class(interface) for parsing. The concrete strategy for parsing would implement the required algorithm for parsing inheriting this abstract class.
Thus we can use required strategy for parsing from these family of algorithm.


Answer to 4:
Done.

Answer to 5:
Done.

Answer to 6: 
Output:

infix input:2 + 3
infix result=5
prefix input:+ 2 3
prefix result=5
infix input:10 / 2 * 3 + 20 - 12
infix result=23
prefix input:/ 10 - + * 2 3 20 12
prefix result=23
infix input:10 + 20 - 5 / 5 * 10
infix result=50
prefix input:- + 10 20 / 5 * 5 10
prefix result=50
