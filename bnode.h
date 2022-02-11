/***********************************************************************
 * Header:
 *    BINARY NODE
 * Summary:
 *    One node in a binary tree (and the functions to support them).
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        BNode         : A class representing a BNode
 *    Additionally, it will contain a few functions working on Node
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once

#include <iostream>  // for OFSTREAM
#include <cassert>

/*****************************************************************
 * BNODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BNode
{
public:
   //
   // Construct
   //
   BNode()
   {
      pLeft = pRight = pParent = nullptr;
   }
   BNode(const T& t)
   {
      pLeft = pRight = pParent = nullptr;
       this-> data = data;
   }
    BNode(T&& t): data(std::move(t))
   {
      pLeft = pRight = pParent = nullptr;
       
   }

   //
   // Data
   //
   BNode <T>* pLeft;
   BNode <T>* pRight;
   BNode <T>* pParent;
   T data;
};

/*******************************************************************
 * SIZE BTREE
 * Return the size of a b-tree under the current node
 *******************************************************************/
template <class T>
inline size_t size(const BNode <T> * p)
{
   if (p == nullptr)
   {
       return 0;
   }
   else
   {
       return size(p->pLeft) + 1 + size(p->pRight);
   }
}


/******************************************************
 * ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <class T>
inline void addLeft(BNode <T> * pNode, BNode <T> * pAdd)
{
    pNode->pLeft = pAdd;
}

/******************************************************
 * ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <class T>
inline void addRight (BNode <T> * pNode, BNode <T> * pAdd)
{
    pNode->pRight = pAdd;
}

/******************************************************
 * ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <class T>
inline void addLeft (BNode <T> * pNode, const T & t)
{
    if (pNode->pLeft == nullptr)
    {
        pNode->pLeft = new BNode<T>;
        pNode->pLeft->data = t;
    }
    else
    {
        pNode->pLeft->data = t;
    }
}

template <class T>
inline void addLeft(BNode <T>* pNode, T && t)
{
    if (pNode->pLeft == nullptr)
    {
        pNode->pLeft = new BNode<T>;
        pNode->pLeft->data = t; //This needs a (std::move(t))
    }
    else
    {
        pNode->pLeft->data = t; //This needs a (std::move(t))
    }
}

/******************************************************
 * ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <class T>
void addRight (BNode <T> * pNode, const T & t)
{
    if (pNode->pRight == nullptr)
    {
        pNode->pRight = new BNode<T>;
        pNode->pRight->data = t;
    }
    else
    {
        pNode->pRight->data = t;
    }
}

template <class T>
void addRight(BNode <T>* pNode, T && t)
{
    if (pNode->pRight == nullptr)
    {
        pNode->pRight = new BNode<T>;
        pNode->pRight->data = t; //This needs a (std::move(t))
    }
    else
    {
        pNode->pRight->data = t; //This needs a (std::move(t))
    }
}

/*****************************************************
 * DELETE BINARY TREE
 * Delete all the nodes below pThis including pThis
 * using postfix traverse: LRV
 ****************************************************/
template <class T>
void clear(BNode <T> * & pThis) //this should be correct, but it dosen't raise the persentage at all
{
    if (pThis == nullptr)
    {
        return;
    }
    else
    {
        clear(pThis->pLeft);
        
        clear(pThis->pRight);
        
        delete pThis;
    }
}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
template <class T>
inline void swap(BNode <T>*& pLHS, BNode <T>*& pRHS)
{
    BNode<T>* potato;
    potato = pLHS;
    pLHS = pRHS;
    pRHS = potato;
}

/**********************************************
 * COPY BINARY TREE
 * Copy pSrc->pRight to pDest->pRight and
 * pSrc->pLeft onto pDest->pLeft
 *********************************************/
template <class T>
BNode <T> * copy(const BNode <T> * pSrc)
{
   return new BNode<T> ;
}

/**********************************************
 * assign
 * copy the values from pSrc onto pDest preserving
 * as many of the nodes as possible.
 *********************************************/
template <class T>
void assign(BNode <T> * & pDest, const BNode <T>* pSrc)
{
    //pDest = copy(pSrc); <- this should call the copy function
    pDest = pSrc; //<-this is the only thing that works rn
}
