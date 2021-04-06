#### Search in a BST

Problem: [Link](https://leetcode.com/problems/search-in-a-binary-search-tree/)

```
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        // Base condition
        if(root == NULL || root->val == val)
            return root;
        
        if(val < root->val) // Traverse left
            return searchBST(root->left, val);
        else                // Traverse right
            return searchBST(root->right, val);
        
        return NULL;    // Not found, return NULL
    }
};
```

#### Validate BST

Problem: [Link](https://leetcode.com/problems/validate-binary-search-tree/)

```
class Solution {
public:
    // Returns true if the given tree is a BST and its values are >= min and <= max.
    bool isValidBSTUtil(TreeNode* node, long min, long max) {
        if (node==NULL) return true;
        
        // false if this node violates the min/max constraint
        if (node->val <= min || node->val >= max)
            return false;
        
        // otherwise check the subtrees recursively, tightening the min or max constraint
        return isValidBSTUtil(node->left, min, node->val) && isValidBSTUtil(node->right, node->val, max);
    }
    
    bool isValidBST(TreeNode* root) {
        // The tree is empty, and hence, return true
        if(root == NULL) return true;
        // Check if the tree is BST with the utility function
        // As the contraint says -2^31 <= Node.val <= 2^31 - 1, let's select long data type
        return (isValidBSTUtil(root, LONG_MIN, LONG_MAX));
    }
};
```

#### Diameter of Binary Tree

Problem: [Link](https://leetcode.com/problems/diameter-of-binary-tree/)

```
class Solution {
public:
    /*
        The diameter of a tree is the maximum sum of the depths of left and right subtrees among its nodes. So we can compute the depths of the left and right subtrees of each node (recursively) and use these depths to compute the diameter at the current node.
    */
    int depth(TreeNode* node, int &iDiameter)
    {
        if(node == NULL) return 0; // base condition
        // Compute the bredth of the left subtree
        int leftDepth = depth(node->left, iDiameter);
        // Compute the bredth of the right subtree
        int rightDepth = depth(node->right, iDiameter);
        iDiameter = max(iDiameter, leftDepth + rightDepth);
        return max(leftDepth, rightDepth) + 1;
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        int iDiameter = 0;
        depth(root, iDiameter);
        return iDiameter;
    }
};
```

#### Maximum Depth of Binary Tree

Problem: [Link](https://leetcode.com/problems/maximum-depth-of-binary-tree/)

```
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == NULL) return 0; // base condition
        // Compute the depth of the left subtree
        int leftDepth = maxDepth(root->left);
        // Compute the depth of the right subtree
        int rightDepth = maxDepth(root->right);
        // We care about the maximum value
        return max(leftDepth,rightDepth) + 1;
    }
};
```

#### Increasing Order Search Tree

Problem: [Link](https://leetcode.com/problems/increasing-order-search-tree/)

```
class Solution {
public:
    // This queue structure will store all the elements in the inorded traversal function
    queue<TreeNode*> nodesQueue;
    
    // The utility function to print the 
    void inOrderTraversal(TreeNode* root)
    {
        // Base condition
        if(root == NULL) return;
        inOrderTraversal(root->left);
        nodesQueue.push(root);  // Push it to the queue
        inOrderTraversal(root->right);
    }
    TreeNode* increasingBST(TreeNode* root)
    {
        // Condition to terminate further processes
        if(root == NULL) return NULL;
        
        // Call the inorder traversal funciton to add all the elements in a queue
        inOrderTraversal(root);
        // the modified root
        root = nodesQueue.front();
        root->left = NULL;
        root->right = NULL;
        nodesQueue.pop();   // First element is no longer required
        // Traverse through all the elements in the queue to add the new node in the tree as per requirement
        while(!nodesQueue.empty())
        {
            // Temporary pointer to point to the last connected node
            TreeNode* temp = root;
            
            // We care about only the right child
            while(temp->right != NULL)
                temp = temp->right;
                
            // Add the new node to the right child
            temp->right = nodesQueue.front();
            temp = temp->right;
            temp->left = NULL;
            temp->right = NULL;
            nodesQueue.pop();   // Remove from the queue
        }
        return root;
    }
};
```

#### Invert Binary Tree

Problem: [Link](https://leetcode.com/problems/invert-binary-tree/)

```
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        // base condition
        if (root == NULL) return NULL;
        
        // Scan through the subtrees
        struct TreeNode* rightSubtree;
        struct TreeNode* leftSubtree;
        rightSubtree = invertTree(root->right);
        leftSubtree = invertTree(root->left);
        
        // Swap the pointer in this node
        root->right = leftSubtree;
        root->left = rightSubtree;
        
        // Return the inverted binary tree's root 
        return root;
    }
};
```

#### Binary Search Tree Iterator

Problem: [Link](https://leetcode.com/problems/binary-search-tree-iterator/)

```
class BSTIterator {
    
private:
    queue<TreeNode*> nodesQueue;
    
public:
    BSTIterator(TreeNode* root)
    {
        // Only inorder traversal needs to perform all the tasks
        inorderTraversal(root);
    }
    
    void inorderTraversal(TreeNode* root)
    {
        // Base condition
        if (root == NULL) return;
        
        inorderTraversal(root->left);   // Visit the left subtree
        nodesQueue.push(root);          // Store it to the queue
        inorderTraversal(root->right);  // Visit the left subtree
    }
        
    int next()
    {
        if(!nodesQueue.empty())
        {
            // Fetch the val of the node
            int nodeValue = nodesQueue.front()->val;
            // Pop that value as it is no longer required anymore
            nodesQueue.pop();
            return nodeValue;   // Return the value
        }
        else    // Unlikely to happen, but given for i/o sanitization
            return -1;
    }
    
    bool hasNext() {
        // If the queue is not empty, it means there is there another node that can be visited
        if(!nodesQueue.empty())
            return true;
        return false;   // The queue is empty; hence, all the nodes have been visited
    }
};
```

#### Convert Sorted Array to Binary Search Tree

Problem: [Link](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/)

```
class Solution {
public:
    // This utility function constructs the BST from nums elements between indexes left and right
    TreeNode* BSTUtil(int leftIndex, int rightIndex, vector<int>& nums)
    {
        // Base condition: There is no elements available for that subtree
        if (leftIndex > rightIndex) return NULL;
        
        // Choose left middle node as a root
        int middleNodeIndex = (leftIndex + rightIndex) / 2;
            
        // Preorder traversal: node -> left -> right
        TreeNode* root = new TreeNode(nums[middleNodeIndex]);
        root->left = BSTUtil(leftIndex, middleNodeIndex-1, nums);
        root->right = BSTUtil(middleNodeIndex+1, rightIndex, nums);
        
        // This will return the original root of the tree
        return root;
    }
        
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // Only calling this utility function works
        return BSTUtil(0, nums.size()-1, nums);
    }
};
```

#### Convert Binary Search Tree to Sorted Doubly Linked List

Problem: [Link](https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/)

```
class Solution {
public:
    Node* first = NULL;     // This node will be pointing at the smallest node value
    Node* last = NULL;      // This node will be pointing at the largest (last) node
    
    // This is the utility function to scan all the nodes in the BST while making inorder traversal
    void inorderTraversal(Node* node)
    {
        // Base condition
        if (node == NULL) return;
        
        // Inorder traversal: left -> node -> right
        inorderTraversal(node->left);   // Go left
        
        // If not null, the last is going to point at the node that has got larger value
        if(last != NULL)
        {
            last->right = node;
            node->left = last;
        }
        else    // This will be true for the smallest item discovered on the left-most side of tree
            first = node;
        last = node;    // Change the last to point at the current node for the next recursive call
        
        inorderTraversal(node->right);  // Go right
    }
    
    Node* treeToDoublyList(Node* root)
    {
        // When the number of node is 0 in the BST
        if (root == NULL) return NULL;
        
        inorderTraversal(root);
        // Making the cyclic structure
        last->right = first;
        first->left = last;
        return first;
    }
};
```

#### Closest Binary Search Tree Value

Problem: [Link](https://leetcode.com/problems/closest-binary-search-tree-value/)

```
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int iNodeValue;
        double dDifference = DBL_MAX;
        
        // The loop will iterate through the BST to find the closest node value
        while(root != NULL)
        {
            if((double)root->val > target)
            {
                // Check the difference
                if(dDifference > ((double)root->val - target))
                {
                    dDifference = (double)root->val - target;
                    iNodeValue = root->val;
                }
                root = root->left;  // Go left
            }
            else if((double)root->val < target)
            {
                // Check the difference
                if(dDifference > (target - (double)root->val))
                {
                    dDifference = target - (double)root->val;
                    iNodeValue = root->val;
                }
                root = root->right; // Go right
            }
            else    // The target value is equal to the node
            {
                iNodeValue = root->val;
                break;  // As we are guaranteed to have only one unique value in the BST that is closest to the target.
            }
        }
        return iNodeValue;
    }
};
```

#### Binary Tree Paths

Problem: [Link](https://leetcode.com/problems/binary-tree-paths/)

```
class Solution {
public:
    void preOrderTraversal(TreeNode* root, string path, vector<string>&vBinaryTreePaths)
    {
        // Base condition
        if (root == NULL) return;
        
        // Add the node value to the path string
        path += to_string(root->val);
        
        // Leaf node -- add it to the vector
        if (root->left == NULL && root->right == NULL)
            vBinaryTreePaths.push_back(path); 
        else    // Continue appending to the path for the next node
            path += "->";
        
        // Go left
        preOrderTraversal(root->left, path, vBinaryTreePaths);
        // Go right
        preOrderTraversal(root->right, path, vBinaryTreePaths);
        
    }
    
    vector<string> binaryTreePaths(TreeNode* root) {
        // This vector container will store all the paths
        vector<string> vBinaryTreePaths;
        // Call this utility function
        preOrderTraversal(root, "", vBinaryTreePaths);
        // Returning the vector will work
        return vBinaryTreePaths;
    }
};
```