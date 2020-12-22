/*
#include <iostream>
#include "sjf_btree.h"

using namespace std;

// constructor  initializes Root
BST::BST()
{
	Root = NULL;   // This is an empty tree
	total = 0;
}
// destructor must completely destroy the tree
BST::~BST()
{
	dtraverse(Root); // traverse to delete all vertices in post order
	Root = NULL;
}
// PURPOSE: Does Post Order traversal of the tree and deletes each vertex
// PARAM:   V is a pointer to the vertex to be deleted
void BST::dtraverse(Vertex* V)  // recursive post order traversal
{
	if (V != NULL)
	{
		dtraverse(V->Left);        //destroy left sub tree of V
		dtraverse(V->Right);       //destroy right sub tree of V
		delete V;                  //delete V
	}
}
// PURPOSE: Show vertices in IN order traversal from the Root
void BST::Display()
{
	INorderTraversal(Root);  // start in-order traversal from the root
}
// PURPOSE: Does IN order traversal from V recursively
// PARAM: V is te pointer to the vertex to visit right now
// For non EC (non-Extra Credit), the height and balance will always be 0 
void BST::INorderTraversal(Vertex* V)
{
	if (V != NULL)
	{
		INorderTraversal(V->Left);//traverse left sub-tree of V recursively
		if (V->count.size() == 0)
		{
			cout << "ID: " << V->Elem.name << " Priority: " << V->Elem.priority << endl;
		}
		else//duplicate values
		{
			cout << "ID: " << V->Elem.name << " Priority: " << V->Elem.priority << endl;
			for (int i = 0; i < V->count.size(); i++)
			{
				elem_t temp;
				temp = V->count.front();
				V->count.pop();
				V->count.push(temp);
				cout << "ID: " << temp.name << " Priority: " << temp.priority << endl;
			}

		}
		INorderTraversal(V->Right);//traverse right sub-tree of V recursively
	}
}
// PURPOSE: Searches for an element in PRE-order traversal
bool BST::Search(elem_t K)
{
	return PREorderSearch(Root, K);  // start pre-order traversal from the root
}
// PURPOSE: Does PRE order search from V recursively
// PARAM: V is the pointer to the vertex to be visited now
//        K is what we are looking for
bool BST::PREorderSearch(Vertex* V, elem_t K)
{
	if (V != NULL)
	{
		if (K.priority == V->Elem.priority)
			return true;					// found the element in V
		else if (K.priority < V->Elem.priority)
			PREorderSearch(V->Left, K);		//traverse left sub-tree of V recursively
		else
			PREorderSearch(V->Right, K);		//traverse right sub-tree of V recursively
	}
	else
	{
		return false;
	}
}
// ------ The following are for adding and deleting vertices -----

// PURPOSE: Adds a vertex to the binary search tree for a new element 
// PARAM: the new element E
// ALGORITHM: We will do this iteratively (not recursively)
// to demonstrate the algorithm that is in the notes
//    - smaller than the current -> go to the left
//    - bigger than the current  -> go to the right
//    - cannot go any further    -> add it there
void BST::InsertVertex(elem_t E)
{
	// Set up a new vertex first
	Vertex* N;         // N will point to the new vertex to be inserted
	N = new Vertex;    // a new vertex is created
	N->Left = NULL;   // make sure it does not
	N->Right = NULL;   // point to anything
	N->Elem = E;
	this->total++;		//increases the total
	N->Up = NULL;      // no parent for now

	if (Root == NULL)  // Special case: we have a brand new empty tree
	{
		Root = N;      // the new vertex is added as the root
		//cout << "...adding " << E.priority << " as the root" << endl;
	}// end of the special case
	else  // the tree is not empty
	{
		Vertex* V;       // V will point to the current vertex
		Vertex* Parent;  // Parent will point to V's parent

		V = Root;        // start with the root as V
		Parent = V->Up;
		//go down the tree until you cannot go any further        
		while (V != NULL)
		{
			if (N->Elem.burst == V->Elem.burst) // the element with the same priority already exists
			{
				V->count.push(N->Elem);
				return;
			}
			else
				if (N->Elem.burst < V->Elem.burst)  // what I have is smaller than V
				{
					//cout << "...going to the left" << endl;
					Parent = V;				//change Parent to be V to go down 
					V = V->Left;			//change V to be V's Left 
				}
				else // what I have is bigger than V
				{
					//cout << "...going to the right" << endl;
					Parent = V;			//change Parent to be V to go down
					V = V->Right;		//change V to be V's Right 
				}
		}//end of while

		 // reached NULL -- Must add N as the Parent's child

		if (N->Elem.burst < Parent->Elem.burst)
		{
			Parent->Left = N;		//Parent's Left should point to the same place as N 
			N->Up = Parent;			//N should point UP to the Parent 
			//cout << "...adding " << E.priority << " as the left child of " << Parent->Elem.priority << endl;
		}
		else
		{
			Parent->Right = N;		//Parent's Right should point to the same place as N 
			N->Up = Parent;			//N should point UP to the Parent 
			//cout << "...adding " << E.priority << " as the right child of " << Parent->Elem.priority << endl;
		}
	}// end of normal case
}// end of InsertVertex

 // PURPOSE: Deletes a vertex that has E as its element.
 // PARAM: element E to be removed
 // ALGORITHM: First we must find the vertex then call Remove
void BST::DeleteVertex(elem_t E)
{
	//cout << "Trying to delete " << E.priority << endl;
	Vertex* V;              // the current vertex
	Vertex* Parent = 0;

	// case 1: Lonely Root  
	if ((E.burst == Root->Elem.burst) && (Root->Left == NULL) && (Root->Right == NULL))
	{
		if (Root->count.size() > 0)
		{
			Root->Elem = Root->count.front();
			Root->count.pop();
			this->total--;
			return;
		}
		else
		{
			//cout << "...deleting the lonely root" << endl;
			this->total = 0;
			delete Root;
			Root = NULL;
			return;
		}
	}  // only the Root was there and deleted it

	   // case 2:  One Substree Root
	if (E.burst == Root->Elem.burst)//if what you want to delete is the root
	{
		if (Root->count.size() > 0)
		{
			Root->Elem = Root->count.front();
			Root->count.pop();
			this->total--;
			return;
		}
		else
		{
			if (Root->Left != NULL && Root->Right == NULL)//and it has only the left subtree
			{
				Root = Root->Left;			//change the root to the left child and return
				this->total--;
				return;
			}
			if (Root->Left == NULL && Root->Right != NULL)//and it has only the right subtree
			{
				Root = Root->Right;			//change the root to the right child and return
				this->total--;
				return;
			}
		}
	}// end of deleting the root with one subtree

	 // Otherwise deleting something else

	V = Root;  // start with the root to look for E

	// going down the tree looking for E
	while (V != NULL)
	{
		if (E.burst == V->Elem.burst)   // found it
		{
			if (V->count.size() > 0)	//deletes the duplicate value
			{
				V->Elem = V->count.front();

				V->count.pop();
				this->total--;
				return;
			}
			else
			{
				//cout << "...removing " << V->Elem.priority << endl;
				remove(V, Parent);//call remove here to remove V
				return;
			}
		}
		else
			if (E.burst < V->Elem.burst)
			{
				//cout << "...going to the left" << endl;
				Parent = V;		//update Parent and V here to go down 
				V = V->Left;
			}
			else
			{
				//cout << "...going to the right" << endl;
				Parent = V;		// update Parent and V here to go down
				V = V->Right;
			}
	}// end of while

	 // reached NULL  -- did not find it
	cout << "Did not find the key in the tree." << endl;
}// end of DeleteVertex

//increases the wait time of the PCB in ReadyQueue by one each time it is called
void BST::increaseWait()
{
	upWaitTime(Root);
}

void BST::upWaitTime(Vertex* V)
{
	if (V != NULL)
	{
		upWaitTime(V->Left);//traverse left sub-tree of V recursively
		if (V->count.size() == 0)
		{
			V->Elem.wait_time++;
		}
		else//duplicate values
		{
			V->Elem.wait_time++;
			for (int i = 0; i < V->count.size(); i++)
			{
				elem_t temp;
				temp = V->count.front();
				V->count.pop();
				temp.wait_time++;
				V->count.push(temp);
			}
		}
		upWaitTime(V->Right);//traverse right sub-tree of V recursively
	}
}

// PURPOSE: Removes vertex pointed to by V
// PARAM: V and its parent  pointer P
// Case 1: it is a leaf, delete it
// Case 2: it has just one child, bypass it
// Case 3: it has two children, replace it with the max of the left subtree
void BST::remove(Vertex* V, Vertex* P)
{
	this->total--;//reduce total of elements by one
	if (V->Left == NULL && V->Right == NULL)//if V is a leaf (case 1)
	{
		//cout << "removing a leaf" << endl;
		if (V == P->Left)		//if V is a left child of P
		{
			delete V;			//delete V and also make Parent's left NULL		
			P->Left = NULL;
		}
		else // V is a right child of the Parent
		{
			delete V;		//delete V and also make Parent's right NULL 
			P->Right = NULL;
		}
	}//end of leaf case
	else if (V->Left != NULL && V->Right == NULL) //if V has just the left child so bypass V (case 2)
	{
		//cout << "removing a vertex with just the left child" << endl;
		if (V->Elem.burst < P->Elem.burst)				//You need if then else to determine Parent's left or right
		{
			P->Left = V->Left;			//should point to V's left child; Make the left child
			V->Left->Up = P;				//point UP to the parent;
			delete V;					//Be sure to delete V
		}
		else
		{
			P->Right = V->Left;
			V->Left->Up = P;
		}
	}// end of V with left child       
	else if (V->Left == NULL && V->Right != NULL) //if V has just the right child so bypass V (case 2)
	{
		//cout << "removing a vertex with just the right child" << endl;
		if (V->Elem.burst < P->Elem.burst)			//You need if then else to determine Parent's left or right
		{
			P->Left = V->Right;		//should point to V's right child; make the right child
			V->Right->Up = P;		//point UP to the parent;
			delete V;				//Be sure to delete V
		}
		else
		{
			P->Right = V->Right;
			V->Right->Up = P;
			delete V;
		}
	}//end of V with right child
	else//(V->Left != NULL && V->Right != NULL) // V has two children (case 3)
	{
		//cout << "removing an internal vertex with children" << endl;
		//cout << "..find the MAX of its left sub-tree" << endl;
		elem_t Melem;
		// find MAX element in the left sub-tree of V
		Melem = findMax(V);
		cout << "..replacing " << V->Elem.burst << " with " << Melem.burst << endl;
		V->Elem.burst = Melem.burst;			//Replace V's element with Melem here
	}//end of V with two children
}// end of remove

//Finds the Maximum value in the Ready Queue
elem_t BST::findNext()
{
	Vertex* P = Root;
	while (P->Left != NULL)
	{
		P = P->Left;
	}
	//return P->Elem;
	if (P->count.size() > 0)//were sending a PCB with the same priority.
	{
		return P->Elem;
		//return P->count.front();
	}
	else
	{
		return P->Elem;
	}
}

// PURPOSE: Finds the first element in the left sub-tree of V
// and also deletes that vertex
elem_t BST::findMax(Vertex* V)
{
	Vertex* P = V;
	while (P->Left != NULL)
	{
		P = P->Right;
	}
	return P->Elem;
}// end of FindMax
*/