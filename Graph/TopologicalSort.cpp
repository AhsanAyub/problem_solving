#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

int* FindTopologicalOrdering(vector<int> g[], int numNodes)
{
    // The topological ordering
    int *order = (int *) malloc(numNodes * sizeof(int));
    // In-degree counts
    int *inDegree = (int *) malloc(numNodes * sizeof(int));
    // Initialize all the elements to zero
    memset(inDegree, 0, sizeof(numNodes * sizeof(int)));
    //vector<int> inDegree(numNodes, 0);

    // Count the indegree
    for(int i = 0; i < numNodes; i++)
    {
        for(int at : g[i])
            inDegree[at] += 1;
    }

    // The queue will keep track of which node to remove
    // from the graph based on indegree counts
    queue<int> nodesQueue;
    // Scan the graph and update the first nodes to work with
    for(int i = 0; i < numNodes; i++)
    {
        if(inDegree[i] == 0)
            nodesQueue.push(i);
    }

    // The iterative approach to find the topological
    // sort using Khan's algorithm
    int index = 0;
    while(!nodesQueue.empty())
    {
        // Get the item
        int at = nodesQueue.front();
        nodesQueue.pop();
        order[index++] = at;
        // Explore its neighbors
        for(int item : g[at])
        {
            inDegree[item] -= 1;
            if(inDegree[item] == 0)
                nodesQueue.push(item);
        }
    }
    // Not a directed acyclic graph
    if(index != numNodes)
        return NULL;
    return order;
}

// Utility function to add an edge between two nodes
// u,v and v,u are conntected
void AddEdge(vector<int> adj[], int src, int dest)
{
    // For the directed graph
    adj[src].push_back(dest);
}

int main()
{
    // Create an adjcancy list
    vector<int> adjList[13];

    // Build the directed graph
    AddEdge(adjList, 9, 2);
    AddEdge(adjList, 9, 10);
    AddEdge(adjList, 2, 6);
    AddEdge(adjList, 10, 6);
    AddEdge(adjList, 0, 2);
    AddEdge(adjList, 0, 6);
    AddEdge(adjList, 0, 3);
    AddEdge(adjList, 6, 7);
    AddEdge(adjList, 6, 11);
    AddEdge(adjList, 3, 1);
    AddEdge(adjList, 3, 4);
    AddEdge(adjList, 7, 4);
    AddEdge(adjList, 7, 12);
    AddEdge(adjList, 1, 4);
    AddEdge(adjList, 4, 5);
    AddEdge(adjList, 4, 8);
    AddEdge(adjList, 12, 8);
    AddEdge(adjList, 11, 12);

    int *topologicalOrdering = FindTopologicalOrdering(adjList, 13);
    if(topologicalOrdering == NULL)
    {
        cerr << "The graph contains a cycle\n";
        return -1;
    }
    
    // Display the ordering
    cout << "Topological ordering\n";
    for(int i = 0; i < 13; i++)
        cout << topologicalOrdering[i] << " ";
    cout << endl;

    return 0;
}