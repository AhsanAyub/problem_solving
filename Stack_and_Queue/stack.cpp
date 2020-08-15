/*
 * Implementation of Stack in C++
 *
 * A stack uses LIFO (last-in first-out) ordering.
 * That is, as in a stack of dinner plates, the most recent
 * item added to the stack is the first item to be removed.
 *
 * Following operations are included in the Stack -
 *
 * pop() : Remove the top item from the stack.
 * push(item) : Add an item to the top of the stack.
 * peek() : Return the top of the stack.
 * isEmpty() : Return true if and only if the stack is empty.
 * display() : Display all the items in the stack
 * 
 * Last Edited on August 15, 2020 16:44:11 (CST)
 */

#include <iostream>

using namespace std;

// Defination of the node
struct Node
{
	int iNumber;		// Value of the Node
	struct Node *next;	// Pointer to point the next Node
};
Node *top = NULL;

class MyStack
{
	public:
		// Utility function to return true if and only if the stack is empty
		short isEmpty()
		{
			return top == NULL;
		}

		// Utility function to return the top of the stack
		int peek()
		{
			// Check whether or not the stack is empty
			if(isEmpty())
			{
				cout << "The stack is empty" << endl;
				exit(1);	// Exit from the function
			}
			else
				return top->iNumber;
		}

		// Utility function to add an item to the top of the stack
		void push(int iData)
		{
			// Creating the node
			struct Node *temp = new Node;

			// Adding the value
    		temp->iNumber = iData;

    		// Put the next pointer reference into temp
    		temp->next = top;

    		// Make temp as top of the stack
    		top = temp;

    		return;
		}

		// Utility function to remove the top item from the stack
		int pop()
		{
			// Check whether or not the stack is empty
			if(isEmpty())
			{
				cout << "The stack is empty" << endl;
				exit(1); // Exit from the function
			}
			// There is an item available to pop out
			else
			{
				// Initialize a temporary node
				struct Node *temp = new Node;

				// Pointing to the top so that the last-in node can be released
				temp = top;

				// Top will now point to the next node
				top = top->next;

				// Remove connection between the nodes
				temp->next = NULL;

				// Value to display
				int iData = temp->iNumber;

				// Free the memory
				free(temp);

				return iData;
			}
		}

		// Utility function to display all the items in the stack
		void display()
		{
			// Check whether or not the stack is empty
			if(isEmpty())
			{
				cout << "The stack is empty" << endl;
				return; // Exit from the function
			}
			else
			{
				// Initialize a temporary node to iterate through the list
				struct Node *temp = new Node;

				// Pointing to the top
				temp = top;

				while(temp != NULL)
				{
					cout << temp->iNumber << "\t";
					temp = temp->next;
				}
				cout << endl;
			}
		}
};

// Driver function
int main()
{
	MyStack myStack;
	
	myStack.display();

	myStack.push(10);
	myStack.push(20);
	myStack.push(30);
	myStack.push(40);
	myStack.push(50);
	myStack.display();

	myStack.pop();
	myStack.pop();
	myStack.display();

	cout << "Top element: " << myStack.peek() << endl;
}