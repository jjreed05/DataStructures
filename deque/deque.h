/***********************************************************************
* Header:
*    Deque
* Summary:
*    This class contains the notion of a Deque, a bucket to hold
*    data for the user as a pop out and pop in on each end.

* Author
*    Jason Reed
************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>
#include <iostream>

using namespace std;

/************************************************
* Deque
* A class that holds stuff
***********************************************/
template <class T>
class Deque
{
public:
	// default constructor : empty and kinda useless
	Deque() : cap(0), numItems(0), myFront(0), myBack(0) { allocate(cap); }

	// copy constructor : copy it
	Deque(const Deque & rhs) throw (const char *);

	// non-default constructor : pre-allocate
	Deque(int cap) throw (const char *);

	// destructor : free everything
	~Deque() { if (cap) delete[] data; }
 
 	// assignment operator
	Deque& operator = (const Deque& rhs) throw (const char *);
 
	// checks to see if the Deque is empty
	bool empty() const { return (numItems == 0); }

	// removes the items from the Deque
	void clear() { while (!empty()) { pop_front(); } }

	// amount of items in the deque
	int size() const { return numItems; }

	// returns the capacity of the deque
	int capacity() { return cap; }
 
	// pushes an item to the front
	void push_front(const T & value) throw (const char *);

	// pushes an items to the back
	void push_back(const T & value) throw (const char *);

	// remove the front item
	void pop_front() throw (const char *);

	// remove the back item
	void pop_back() throw (const char *);

	// access the front item
	T & front() throw (const char *) { return array(myFront); }
 
  // acces the back item
	T & back() throw (const char *);
	
private:
	T * data;       // dynamically allocate the array     
	int myFront;    // integer to track the front            
	int myBack;     // integer to track the back            
	int cap;        // integer to track the capacity   
	int numItems;   // integer to track the number of items              

  // function used to help copy items
  void copy(const Deque<T> & rhs);
  
  // function to check for errors
	void allocate(int Space) throw (const char *);
  
  // function used to return an item in the array
	T & array(int index) throw (const char *);
};

/*******************************************
* Deque :: COPY CONSTRUCTOR
*******************************************/
template <class T>
Deque <T> ::Deque(const Deque <T> & rhs) throw (const char *)
{
	assert(rhs.cap >= 0);

	// do nothing if there is nothing to do
	if (rhs.cap == 0)
	{
		cap = numItems = 0;
		data = NULL;
		myFront = myBack = 0;
		return;
	}

	// attempt to allocate
	allocate(rhs.cap);

	// copy over the myCapacity and size
	assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
	this->cap = rhs.cap;
	this->numItems = rhs.numItems;
	this->myFront = rhs.myFront;
	this->myBack = rhs.myBack;

	int index = myFront;
	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
	{
		data[index] = rhs.data[index];
		index = (index + 1) % cap;
	}
}

/**********************************************
* Deque : NON-DEFAULT CONSTRUCTOR
* Preallocate the Deque to "myCapacity"
**********************************************/
template <class T>
Deque <T> ::Deque(int pCapacity) throw (const char *)
{
	assert(pCapacity >= 0);

	// do nothing if there is nothing to do
	if (pCapacity == 0)
	{
		this->cap = this->numItems = 0;
		this->data = NULL;
		this->myFront = this->myBack = 0;
		return;
	}

	// try to allocate
	allocate(pCapacity);

	// set the variables
	this->cap = pCapacity;
	this->numItems = 0;
	this->myFront = this->myBack = 0;

	// initialize the Deque by calling the default constructor
	for (int i = 0; i < pCapacity; i++)
		data[i] = T();
}

/***************************************************
 * Deque :: operator =
 * Copies the data from one stack to another
 **************************************************/
template <class T>
Deque <T> & Deque <T> :: operator = (const Deque & rhs) 
  throw (const char *)
{
   if (cap != rhs.cap)
		{
			allocate(rhs.cap);
		}
		copy(rhs);
		return *this;
}

