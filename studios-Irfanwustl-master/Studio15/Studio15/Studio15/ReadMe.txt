Answer to 1:
Name: Irfan Alahi

Answer to 2:
We can assign every pair.
We can do this because when we do the assignment only the values are copied. And when
we use a r-value reference compiler is forced to store that. So we can assign this value to 
other variable.

Answer to 3:
We can do all the operattions successfully. It means that though the values are moved, they are still not
destroyed and assignment operator woeks on a moved object.

Answer to 4:
(1)Yes.
(2)Because the number of constructor and destructor agrees.




Answer to 5:
(1) The number of constructor and destructor agrees. We can also verify it with 'real' word in the output, which tells total number
of created detector object upto that time. Note that within move constructor no new object is created because move moves the content.

(2)
output:
 main start
detector() address=013C1D20 x=0  real==1
....entering deep copy....
real detector obj=1
temp detector obj=0
detector() address=013C9310 x=1  real==2
temp detector obj=0
real detector obj=2
.....leaving deep copy ....
 entering move constructor
leaving move constructor
end main
~detector() address=013C1D20 x=0  real==2
~detector() address=013C9310 x=0  real==2

Answer to 6:
(1)Like question 5, the number of constructor and destructor agrees. We can also verify it with 'real' word in the output, which tells total number
of created detector object upto that time. Note that within move assignment no new object is created because move moves the content.

(2)
output:
 main start
detector() address=00EAF910 x=0  real==1
detector() address=00EA57A8 x=1  real==2
detector() address=00EAAEF0 x=2  real==3
 copy assignment start
....entering deep copy....
real detector obj=3
temp detector obj=0
detector() address=00EAAF20 x=3  real==4
temp detector obj=0
real detector obj=4
.....leaving deep copy ....
~detector() address=00EA57A8 x=1  real==4
copy assignment end
Entering move assignment
leaving move assignment
~detector() address=00EAAEF0 x=2  real==4
~detector() address=00EAAF20 x=0  real==4
~detector() address=00EAF910 x=0  real==4