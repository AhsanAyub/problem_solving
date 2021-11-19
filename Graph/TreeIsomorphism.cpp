#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

class TreeNode
{
    private:
        // The properties of the tree node
        int value;
        TreeNode *parent;
        vector<TreeNode*> children;

    public:
        // The default constructor
        TreeNode(int val)
        {
            value = val;
            parent = NULL;
        }

        // Return the value of the tree
        int GetValue()
        {
            return value;
        }
        
        // Adds a child to the node
        void AddChildren(TreeNode* node)
        {
            children.push_back(node);
        }

        // Returns all the children in a vector
        vector<TreeNode*> GetChildren()
        {
            return children;
        }

        // Sets the parent of the node
        void SetParent(TreeNode* p)
        {
            parent = p;
        }

        // Gets the parent of the node
        TreeNode* GetParent()
        {
            return parent;
        }
};

// DFS Routine to build the tree
TreeNode* BuildTree(vector<int> graph[], TreeNode* node)
{
    for(auto &childNode : graph[node->GetValue()])
    {
        // Ignore adding an edge pointing back to parent
        if(node->GetParent() != NULL && childNode == node->GetParent()->GetValue())
        {
            //cout << "Not Run: " << childNode << endl;
            continue;
        }

        // Creating the node to populate the tree
        TreeNode* child = new TreeNode(childNode);
        // Adding the built node as the child of its parent
        node->AddChildren(child);
        // Child node also stores the pointer to its parent
        child->SetParent(node);

        // Testing purpose
        //cout << "Insert: " << child->GetValue() << endl;

        // Recursive call to work with the child node
        BuildTree(graph, child);
    }
    
    // Eventually, node will be the root node
    return node;
}

// Utility function for the Rooting tree method
TreeNode* RootingTree(vector<int> graph[], int val)
{
    // Create the root the of the tree
    TreeNode* root = new TreeNode(val);
    // Invoke the DFS routine to build the tree for us
    return BuildTree(graph, root);
}

// Utility function to add an edge between two nodes
// u,v and v,u are conntected
void AddEdge(vector<int> adj[], int src, int dest)
{
    // For the undirected graph
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}

// Utility function to print the Rooting Tree
void PrintTree(TreeNode* root)
{
    // This queue will make sure that the nodes
    // are printed in order
    queue<TreeNode*> nodesQueue;

    // Push the root of the tree in the queue first
    nodesQueue.push(root);

    // This iterative approach will work 
    while(!(nodesQueue.empty()))
    {
        TreeNode* node = nodesQueue.front();
        nodesQueue.pop();
        cout << node->GetValue() << " ";
        
        for (auto& childNodes : node->GetChildren())
        {
            nodesQueue.push(childNodes);
        }
    }
    cout << endl;
}

// Utility function to derive the center for the tree based on degree
vector<int> FindTreeCenter(vector<int> graph[], int n)
{
    // This variable will count the number nodes are
    // pruned from the tree as leaves
    unsigned int count;
    int *degree = (int*) malloc(n * sizeof(int));
    // A much faster way than setting all the values by
    // running a loop. (as the function directly works on
    // a block of memory rather than an array element)
    memset(degree, 0, sizeof(n * sizeof(int)));
    // The 
    vector<int> leaves;

    // Update the degrees of the node in first iteration
    for(int i = 0; i < n; i++)
    {
        degree[i] = graph[i].size();
        // Check for leaves
        if(degree[i] == 0 || degree[i] == 1)
        {
            leaves.push_back(i);
            // Won't be used in the next
            degree[i] = 0;
        }
    }
    // Update the count variable of leaves
    count = leaves.size();

    // This iterative approach will scan the leave nodes
    // and then find out the new leave nodes
    while(count < n)
    {
        // To store the new leaves
        vector<int> newLeaves;
        for(auto& node : leaves)
        {
            for(auto& neighbors : graph[node])
            {
                degree[neighbors] -= 1;
                if(degree[neighbors] == 1)
                {
                    newLeaves.push_back(neighbors);
                }
            }
            degree[node] = 0;
        }
        // Update the count variable for the modified leaves
        count += newLeaves.size();
        // Be ready to work with the new layer
        leaves = newLeaves;
    }
    return leaves;  // This will return the center(s)
}

// This is the utility function that constructs the canonical form
// representation of a tree as a string (ref: AHU algorithm)
string encode(TreeNode* node)
{
    // Leaf node, only return ()
    if(node->GetChildren().empty())
    {
        return "()";
    }

    // The string labeles to be stored for each nodes
    vector<string> labels;
    // Explore all the childs and traverse back
    for(auto& childs : node->GetChildren())
    {
        // Recursive calls
        labels.push_back(encode(childs));
    }
    // Sort the string labels
    // For example, (()), (()()) -> (()()),(())
    sort(labels.begin(), labels.end());
    
    // The is the encoded string to be derived from the vector
    string encodedString = "";
    for(auto& str : labels)
    {
        encodedString += str;
    }
    encodedString = "(" + encodedString + ")";
    return encodedString;
}

// Utility function to check if two unrooted tree trees are isomorphic 
bool IsIsomorphic(vector<int> g1[], int n1, vector<int> g2[], int n2)
{
    // Find the centers of each graph
    vector<int> treeCenter1 = FindTreeCenter(g1, n1);
    vector<int> treeCenter2 = FindTreeCenter(g2, n2);

    // Build the tree with the 1st center of graph1
    TreeNode* root1 = RootingTree(g1, treeCenter1[0]);
    // Derive the encoded version for the 1st tree
    string tree1Enconding = encode(root1);

    // Check if the encoded version of 2nd tree matches with
    // the encoded version of the 1st tree
    for(auto& center : treeCenter2)
    {
        // Build the tree
        TreeNode* root2 = RootingTree(g2, center);
        // Derive the encoded version of the tree
        string tree2Encoding = encode(root2);

        // Return true if two strings are equal
        if(tree1Enconding.compare(tree2Encoding) == 0)
            return true;
    }
    // No match, return false -- not isomorphic
    return false;
}

int main()
{
    // Create the adjcancy lists for 2 graphs
    vector<int> graph1[6];
    vector<int> graph2[6];

    // Build the 1st graph
    AddEdge(graph1, 0, 1);
    AddEdge(graph1, 1, 2);
    AddEdge(graph1, 1, 4);
    AddEdge(graph1, 4, 3);
    AddEdge(graph1, 5, 3);
    /* Graph1 ->
        0   3 - 5
        |   |    
        1 - 4
        |
        2
    */

    // Build the 2nd graph
    AddEdge(graph2, 0, 1);
    AddEdge(graph2, 1, 2);
    AddEdge(graph2, 2, 4);
    AddEdge(graph2, 4, 3);
    AddEdge(graph2, 4, 5);
    /* Graph2 ->
                5
                |
            3 - 4
                |    
        0 - 1 - 2
    */


    /* Rooted tree ->
            0
        2   1   5
        3      4 6
    */

    // Display the tree level-wise
    //PrintTree(root);
    // Display -> 0 2 1 5 3 4 6 (as per the tree above!)

    if(IsIsomorphic(graph1, 6, graph2, 6))
        cout << "Isomorphic" << endl;
    else
        cout << "Not isomorphic" << endl;

    return 0;
}