/**********************************************
* Deque : push_front
* Pushes an item to the front
**********************************************/
template <class T>
void Deque <T> ::push_front(const T & value) throw (const char *)
{
	int newFront;
  // sets the variables if it's empty
	if (numItems == 0 && cap != 0)
	{
		myFront = 0;
		myBack = 0;
	}
   
  // Double the capacity if empty
	if (cap == 0)
	{
		cap = 2;
		allocate(cap);
		newFront = (myFront) % cap;
	}
 
  // Double the capacity if we are over capacity
	else if (numItems >= cap)
	{
		int oldCapacity = cap;
		cap *= 2;
    // dynamically allocate a temporary array
		T * tmp;
   
    // check for error
		try
		{
			tmp = new T[cap];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for Deque";
		}
    
    // allows us to use the original myFront
		int index = myFront;
    // copy the items from temporary array to the new
		for (int i = 0; i < numItems; i++)
		{
			tmp[i] = data[(index + i) % oldCapacity];
		}

		delete[] data;
		data = tmp;
		myFront = 0;
		myBack = numItems;
	}
 
  // push the item unto the array if we have 0 items
	else if (numItems == 0)
	{
		data[myFront] = value;
		numItems++;
		return;
	}

  // keep the circular implementation and push
	myFront = (myFront - 1 + cap) % cap;
	data[myFront] = value;
	numItems++;
}

/**********************************************
* Deque : push_back
* Pushes an item to the back
**********************************************/
template <class T>
void Deque <T> :: push_back(const T & value) throw (const char *)
{
	int newBack;
  // sets the variables if it's empty
	if (numItems == 0 && cap != 0)
	{
		myFront = 0;
		myBack = 0;
	}

	if (cap == 0)
	{
		cap = 2;
		allocate(cap);
		newBack = (myBack + 1) % cap;
	}
	else if (numItems >= cap)
	{
		int oldCapacity = cap;
		cap *= 2;
		T * tmp;

		// check for error
		try
		{
			tmp = new T[cap];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for Deque";
		}

		int index = myFront;
   
		// copy the items over one at a time using the assignment operator
		for (int i = 0; i < numItems; i++)
		{
			tmp[i] = data[index];
			index = (index + 1) % oldCapacity;
		}

		delete[] data;
		data = tmp;
  
    // reset the variables
		myFront = 0;
		myBack = numItems;
	}
  
  // make sure the back is set to 0
	else if (numItems == 0)
	{
		myBack = 0;
	}
  
  // push the value into the array
	data[myBack] = value;
  // implement the cicle
	myBack = (myBack + 1) % cap;
	numItems++;
}

/**********************************************
* Deque : pop_front
* Pops an item off the front
**********************************************/
template <class T>
void Deque <T> :: pop_front() throw (const char *)
{
   // their has to be items to pop
   if (!empty())
		{
			myFront = (myFront + 1) % cap;
			numItems--;
		}
		else
		{
			throw "ERROR: unable to pop from the front of empty deque";
		}
}

/**********************************************
* Deque : pop_back
* Pop an item off the back
**********************************************/
template <class T>
void Deque <T> :: pop_back() throw (const char *)
{
   if (!empty())
		{
			myBack = (myBack - 1 + cap) % cap;
			numItems--;
		}
		else
		{
			throw "ERROR: unable to pop from the back of empty deque";
		}
}

/**********************************************
* Deque : copy
* Copy items from Deque from one to the other
**********************************************/
template <class T>
void Deque <T> :: copy(const Deque<T> & rhs)
{
	assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
	numItems = rhs.numItems;
	cap = rhs.cap;
	myFront = rhs.myFront;
	myBack = rhs.myBack;

	int index = myFront;
	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
	{

		data[index] = rhs.data[index];
		index = (index + 1) % cap;
	}

}

/*******************************
 * BACK
 *  Return LAST item
 *******************************/
template <class T>
T & Deque <T> :: back() throw (const char *)
{
   if (myBack != 0)
			return array(myBack - 1);
		else
			return array(myBack);
}

/**********************************************
* Deque : allocate
* Check for errors
**********************************************/
template <class T>
void Deque <T> :: allocate(int space) throw (const char *)
{
	// attempt to allocate
	try
	{
		data = new T[space];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a new buffer for Deque";
	}
}

/**********************************************
* Deque : array
* Returns the item in the array
**********************************************/
template <class T>
T & Deque <T> :: array(int index) throw (const char *)
{
	if (!empty())
	{
		return data[index];
	}
	else
	{
		throw "ERROR: unable to access data from an empty deque";
	}
}

#endif // DEQUE_H