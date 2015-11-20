/*
* A simple smart_ptr.
*/

#include<iostream>
using namespace std;

template<class T>
class smart_ptr
{
public:
	smart_ptr(T* ptr)
	{   
		ref = ptr;
		ref_count = new int(0);
		*ref_count = 1;
	}   
	~smart_ptr()
	{   
		if(--*ref_count == 0)
			clear();
	}   
	smart_ptr(smart_ptr<T>& sptr)
	{   
		ref = sptr.ref;
		ref_count = sptr.ref_count;
		++ *ref_count;
	}   
	smart_ptr<T>& operator = (smart_ptr<T>& sptr)
	{   
		if (this != &sptr)
		{
			if(--(*ref_count) == 0)
				clear();
			ref = sptr.ref;
			ref_count = sptr.ref_count;
			++(*ref_count);
		}
		return *this;
	}   
	T& operator * ()
	{
		if (*ref_count)
		{
			return *ref;
		}
	}
	T* operator -> ()
	{
		return ref;
	}
	int get_ref_count()
	{
		return *ref_count;
	}
protected:
	void clear()
	{
		if (ref_count)
		{
			delete ref_count;
		}
		if (ref)
		{
			delete ref;
		}
		ref_count = NULL;
		ref = NULL;
	}
protected:
	int *ref_count;
	T   *ref;
};
int main(int argc, char* argv[]) 
{	
	int *iptr = new int(10);
	smart_ptr<int> myptr1(iptr);
	cout<<myptr1.get_ref_count();
	smart_ptr<int> myptr2(myptr1);
	cout<<myptr2.get_ref_count();
	int *iptr2 = new int(20);
	smart_ptr<int> myptr3(iptr2);
	myptr3 = myptr1;
	cout<<myptr3.get_ref_count();
	getchar();
£ý
