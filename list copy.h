/***********************************************************************
 * Header:
 *    LIST
 * Summary:
 *    Our custom implementation of std::list
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        List         : A class that represents a List
 *        ListIterator : An iterator through List
 * Author
 *    Samuel Ogilvie, Ethan Hodge, Jacob Nelson
 ************************************************************************/

#pragma once
#include <cassert>     // for ASSERT
#include <iostream>    // for nullptr
#include <new>         // std::bad_alloc
#include <memory>      // for std::allocator

namespace custom
{

/**************************************************
 * LIST
 * Just like std::list
 **************************************************/
template <typename T>
class list
{
public:
   //
   // Construct
   //

   list(); //{pHead = pTail = nullptr; }
   list(list <T> & rhs);
   list(list <T>&& rhs);
   list(size_t num, const T & t);
   list(size_t num);
   list(const std::initializer_list<T>& il);
   template <class Iterator>
   list(Iterator first, Iterator last);
  ~list()
   {
   }

   //
   // Assign
   //

   list <T> & operator = (list &  rhs);
   list <T> & operator = (list && rhs);
   list <T> & operator = (const std::initializer_list<T>& il);

   //
   // Iterator
   //

   class  iterator;
   iterator begin()  { return iterator(); }
   iterator rbegin() { return iterator(); }
   iterator end()    { return iterator(); }

   //
   // Access
   //

   T& front();
   T& back();

   //
   // Insert
   //

   void push_front(const T&  data);
   void push_front(      T&& data);
   void push_back (const T&  data);
   void push_back (      T&& data);
   iterator insert(iterator it, const T& data);
   iterator insert(iterator it, T&& data);

   //
   // Remove
   //

   void pop_back();
   void pop_front();
   void clear();
   iterator erase(const iterator& it);

   //
   // Status
   //

   bool empty()  const { return true; }
   size_t size() const { return numElements;   }


#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif
   // nested linked list class
   class Node;

   // member variables
   size_t numElements; // though we could count, it is faster to keep a variable
   Node * pHead;    // pointer to the beginning of the list
   Node * pTail;    // pointer to the ending of the list
};

/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
template <typename T>
class list <T> :: Node
{
public:
   //
   // Construct
   //
   Node()
   {
       pNext = pPrev = nullptr;
   }
   Node(const T &  data)
   {
       pNext = pPrev = nullptr;
       this->data = data;
   }
   Node(      T && data)
   {
       pNext = pPrev = nullptr;
        this->data = data;
        data = 0;
   }

   //
   // Data
   //

   T data;                 // user data
   Node * pNext;       // pointer to next node
   Node * pPrev;       // pointer to previous node
};

/*************************************************
 * LIST ITERATOR
 * Iterate through a List, non-constant version
 ************************************************/
template <typename T>
class list <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()
   {
       p = nullptr;
   }
   iterator(Node * p)
   {
       this->p = p;
   }
   iterator(const iterator  & rhs)
   {
      *this = rhs;
   }
   iterator & operator = (const iterator & rhs)
   {
       this->p = rhs.p;
          return *this;
   }
   
