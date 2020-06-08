### Singly Linked List

Linked List is a special type of data structure, and its implementation can be found [here](https://github.com/AhsanAyub/problem_solving/blob/master/Linked_List/single_linked_list.c). The following sections discuss some of the problem topics with _a_ solution.

#### Reverse Linked List

The following code snippet written in C can be used for reversing a singly linked list -

```
Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* reverseList(struct ListNode* head){
    struct ListNode* prev = NULL;
    struct ListNode* current = head;
    struct ListNode* next = NULL;

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
    return prev;
}
```

#### Merge Two Sorted Lists

To merge two sorted linked lists and return it as a new sorted list, we may refer the following code snippet written in C -

```
Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
    if (l1 == NULL)	// l1 list is empty; hence, return l2
        return l2;
    else if(l2 == NULL)	// l2 list is empty; hence, return l1
        return l1;
    else
    {
    	/* Creating two nodes: one will point at the head,
    	the other one will point at the tail */
        struct ListNode* mergedList = NULL;
        struct ListNode* mergedListTail = NULL;
        
        while(1) // Infinite loop for insertion
        {
            if (l1 == NULL)	// Nothing left in l1 list
            {
                mergedListTail->next = l2;
                break;
            }
            else if (l2 == NULL) // Nothing left in l2 list
            {
                mergedListTail->next = l1;
                break;
            }
            else
            {
                if(l1->val <= l2->val)
                {
                    // Create a node
                    struct ListNode* temp = malloc(sizeof(struct ListNode));
                    temp->val = l1->val;
                    temp->next = NULL;
                                    
                    if(mergedList == NULL) // No node exists
                    {
                        mergedList = temp;
                        mergedListTail = mergedList;
                    }
                    else // Iterate through to find the right position
                    {
                        struct ListNode* tempNode = mergedList;
                        while(tempNode->next != NULL)
                            tempNode = tempNode->next;
                        tempNode->next = temp;
                        mergedListTail = temp;
                    }
                    
                    // delete the node from l1
                    temp = l1;
                    l1 = l1->next;
                    free(temp);
                }
                else
                {
                    // Create a node
                    struct ListNode* temp = malloc(sizeof(struct ListNode));
                    temp->val = l2->val;
                    temp->next = NULL;
                    
                    if(mergedList == NULL) // No node exists
                    {
                        mergedList = temp;
                        mergedListTail = mergedList;
                    }
                    else // Iterate through to find the right position
                    {
                        struct ListNode* tempNode = mergedList;
                        while(tempNode->next != NULL)
                            tempNode = tempNode->next;
                        tempNode->next = temp;
                        mergedListTail = temp;
                    }
                    
                    // delete the node from l1
                    temp = l2;
                    l2 = l2->next;
                    free(temp);
                }
            }
        }
        return mergedList;	// Return the head
    }
}
```

#### Linked List Cycle

Given a linked list, determine if it has a cycle in it. To represent a cycle in the given linked list, we use an integer `pos` which represents the position (0-indexed) in the linked list where tail connects to. If `pos` is `-1`, then there is no cycle in the linked list. Let's refer to the following code snippet written in C++ that uses STL -

```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    bool hasCycle(ListNode *head) {
        std::unordered_set<ListNode*> items; // Hash table
        struct ListNode *temp = head; // Iterator to iterate through the list
        
        while(temp != NULL)
        {
            if (items.find(temp) != items.end()) // node is found
                return true;
            else    // node is not found, insert the node to the vector
                items.insert(temp);
            
            temp = temp->next; // Point to the next node
        }
        // there is a node pointing at NULL; hence, the no cycle
        return false;
    }
};
```

#### Middle of the Linked List

Given a non-empty, singly linked list with head node head, return a middle node of linked list. If there are two middle nodes, return the second middle node. Let's refer to the following code snippet -

```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* middleNode(struct ListNode* head){
    // Two pointers
    struct ListNode* slow = head; // Slow and regular walk
    struct ListNode* fast = head; // Fast and maintain the desired distance with slow pointer


    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; // this will point to the middle node
}
```

#### Convert Binary Number in a Linked List to Integer

Given head which is a reference node to a singly-linked list. The value of each node in the linked list is either 0 or 1. The linked list holds the binary representation of a number. Return the decimal value of the number in the linked list. Let's refer to the following code snippet -

```
Input: head = [1,0,1]
Output: 5
Explanation: (101) in base 2 = (5) in base 10

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

int getDecimalValue(struct ListNode* head){
    int iDecimal = 0, iLengh = -1;
    struct ListNode* temp = head;
    
    while(temp != NULL) // This loop will count length of the given list
    {
        iLengh += 1;
        temp = temp->next;
    }
 
    while(head != NULL) // This loop will make the conversion
    {
        iDecimal += head->val * pow(2, iLengh); // binary to decimal conversion
        head = head->next; // Iterate to next node
        iLengh -= 1;
    }
    return iDecimal;
}
```

#### Palindrome Linked List

Given a singly linked list, determine if it is a palindrome. To achieve this task, let's refer to the following code snippet written in C++ that uses STL -

```
Input: 1->2->2->1
Output: true

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        struct ListNode *temp = head;
        if (temp == NULL) // No item in the list 
            return true; 
        
        std::vector<int> vList;
        
        // Build the vector to dynamically store the nodes' values
        while(temp != NULL)
        {
            vList.push_back(temp->val);
            temp = temp->next;
        }
        
        temp = head; // Back to pointing at the head of the list
        int iVectorSize = vList.size();
        int iLastIndex; // Last index to iterate and identify palindrome
        if(iVectorSize == 1) // Only one item in the list
            return true;
        else if(iVectorSize % 2 == 0) // Even
            iLastIndex = (iVectorSize / 2);
        else // Odd
            iLastIndex = (iVectorSize / 2) + 1;
        
        // Check the first half index w/ the last half index
        for(int i = iVectorSize - 1; i >= iLastIndex; i--)
        {
            if(temp->val != vList.at(i))
                return false;
            temp = temp->next;
        }

        // Deallocating memory
        vList.clear();

        return true; // Passed the screening
    }
};
```

#### Intersection of Two Linked Lists

Write a program to find the node at which the intersection of two singly linked lists begins [[example]](https://leetcode.com/problems/intersection-of-two-linked-lists/). Let's refer to the following code snippet written in C++ that uses STL -

```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        std::unordered_set<ListNode*> list;
        struct ListNode *l1 = headA;
        struct ListNode *l2 = headB;
        
        // Iterate through the first list
        while(l1 != NULL)
        {
            list.insert(l1);
            l1 = l1->next;
        }
        
        // Iterate through the first list
        while(l2 != NULL)
        {
            if(list.find(l2) != list.end()) // node is found
                return l2;
            l2 = l2->next;
        }
        return NULL;
    }
};
```