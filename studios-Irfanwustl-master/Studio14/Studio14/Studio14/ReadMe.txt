Answer to 1:
Name: Irfan Alahi

Answer to 2:
(1) One detector  object was created
(2)One detector  object was destroyed.

Answer to 3:
(1) One detector  object was created but it was not destroyed.
(2) The created object was not destroyed in this case. Because it was created using new. So it remains in the heap. But previously the object was created 
with the variable that is destroyed when it is out of scope.


Answer to 4:
Now one detector  object was created and it was also destroyed. It occurred because we have explicitely freed the pointer to the detector  object in the wrapper 
destructor.

Answer to 5:
(1) Detector  object was both created and destroyed once.
(2) There might be a problem. If we do  not use the Boolean variable, deallocation will be occurred twice resulting in a crash.
(3) The first one (default constructed) as the Boolean variabl is true in the first one.

Answer to 6:
2 Detector  object was created and destroyed.

