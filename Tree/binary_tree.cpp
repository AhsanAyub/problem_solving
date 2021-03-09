/*
 * Implementation of a Binary Tree
 *      by following Binary Search Tree Structure
 *
 * The code covers the basic operations, e.g.,
 * Insertion (as per the binary search tree formation),
 * Lookup (search a "target" value), Deletion (Delete
 * a node from the tree following BST structure),
 * and Traversal (inorder, preorder, postorder, and level order).
 *
 * Other functionalites include:
 *      (1) size (count the number of the nodes in the tree)
 *      (2) maxDepth (computation of the number of the nodes along with the
 *          longest path from the root node down to the farthest leaf node)
 *      (3) maxValue (return the maximum value of the BST)     
 *      (4) minValue (return the minimum value of the BST)
 *      (5) isBST (check if the tree is a BST)
 * 
 * Last Edited on March 08, 2021 19:49:28 (CST)
 */

#include <iostream>
#include <queue>

using namespace std;

// Definition for a binary tree node
struct TreeNode
{
    int val;
    TreeNode* left;     // Left pointer
    TreeNode* right;    // Right pointer
};

/* This is the utility function to insert a node to the tree following
the structure of the binary search tree (BST). */
TreeNode* insert(TreeNode* root, int val)
{
    if(root == NULL)    // Empty tree (without root)
    {
        cout << "The tree is empty." << endl;
        return NULL;
    }
    else
    {
        // A temporary node to iterate through the tree
        struct TreeNode* temp = (struct TreeNode*) malloc(sizeof(struct TreeNode));
        temp = root;
        // An infite loop to locate the node from which the new node will be inserted
        bool positionLeft = true;
        while(true)
        {
            if (val <= temp->val)
            {
                if (temp->left != NULL) // Treverse left
                    temp = temp->left;
                else // Found the node, break
                {
                    positionLeft = true;
                    break;
                }    
            }
            else
            {
                if (temp->right != NULL) // Treverse right
                    temp = temp->right;
                else // Found the node, break
                {
                    positionLeft = false;
                    break;
                }
            }
        }
        /* Time for insertion */
        // Creating the new node to add it to the tree
        struct TreeNode* newNode = (struct TreeNode*) malloc(sizeof(struct TreeNode));
        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;

        // Connection to its parent
        if (positionLeft)
            temp->left = newNode;
        else
            temp->right = newNode;

        cout << "Insertion of " <<  val << " is done." << endl;
        free(temp); // Free the memory
    }

    return root; // The pointer has been unchanged throughout the operations
}

// This is the utility function to search and return the maximum value of the BST
TreeNode* maxValue(TreeNode* node)
{
    // Keep traversing to the right most side of the BST
    while(true)
    {
        if(node->right != NULL)
            node = node->right;
        else
            break;
    }
    return node;
}

// This is the utility function to search and return the minimum value of the BST
TreeNode* minValue(TreeNode* node)
{
    // Keep traversing to the left most side of the BST
    while(true)
    {
        if(node->left != NULL)
            node = node->left;
        else
            break;
    }
    return node;
}

// This is the utility function to print the preorder tree traversal
void printPreorder(TreeNode* root)
{
    // Recursive terminating condition
    if (root == NULL)
        return;
    
    cout << root->val << " ";    // Print value
    printPreorder(root->left);   // Left subtree traverse
    printPreorder(root->right);  // Right subtree traverse
}

// This is the utility function to print the inorder tree traversal
void printInorder(TreeNode* root)
{
    // Recursive terminating condition
    if (root == NULL)
        return;
    
    printInorder(root->left);   // Left subtree traverse
    cout << root->val << " ";   // Print value
    printInorder(root->right);  // Right subtree traverse
}

// This is the utility function to print the postorder tree traversal
void printPostorder(TreeNode* root)
{
    // Recursive terminating condition
    if (root == NULL)
        return;
    
    printPostorder(root->left);   // Left subtree traverse
    printPostorder(root->right);  // Right subtree traverse
    cout << root->val << " ";     // Print value
}

// This is the utility function to print the level order tree traversal
//TreeNode*  printLeverOrder(TreeNode* root)
void printLeverOrder(TreeNode* root)
{
    // Create a queue to insert the nodes left to explore
    queue<TreeNode*> nodeRecords;
    
    // A temporary node to iterate through the children of the node
    struct TreeNode* temp = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    nodeRecords.push(root);     // initialize the queue with the root
    
    // Begin with the root inside of the queue and finish when the queue is empty
    while(!nodeRecords.empty())
    {
        // Print the visited node that has traversed first
        cout << nodeRecords.front()->val << " ";
         
        temp = nodeRecords.front(); // Point at the node
        nodeRecords.pop();          // Remove from the queue as it's been printed

        // At each iteration, we add the left and right child of the current node
        if (temp->left != NULL)
            nodeRecords.push(temp->left);
        if (temp->right != NULL)
            nodeRecords.push(temp->right);
     }
}

// This is the utility function to compute the number of the nodes in the tree
int treeSize(TreeNode* root)
{
    if (root == NULL)   // Base condition
        return 0;
    else
        /* Traversing in both directions and for each node visited, we will
        get 1 returned for node visited. Hence, the root will return the sum of all the nodes. */
        return (treeSize(root->left) + treeSize(root->right) + 1);
}

/* Given a binary search tree and a "target" value, this function searches
the tree to see if it contains the target */
bool lookup(TreeNode* node, int target)
{
    if (node == NULL)               // Base condition
        return false;
    else if(node->val == target)    // Target is found
        return true;
    else                            // Keep exploring to find the target
    {
        if (node->val < target)         // Go left
            lookup(node->left, target);
        else if (node->val < target)    // Go right
            lookup(node->right, target);
    }
}

