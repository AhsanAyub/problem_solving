#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int iNumber;
	struct node *next;
}
node;

struct node *list = NULL;

// Print function of the linked list
void printLinkedList()
{
	if(list != NULL)
	{
		node *temp = list;
		while(temp != NULL)
		{
			printf("%i\t", temp->iNumber);
			temp = temp->next;
		}
		printf("\n");
	}
	else
		printf("Empty list\n");
}

// Reverse a linked list
void reverse()
{
	if(list == NULL)
	{
		printf("List is empty\n");
		return;
	}
	else
	{
		node *prev = NULL;
		node *current = list;
		node *next = NULL;

		while(current != NULL)
		{
			// Storing the next
			next = current->next;

			// Reverse the current node's pointer
			current->next = prev;

			// Move pointers one position ahead
			prev = current;
			current = next;
		}
		// Referencing the last item as starting item
		list = prev;
	}
	printLinkedList();
}

// Reverse printing of linked list
void reversePrintLinkedList(node *head)
{
	if(head == NULL)	// base condition
		return;
	reversePrintLinkedList(head->next);	// Recursive call
	printf("%i\t", head->iNumber);
}

// Utility function to remove an item
short delete(int iNum)
{
	// Check if there is item(s) in the list
	if(list == NULL)
		return 0;	// Fail to delete 

	// Checking the first item
	else if(list->iNumber == iNum)
	{
		node *temp = list->next;
		if(temp != NULL)	// 2nd item exists
			list->next = temp;
		else	// Only 1 item in the 
			list = NULL;
		return 1;
	}
	else
	{
		short flag = 0;
		node *current = list;		// Pointing at the 1st item
		node *temp = list->next;	// Pointing at the 2nd item
		while(temp != NULL)
		{
			if(temp->iNumber == iNum) // Item has been found
			{
				// Check whether this is the last item
				if(temp->next == NULL)
					current->next = NULL;
				else
				{
					temp = temp->next;
					current->next = temp;
				}
				flag = 1;
				break;
			}
			temp = temp->next;
			current = current->next;
		}
		return flag;
	}
}

// Utility function to search a node
short search(int iNum)
{
	node *temp = list;
	while(temp != NULL)
	{
		if(temp->iNumber == iNum)
			return 1;	// true
		temp = temp->next;
	}
	return 0;	// false
}

// Utility function to insert a node at the end
void insert(int iNum)
{
	// Create a new node
	node *n = malloc(sizeof(node));
	if (n == NULL)	// Something went wrong; checking for null
		return; // exit
	else	// Everything worked fine
	{
		n->iNumber = iNum;
		n->next = NULL;
	}
	if(list == NULL) // No other node exists
		list = n;
	else
	{
		node *temp = list;
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = n;
	}
}

// Utility function to insert a node at a location in sorted order
void sortedInsertion(int iNum)
{
	// Create a new node
	node *n = malloc(sizeof(node));
	if (n == NULL)	// Something went wrong; checking for null
		return; // return false
	else	// Everything worked fine
	{
		n->iNumber = iNum;
		n->next = NULL;
	}
	if(list == NULL) // No other node exists
		list = n;
	else if(list->next == NULL) // Only one item exists
	{
		if (iNum >= list->iNumber) // item is greater than 1st element
			list->next = n;
		else // item is less than 1st element
		{
			n->next = list;
			list = n;
		}
	}
	else // Multiple items exist
	{
		if(iNum <= list->iNumber) // Comparison of the first item
		{
			n->next = list;
			list = n;
		}

		else // Comparison from the second items onwards
		{
			short flag = 0;
			node *current = list; // Point at the first item
			node *temp = list->next; // temp : current -> next
			while(temp->next != NULL) // Comparison with 1st to n-1th location
			{
				if(iNum <= temp->iNumber)
				{
					n->next = temp;
					current->next = n;
					flag = 1;
					break;
				}
				current = current->next;
				temp = temp->next;
			} 
			if(!flag) // Last item need to check
			{
				if(iNum <= temp->iNumber) // Insert at last-1 index
				{
					n->next = temp;
					current->next = n;
				}
				else // Insert at last index
					temp->next = n;
			}
		}
	} 
}

// Driver program
int main()
{
	for (int i = 2; i <= 20; i += 2)
		sortedInsertion(i);
	
	// Print list
	printLinkedList();

	// Reverse the linked list
	printf("Reversing the list\n");
	reverse();

	// Reverse Print Linked List
	printf("Reverse printing of the list\n");
	reversePrintLinkedList(list);
	printf("\n");

	// Free list
	while(list != NULL)
	{
		node *temp = list->next;
		free(list);
		list = temp;
	} 

	return 0;
}