   // equals, not equals operator
   bool operator == (const iterator& rhs) const { return rhs.p != this->p; }
   bool operator != (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator, fetch a node
   T & operator * ()
   {
       return p->data;
       //else
        //   throw "Error";
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
       iterator temp(*this);
       p->pNext;
       return *this;
   }

   // prefix increment
   iterator & operator ++ ()
   {
       p->pNext;
       return *this;
   }
   
   // postfix decrement
   iterator operator -- (int postfix)
   {
       iterator temp(*this);
       p->pPrev;
       return *this;
   }

   // prefix decrement
   iterator & operator -- ()
   {
       p->pPrev;            //iterate the linked list
       return *this;
   }

   // two friends who need to access p directly
   friend iterator list <T> :: insert(iterator it, const T &  data);
   friend iterator list <T> :: insert(iterator it,       T && data);
   friend iterator list <T> :: erase(const iterator & it);

#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif

   typename list <T> :: Node * p;
};

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> ::list(size_t num, const T & t)
{
    numElements = num;
    pHead = pTail = nullptr;
    for (int i = 0; i < num; i++)
    {
        push_back(t);
    }
}

/*****************************************
 * LIST :: ITERATOR constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
template <class Iterator>
list <T> ::list(Iterator first, Iterator last)
{
   numElements = 99;
   pHead = pTail = new list <T> ::Node();

}

/*****************************************
 * LIST :: INITIALIZER constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
list <T> ::list(const std::initializer_list<T>& il)
{
    numElements = 0;
    pHead = pTail = nullptr;
    if (il.size())
    {

        // copy the value
        for (auto& item : il)
            push_back(item);

    }
    
   //numElements = 99;
   //pHead = pTail = new list <T> ::Node();
}

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> ::list(size_t num)
{
   numElements = num;
   pHead = pTail = nullptr;
   for (int i = 0; i < num; i++)
   {
       push_back(0);                                // we can just make new nodes!
   }
}

/*****************************************
 * LIST :: DEFAULT constructors
 ****************************************/
template <typename T>
list <T> ::list()
{
   numElements = 0;
   pHead = pTail = nullptr;
}

/*****************************************
 * LIST :: COPY constructors
 ****************************************/
template <typename T>
list <T> ::list(list& rhs)
{
    numElements = 0;
    pHead = pTail = nullptr;                        //ensure we're working with fresh elements
    if (rhs.pHead != nullptr)
    {
        list <T>::iterator index(rhs.pHead);        // declare our iterator and hand it the rhs
        while (index != rhs.pTail)                  // make use of our iterator
        {
            push_back(*index);
            index++;
        }
    }
}

/*****************************************
 * LIST :: MOVE constructors
 * Steal the values from the RHS
 ****************************************/
template <typename T>
list <T> ::list(list <T>&& rhs)
{
   numElements = rhs.numElements;
   pHead = rhs.pHead;
   pTail = rhs.pTail;
   rhs.pTail = rhs.pHead = nullptr;
}

/**********************************************
 * LIST :: assignment operator - MOVE
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS
 *********************************************/
template <typename T>
list <T>& list <T> :: operator = (list <T> && rhs)
{
   return *this;
}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
list <T> & list <T> :: operator = (list <T> & rhs)
{
    /*
    node <T>* pHead = nullptr;
    if (pSource != nullptr)         // we'll create a pHead and assign it value.
    {
        pHead = new Node <T>;
        pHead->data = pSource->data;
        pHead->pNext = nullptr;
        pHead->pPrev = nullptr;

        Node <T>* destPrev = pHead; // we want to keep pHead the same no matter what.
        Node <T>* atSource = pSource->pNext;
        while (atSource != nullptr)
        {
            destPrev->pNext = new Node <T>;
            destPrev->data = atSource->data;
            destPrev->pNext->pPrev = destPrev;

            atSource = atSource->pNext; // this iterates through atSource
            destPrev = destPrev->pNext;
        }
    }
    */
    return *this;
}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
list <T>& list <T> :: operator = (const std::initializer_list<T>& rhs)
{
   return *this;
}

/**********************************************
 * LIST :: CLEAR
 * Remove all the items currently in the linked list
 *     INPUT  :
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
void list <T> :: clear()
{
    if (pHead != nullptr)
    {
        list <T>::iterator index(pHead);  // declare our iterator and hand it the rhs
        for (int i = 0; i < numElements; i++)                                   // make use of our iterator
        {
            pop_front();
        }
    }
    numElements = 0;
}

/*********************************************
 * LIST :: PUSH BACK
 * add an item to the end of the list
 *    INPUT  : data to be added to the list
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_back(const T & data)
{
    Node* pNew = new Node(data);     //declare an empty node.
    if (pTail != nullptr)
    {
        pTail->pNext = pNew;         // attach pNew on the end of the list.
        pNew->pPrev = pTail;         // aim the pointer of Phead at the oldpHead.

        pTail = pNew;                // make new head
    }
    else
        pHead = pTail = pNew;
    numElements++;
}

template <typename T>
void list <T> ::push_back(T && data)
{
    Node* pNew = new Node(data);     //declare an empty node.
    if (pTail != nullptr)
    {
        pTail->pNext = pNew;         // attach pNew on the end of the list.
        pNew->pPrev = pTail;         // aim the pointer of Phead at the oldpHead.

        pTail = pNew;                // make new head
    }
    else
        pHead = pTail = pNew;
    numElements++;
}

/*********************************************
 * LIST :: PUSH FRONT
 * add an item to the head of the list
 *     INPUT  : data to be added to the list
 *     OUTPUT :
 *     COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_front(const T & data)
{
    Node* pNew = new Node(data);     //declare an empty node.
    if (pHead != nullptr)
    {
        pNew->pNext = pHead;         // append all of pHead below the new node.
        pHead->pPrev = pNew;         // aim the pointer of Phead at the oldpHead.

        pHead = pNew;                // make new head
    }
    else
        pHead = pTail = pNew;
    numElements++;
}

template <typename T>
void list <T> ::push_front(T && data)
{
    Node* pNew = new Node(data);     //declare an empty node.
    if (pHead != nullptr)
    {
        pNew->pNext = pHead;         // append all of pHead below the new node.
        pHead->pPrev = pNew;         // aim the pointer of Phead at the oldpHead.

        pHead = pNew;                // make new head
    }
    else
        pHead = pTail = pNew;
    numElements++;
}


/*********************************************
 * LIST :: POP BACK
 * remove an item from the end of the list
 *    INPUT  :
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> ::pop_back()
{
    if (pTail != nullptr)
    {
        if (pTail->pPrev != nullptr)        // we need a head before we can determine if it's alone.
        {
            pTail = pTail->pPrev;           // we make the front the next in line.
            delete pTail->pNext;            // follow the path behind pHead which should no longer be there and free it.
            pTail->pNext = nullptr;         // paranoia
        }
        else
        {
            delete pTail;                   //destroy the single node
            pTail = nullptr;
        }
        numElements--;
    }
}

/*********************************************
 * LIST :: POP FRONT
 * remove an item from the front of the list
 *    INPUT  :
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> ::pop_front()
{
    if (pHead != nullptr)
    {
        if (pHead->pNext != nullptr)        // we need a head before we can determine if it's alone.
        {
            pHead = pHead->pNext;           // we make the front the next in line.
            delete pHead->pPrev;            // follow the path behind pHead which should no longer be there and free it.
            pHead->pPrev = nullptr;         // paranoia
        }
        else
        {
            delete pHead;                   //destroy the single node
            pHead = nullptr;
        }
        numElements--;
    }
}

/*********************************************
 * LIST :: FRONT
 * retrieves the first element in the list
 *     INPUT  :
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: front()
{
    if(pHead != nullptr)
        return pHead->data;
    else
    {
//        throw std::string("ERROR: unable to access data from an empty list");
        return *(new T);
    }
}

/*********************************************
 * LIST :: BACK
 * retrieves the last element in the list
 *     INPUT  :
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: back()
{
    if (pTail != nullptr)
        return pTail->data;
    else
    {
        throw "ERROR: unable to access data from an empty list";
    }
}

/******************************************
 * LIST :: Erase
 * remove an item from the middle of the list
 *     INPUT  : an iterator to the item being removed
 *     OUTPUT : iterator to the new location
 *     COST   : O(1)
 ******************************************/
template <typename T>
typename list <T> :: iterator  list <T> :: erase(const list <T> :: iterator & it)
{
    //it.p
   return end();
}

/******************************************
 * LIST :: INSERT
 * add an item to the middle of the list
 *     INPUT  : data to be added to the list
 *              an iterator to the location where it is to be inserted
 *     OUTPUT : iterator to the new item
 *     COST   : O(1)
 ******************************************/
template <typename T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it,
                                                 const T & data)
{
   return end();
}

template <typename T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it,
   T && data)
{
   return end();
}

/**********************************************
 * LIST :: assignment operator - MOVE
 * Copy one list onto another
 *
 *********************************************/
template <typename T>
void swap(list <T> & lhs, list <T> & rhs)
{
    list <T>* temp = lhs;
    lhs = rhs;
    rhs = temp;
}


//#endif
}; // namespace custom
