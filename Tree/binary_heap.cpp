/*
 * Implementation of a Binary Heap
 *
 * A Binary Heap is a Binary Tree with following properties.
 *
 * 1) It’s a complete tree (All levels are completely filled except possibly
 * the last level and the last level has all keys as left as possible). This
 * property of the Binary Heap makes them suitable to be stored in an array.
 * 2) 2) A Binary Heap is either Min Heap or Max Heap. In a Min Binary Heap,
 * the key at root must be minimum among all keys present in Binary Heap.
 * The same property must be recursively true for all nodes in Binary Tree.
 * 
 * The root element will be at Arr[0].
 * Arr[(i-1)/2]	-> Returns the parent node
 * Arr[(2*i)+1]	-> Returns the left child node
 * Arr[(2*i)+2]	-> Returns the right child node
 * 
 * The code covers the basic operations of the Min Heap, e.g.,
 * getMIn() -- returns the root element of Min Heap. Time
 * Complexity of this operation is O(1); poll() --
 * removes the minimum element from MinHeap. Time Complexity
 * of this Operation is O(Logn); and insert(): Inserting a new
 * key takes O(Logn) time. We add a new key at the end of the tree.
 * 
 * Last Edited on June 25, 2021 15:20:45 (CDT)
 */

#include <iostream>

using namespace std;

/* The class of Min Heaps for integars */
class MinHeap
{
    private:
        int *MinHeapArray;  // The array that'll store the ints
        int Capacity;       // The capacity of the heap array
        int Size;           // The current size of the heap array

    public:
        // The constructor to build the array along with the size
        MinHeap(int iCapacity)
        {
            MinHeapArray = new int[iCapacity];  // Initialization
            Size = 0;   // No elements in the heap, hence the size is 0
            Capacity = iCapacity;   // The capacity of the array
        }

        // Return the index of the parent
        int getParentIndex(int ChildIndex)
        {
            return (ChildIndex - 1) / 2;
        }

        // Check if the key at the given index has parent
        bool hasParent(int index)
        {
            return getParentIndex(index) >= 0;
        }

        // Return the index of the parent's left child
        int getLeftChildIndex(int ParentIndex)
        {
            return ParentIndex * 2 + 1;
        }

        // Check if the key at the given index has left child
        bool hasLeftChild(int index)
        {
            return getLeftChildIndex(index) < Size;
        }

        // Return the index of the parent's right child
        int getRightChildIndex(int ParentIndex)
        {
            return ParentIndex * 2 + 2;
        }

        // Check if the key at the given index has right child
        bool hasRightChild(int index)
        {
            return getRightChildIndex(index) < Size;
        }

        // A utility function to swap two elements
        void swapHeapElements(int index1, int index2)
        {
            int temp = MinHeapArray[index1];
            MinHeapArray[index1] = MinHeapArray[index2];
            MinHeapArray[index2] = temp;
        }

        // Check if the heap is empty
        bool isEmpty()
        {
            return Size == 0 ? true : false;
        }

        // Check if the heap is full
        bool isFull()
        {
            return Size == Capacity ? true : false;
        }

        // Prints the minimum key in the heap array
        void getMin()
        {
            if(isEmpty())
                printf("The heap is empty.\n");
            else
                printf("The minimum key: %d\n", MinHeapArray[0]);
        }

        // Swap the elements up the heap
        void heapifyUp()
        {
            int index = Size - 1;   // Access the last inserted element

            while(hasParent(index) && MinHeapArray[getParentIndex(index)] > MinHeapArray[index])
            {
                swapHeapElements(getParentIndex(index), index);
                index = getParentIndex(index);
            }
        }

        // Swap the elements down the heap from a certain element
        void heapifyDown(int index)
        {
            while(hasLeftChild(index))
            {
                int SmallerChildIndex = getLeftChildIndex(index);
                
                if(hasRightChild(index) && MinHeapArray[getRightChildIndex(index)] < MinHeapArray[getLeftChildIndex(index)])
                    SmallerChildIndex = getRightChildIndex(index);
                
                if(MinHeapArray[index] < MinHeapArray[SmallerChildIndex])
                    break;
                else
                    swapHeapElements(index, SmallerChildIndex);
                    
                index = SmallerChildIndex;
            }
        }

        // Insert an element to the heap array
        void insert(int iValue)
        {
            if(isFull())
            {
                printf("THe heap is full, no more item can be inserted.\n");
                return;
            }

            // Insert the element at the bottom of the tree
            MinHeapArray[Size] = iValue;
            Size += 1;  // Add the size of the heap array

            // Maintain the heap structure by performing the heapify up method
            heapifyUp();
        }

        // Extract the root element from the element
        int poll()
        {
            if(isEmpty())
            {
                printf("The heap is empty. No item can be inserted.\n");
                printf("Exiting from the program\n");
            }
            
            // Store the root in the variable
            int root = MinHeapArray[0];
            // Assign the last node of the tree in the root
            MinHeapArray[0] = MinHeapArray[Size - 1];
            Size -= 1;  // Remove the last node from consideration

            // Maintain the heap structure by performing the heapify down method
            heapifyDown(0);
            // Return the variable
            return root;
        }

        // Print the elements of the heap array
        void printHeapArray()
        {
            if(isEmpty())
            {
                printf("The heap is empty.");
                return;
            }

            for (int i = 0; i < Size; i++)
                printf("%d\t", MinHeapArray[i]);
            printf("\n");
        }
};

// Driver program
int main()
{
    MinHeap MinHeapObj(10);
    
    MinHeapObj.insert(5);
    MinHeapObj.insert(10);
    MinHeapObj.insert(8);
    MinHeapObj.insert(3);
    MinHeapObj.insert(1);

    MinHeapObj.printHeapArray();

    MinHeapObj.poll();
    MinHeapObj.printHeapArray();

    MinHeapObj.getMin();

    return 0;
}