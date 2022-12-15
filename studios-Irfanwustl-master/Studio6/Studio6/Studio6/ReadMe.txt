Answer to 1:
Name: Irfan Alahi


Answer to 2:
If I call squareElement with bigger index, I get a runtime error.
After throwing and catching excetpion, if I provide an out-of-bound index it will be caught. I have implemented such a way that after catching the exception, a meesage (vector out of range)
will be printed.
I have tested the prediction and the out is as expected.
Resulting output: vector out of range

If I failed to catch it, the runtime error would occur again.

Answer to 3:
The order is:
catch (out_of_range e)
catch (logic_error e)
Reason: The out_of_range is inherited from  logic_error . So logic_error can catch out_of_range. If we place catch (logic_error e) first, catch (out_of_range e) canot catch
the out_of_range and become useless.
It is not  necessary to throw out of bound exceptions in  divideSquaredElements because of stack unwinding. The search for appropriate catch clause continues in the calling 
function and main has already that catch clause.


Answer to 4:

case 1 output:
enetering divideSquaredElements
entering squareElement
leaving squareElement
entering squareElement
leaving squareElement
leaving divideSquaredElements

case 2 output:
enetering divideSquaredElements
entering squareElement
leaving squareElement
entering squareElement
leaving squareElement

case 3 output:
enetering divideSquaredElements
entering squareElement
leaving squareElement
entering squareElement

If any exception is occured, nothing will excute until the error is caught. After catching the error, program will resume exceuting from the 
next line of catching, not from the line where the error occurred.
