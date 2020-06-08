/*
 * Implementation of the Doubly Linked List
 *
 * The code covers the basic operations, e.g.,
 * Insertion (at the front, after a given node,
 * at the end, and before a given node), Deletion
 * (At the front, in the middle, and at the end),
 * and Traversal (forward and backward).
 *
 * Last Edited on June 6, 2020 22:15:00 (CST)
 */

#include <stdio.h>
#include <stdlib.h>

// Defination of the list
typedef struct node
{
	int iNumber;	// Value of the node
	struct node *next;	// Pointer to point the next node
	struct node *prev;	// Pointer to point the prev node (the extra one)
}
node;

// Two ways to traverse the list
enum traversalStatus { forward, backward };

//Utility function for Traversal
void printDoublyList(struct node* head, enum traversalStatus tStatus)
{
	if(head != NULL)
	{
		node *temp = head; // Pointing at the head
		if(tStatus == 0) // Forward traversal
		{
			while(temp != NULL) 
			{
				printf("%d\t", temp->iNumber);
				temp = temp->next;
			}
			printf("\n");
		}
		else if (tStatus == 1) // Backward traversal
		{
			while(temp->next != NULL) // Traverse to the last node of the list
				temp = temp->next;

			while(temp != NULL) // Traverse backward while printing the nodes
			{
				printf("%d\t", temp->iNumber);
				temp = temp->prev;	
			}
			printf("\n");
		}
		else
			printf("Traversal status is unknown.\n");
	}
	else
		printf("Empty list\n");
}

// Four ways to insert a node in the list
enum insertionStatus {
	addAtFront, addAtAGivenNode, addBeforeAGivenNode, addAtEnd
};

//Utility function for Insertion
struct node* insertNode(int iValue, struct node* n, enum insertionStatus iStatus)
{
	node *temp = malloc(sizeof(node)); // Creating the node
	temp->iNumber = iValue; // Adding the value
	
	if(iStatus == 0)
	{
		printf("Adding a node (%d) at the front to the list\n", iValue);
		
		temp->next = n;	// New head
		temp->prev = NULL;

		// If the head is not null, then there is a small adjustment
		if(n != NULL)
			n->prev = temp;

		n = temp; // The main pointer will be pointing at the new head

		return n;
	}
	else if(iStatus == 1)
	{
		printf("Adding a node (%d) at a given node (%d) to the list\n", iValue, n->iNumber);

		if(n != NULL)
		{
			temp->next = n->next; // Pointing at the given node's next node
			n->next = temp; // The given node's next node is the new node
			temp->prev = n; // New node's previous node is the given node

			// If the new node's next is not null, we need to change that node's prev pointer
			if(temp->next != NULL)
				temp->next->prev = temp;
		}
	}
	else if(iStatus == 2)
	{
		printf("Adding a node (%d) before a given node (%d) to the list\n", iValue, n->iNumber);
		if(n != NULL)
		{
			temp->next = n; // New node points at the given node
			temp->prev = n->prev; // New node's previous node is the given node's previous node
			n->prev = temp; // Added the new node before the given node
			temp->prev->next = temp; // This change is needed as it was previously pointing at the given node
		}
	}
	else if(iStatus == 3)
	{
		printf("Adding a node (%d) at the end to the list\n", iValue);

		if(n != NULL)
		{
			node *last = malloc(sizeof(node)); // Creating the node to hold the last node
			last = n; // node n is the head, hence last is pointing at the head now
			
			while(last->next != NULL) // Traverse to the end node
				last = last->next;

			last->next = temp;	// last node's next node will be the new node
			temp->prev = last;	// new node's previous node will be the last node
			temp->next = NULL;	// new node's next node will be pointing at the null
		}
	}
	else
		printf("Insertion status is unknown\n");

	return NULL;
}

// Driver program
int main()
{
	struct node *doublyList = NULL;	// Considering the head of the list

	enum insertionStatus iStatus = addAtFront;
	doublyList = insertNode(3, doublyList, iStatus);
	doublyList = insertNode(2, doublyList, iStatus);
	doublyList = insertNode(1, doublyList, iStatus);
	// The list as of now is 1 -> 2 -> 3 -> null

	iStatus = addAtAGivenNode; // Changing the insertion status
	insertNode(1, doublyList->next, iStatus);
	// The list as of now is 1 -> 2 -> 1 -> 3 -> null

	iStatus = addAtEnd; // Changing the insertion status
	insertNode(20, doublyList, iStatus);
	insertNode(10, doublyList, iStatus);
	// The list as of now is 1 -> 2 -> 1 -> 3 -> 20 -> 10 -> null

	iStatus = addBeforeAGivenNode; // Changing the insertion status
	insertNode(15, doublyList->next->next->next, iStatus);
	// The list as of now is 1 -> 2 -> 1 -> 15 -> 3 -> 20 -> 10 -> null
	
	enum traversalStatus tStatus = forward;
	printDoublyList(doublyList, tStatus); // Prints forward

	// Free list
	while(doublyList != NULL)
	{
		node *temp = doublyList->next;
		free(doublyList);
		doublyList = temp;
	}

	return 0;
}