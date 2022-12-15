Answer to 1:
Name: Irfan Alahi


Answer to 2:
code in header file:
class detector {
	unsigned int x;
	static unsigned int y;

public:
	detector();
	~detector();
	unsigned int get_x();
};

code in source file:

unsigned int detector::y = 0;

detector::detector()
{
	x = y;
	y++;
	cout << "detector() address=" << this << " x=" << x<<endl;
}

detector::~detector()
{
	cout << "~detector() address=" << this << " x=" << x << endl;
}

unsigned int detector::get_x()
{
	return x;
}




Answer to 3:
When the shared_ptr goes out of scope, the detector object's destructor is called so the object is destroyed. 

Answer to 4:
(a)shared_ptr in the main function
(b)when main function goes out of scope
(c)only once
(d)No aliases to it remain after the object is destroyed because shared_ptr destroys an object when its reference count become 0.

Answer to 5:
(a)More number are created and destroyed
(b)Because more objects are created now dynamically.

Answer to 6:
output:
Real Addresses: 002BCD14 002BD194 002BD214
Adress in the vector: 002BCD14 002BD194 002BD214

Based on the output, we can say same objects are being aliased by the two different sets of shared_ptr variables. 


 Answer to 7:
 If I explicitly call delete on the pointers to the detector objects, the objects are deleted. But If I do not explicitely call they are not deleted.
 Vector cleans up the value of the pointers, not the objects pointed to.
