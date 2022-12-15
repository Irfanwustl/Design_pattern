
Name: Irfan Alahi

Answer to 1:
1.1:
Choosen list =3,1,2

1.2:
The containers I can feel with push_back():vector, list, deque
The containers I can feel with push_front():forward_list, list, deque

Yes. forward_list must be populated differently. Because element can be inserted only at the beginning of it. 

1.3:
output:
Elements in vector: 3 1 2
Elements in forward_list: 3 1 2
Elements in list: 3 1 2
Elements in deque: 3 1 2


Answer to 2:
2.1:
sort() will only work on vector and deque as they are reandom access.
The hypothesis is tested and turned to be true.

2.2:
reverse() will work on vector, list and deque as they have bidirectional iterators. 
The hypothesis is tested and turned to be true.

output:
Elements in reversed vector: 2 1 3
Elements in reversed deque: 2 1 3
Elements in reversed list: 2 1 3