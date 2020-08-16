/*
 * Implementation of Queue in C++
 *
 * A queue implements FIFO (first-in first-out) ordering.
 * As in a line or queue at a ticket stand, items are removed
 * from the data structure in the same order that they are added.
 *
 * Following operations are included in the Queue -
 *
 * add(item): Add an item to the end of the list.
 * remove(): Remove the first item in the list.
 * peek() : Return the top of the queue.
 * isEmpty() : Return true if and only if the queue is empty.
 * display() : Display all the items in the queue
 * 
 * Last Edited on August 16, 2020 00:30:45 (CST)
 */

#include <iostream>

using namespace std;

// Defination of the node
struct Node
{
	int iNumber;		// Value of the Node
	struct Node *next;	// Pointer to point the next Node
};
Node *front = NULL;	// Responsible for deletion
Node *rear = NULL;	// Responsible for insertion

// Custom class for queue properties' implementation
class MyQueue
{
	public:
		// Utility function to return true if and only if the queue is empty
		short isEmpty()
		{
			return rear == NULL;
		}

		// Utility function to return the top of the queue
		int peek()
		{
			// Check whether or not the queue is empty
			if(isEmpty())
			{
				cout << "The queue is empty" << endl;
				exit(1);	// Exit from the function
			}
			else
				return rear->iNumber;
		}

		// Utility function to add an item to the end of the list
		void add(int iData)
		{
			// Creating the node
			struct Node *temp = new Node;
			temp->iNumber = iData;
			temp->next = NULL;

			// Check whether or not the queue is empty
			if (isEmpty())
			{
				rear = temp;
				front = temp;
			}
			else
			{
				/* Add the node to the queue with the help of rear.
				No need to change the front as it will point to the
				first inserted item to the queue. */
				rear->next = temp;
				rear = temp;
			}
		}

		// Utility function to remove the first item in the list
		int remove()
		{
			// Check whether or not the queue is empty
			if (isEmpty())
			{
				cout << "The queue is empty" << endl;
				exit(1);
			}
			else
			{
				// To return the value that's going to be popped out
				int iData = front->iNumber;

				// Initialize a temporary node to point the deleting node
				struct Node *temp = new Node;
				temp = front;

				// front will point to the next sequence item in the list
				front = front->next;
				free(temp); // deallocate the memory

				/* If front becomes null, then we will need to change the rear because
				the queue becomes empty. Hence, rear will also become null. */
				if(front == NULL)
					rear = NULL;

				return iData;
			}
		}

		// Utility function to display all the items in the queue
		void display()
		{
			// Check whether or not the queue is empty
			if(isEmpty())
			{
				cout << "The queue is empty" << endl;
				return;	// Exit from the function
			}
			else
			{
				// Initialize a temporary node to iterate through the list
				struct Node *temp = new Node;

				// Pointing to the front
				temp = front;

				while (temp != NULL)
				{
					cout << temp->iNumber << "\t";
					temp = temp->next;
				}
				cout << endl;
			}
		}
};

// Driver program
int main()
{
	MyQueue myQueue;
	
	myQueue.display();

	myQueue.add(10);
	myQueue.add(20);
	myQueue.add(30);
	myQueue.add(40);
	myQueue.add(50);
	myQueue.display();

	cout << myQueue.remove() << " is removed" << endl;
	cout << myQueue.remove() << " is removed" << endl;
	myQueue.display();

	cout << "Top element: " << myQueue.peek() << endl;
}