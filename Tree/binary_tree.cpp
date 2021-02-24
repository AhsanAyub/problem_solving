/*
 * Implementation of a Binary Tree
 *      by following Binary Search Tree Structure
 *
 * The code covers the basic operations, e.g.,
 * Insertion (as per the binary search tree formation),
 * Lookup (search a "target" value), Deletion (Delete
 * a node from the tree following BST structure),
 * and Traversal (inorder, preorder, and postorder).
 *
 * Other functionalites include:
 *      (1) size (count the number of the nodes in the tree)
 *      (2) maxDepth (computation of the number of the nodes along with the
 *          longest path from the root node down to the farthest leaf node)
 *      (3) minValue (return the minimum value of the BST)
 *      (4) mirror (Roles of the left and right pointers are swapped at every node)
 *      (5) doubleTree (create a new duplicate node in a BST)
 *      (6) isBST (check if the tree is a BST)
 * 
 * Last Edited on February 08, 2021 00:00:00 (CST)
 */

#include <iostream>

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

// This is the utility function to compute the number of the nodes in the tree
int treeSize(TreeNode* root)
{
    if (root == NULL)   // Base condition
        return 0;
    else
        /* Traversing in both directions and for each node visited, we will
        get 1 returned. Hence, the root will return the sum of all the nodes. */
        return (treeSize(root->left) + treeSize(root->right) + 1);
}

/* Given a binary search tree and a "target" value, this function searches
the tree to see if it contains the target */
bool lookup(TreeNode* root, int target)
{
    if (root == NULL)   // Base condition
        return false;
    else
    {
        if (root->val == target) // Target is found
            return true;
        else // Keep exploring to find the target
        {
            if (root->val >= target)
                
        }
    }
}

// Driver program
int main()
{
    // Creating the root node
    struct TreeNode* root = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    root->val = 10;
    root->left = NULL;
    root->right = NULL;

    cout << "Inserting the nodes." << endl;
    // Inserting some more nodes to the tree to get things started
    root = insert(root, 5);
    root = insert(root, 1);
    root = insert(root, 15);

    /*cout << root->left->left->val << endl;
    cout << root->left->val << endl;
    cout << root->right->val << endl;
    cout << root->val << endl;*/

    cout << "Preorder Traversal:\n";
    printPreorder(root);

    cout << "\nInorder Traversal:\n";
    printInorder(root);

    cout << "\nPostorder Traversal:\n";
    printPostorder(root);

    cout << "\nTree Size: " << treeSize(root) << endl;

    return 0;
}