/*
    Delete a node from a binary search tree (BST) is done in two steps:
    - Find the element we wish to remove (if it exits)
    - Replace the node we want to remove with its successor (if any) to maintain
    the BST variant (which is the left subtree elements < the right subtree elements).
*/
TreeNode* deleteNode(TreeNode* root, int val)
{
    // Check if there is any node in the tree
    if(root == NULL)
    {
        cout << "The tree is empty." << endl;
        return NULL;
    }

    // Check if the tree has only root node
    if(root->left == NULL && root->right == NULL)
    {
        cout << "Only one node in the tree" << endl;
        root = NULL;
        return root;
    }

    struct TreeNode* targetNodeParent = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    struct TreeNode* targetNode = (struct TreeNode*) malloc(sizeof(struct TreeNode));

    // Assign both to the same point
    targetNode = root;
    targetNodeParent = root;

    bool isFound = false;   // A flag value to determine if the node is found

    // The loop to discover the target node as well as its parent for futher operations
    while(targetNode != NULL)
    {
        if (targetNode->val == val)
        {
            isFound = true;
            break;
        }
        else
        {
            targetNodeParent = targetNode;  // Assignment before traversing to the child node
            if(targetNode->val > val)
                targetNode = targetNode->left;
            else
                targetNode = targetNode->right;
        }
    }

    if(!isFound) return root;    // The target node is NOT found; no further operation is required.

    // Case 1: The target node is the leaf node
    if(targetNode->left == NULL && targetNode->right == NULL)
    {
        cout << "Case 1: The target node is the leaf node" << endl;
        if(targetNodeParent->left != NULL)
        {
            if(targetNodeParent->left->val == targetNode->val)  // Check if the child is in the left
            {
                targetNodeParent->left = NULL;
                return root;
            }
            if(targetNodeParent->right->val == targetNode->val)  // Check if the child is in the right
            {
                targetNodeParent->right = NULL;
                return root;
            }
        }
        else                                                // The child is in the right
            targetNodeParent->right = NULL;
    }
    // Case 2: The target node has either a left or a right subtree
    else if(targetNode->left == NULL || targetNode->right == NULL)
    {
        cout << "Case 2: The target node has either a left or a right subtree" << endl;
        // targetNode will point to its only child
        if(targetNodeParent->left->val == targetNode->val)
        {
            if(targetNode->left == NULL)
                targetNode = targetNode->right;
            else
                targetNode = targetNode->left;
            targetNodeParent->left = targetNode;            
        }
        else
        {
            if(targetNode->left == NULL)
                targetNode = targetNode->right;
            else
                targetNode = targetNode->left;
            targetNodeParent->right = targetNode; 
        }
    }
    // Case 3: Target node has both a left and a right subtree
    else
    {
        cout << "Case 3: Target node has both a left and a right subtree" << endl;
        // The successor can either be the largest value in the left subtree (this is implemented) 
        // or the smallest value in the right subtree.
        targetNodeParent = targetNode;              // No longer need to worry about the parent
        targetNode = maxValue(targetNode->left);    // find the larget value in the left subtree
        cout << "Swap Values: " << targetNodeParent->val << " " << targetNode->val << endl;
        targetNodeParent->val = targetNode->val;    // Assignment is done

        // Check if the left susbtree has only one node; then no need to do any recusive call
        if(targetNodeParent->left->left == NULL && targetNodeParent->left->right == NULL)
            targetNodeParent->left = NULL;
        else
            // Now, let's delete the node with this recusive call which value has just been swapped.
            deleteNode(targetNodeParent->left, targetNodeParent->val);
    }

    return root;
}


/* This is the utility function that leverages maxValue() and minValue() functions
 to check if the given tree obtains the BST property */
 bool isBST(TreeNode* node)
 {
    // Base condition
    if(node == NULL) return true;

    // The maximum value of the left subtree should not be more than the node value
    if(node->left != NULL && maxValue(node->left)->val > node->val)
        return false;

    // The minimum value of the right subtree should not be less than the node value
    if(node->right != NULL && minValue(node->right)->val < node->val)
        return false;

    // Call both subtrees to the left and right to check the same properties
    if(!isBST(node->left) || !isBST(node->right))
        return false;

    // Successfully passes all the checks
    return true;
 }

// Driver program
int main()
{
    // Creating the root node
    struct TreeNode* root = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    root->val = 7;
    root->left = NULL;
    root->right = NULL;

    cout << "Inserting the nodes." << endl;
    // Inserting some more nodes to the tree to get things started
    root = insert(root, 5);
    root = insert(root, 20);
    root = insert(root, 4);
    root = insert(root, 6);
    root = insert(root, 22);

    /*cout << root->left->left->val << endl;
    cout << root->left->right->val << endl;
    cout << root->right->val << endl;
    cout << root->val << endl;*/

    cout << "Preorder Traversal:\n";
    printPreorder(root);

    cout << "\nInorder Traversal:\n";
    printInorder(root);

    cout << "\nPostorder Traversal:\n";
    printPostorder(root);

    cout << "\nLevel Order Traversal:\n";
    printLeverOrder(root);

    cout << "\nTree Size: " << treeSize(root) << endl;

    if(lookup(root, 6))
        cout << "6 node exists" << endl;

    cout << "Max Value: " << maxValue(root)->val << endl;
    cout << "Min Value: " << minValue(root)->val << endl;

    if(isBST(root))
        cout << "The tree has the Binary Search Tree (BST) properties." << endl;
    else
        cout << "The tree does not have the Binary Search Tree (BST) properties." << endl;

    root = deleteNode(root, 7);
    printInorder(root);

    return 0;
}