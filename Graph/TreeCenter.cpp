#include <iostream>
#include <queue>
#include <cstring>
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

int main()
{
    // Create the adjcancy list
    vector<int> adjList[7];

    AddEdge(adjList, 0, 1);
    AddEdge(adjList, 0, 2);
    AddEdge(adjList, 0, 5);
    AddEdge(adjList, 2, 3);
    AddEdge(adjList, 5, 4);
    AddEdge(adjList, 5, 6);

    /* Graph ->
        3 - 2 - 0 - 1
                |
            4 - 5 - 6
    */

    vector<int> treeCenter = FindTreeCenter(adjList, 7);
    // root will point at the center
    TreeNode* root = RootingTree(adjList, treeCenter[0]);

    /* Rooted tree ->
            0
        2   1   5
        3      4 6
    */

    // Display the tree level-wise
    PrintTree(root);
    // Display -> 0 2 1 5 3 4 6 (as per the tree above!)

    return 0;
}