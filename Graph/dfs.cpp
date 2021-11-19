/**
 * Depth First Search (DFS) is used to explore nodes and edges of a graph. It runs
 * with a time complexity of O(V+E) and is often used as a building block in other algorithms.
 * 
 * Application of DFS by augmenting it --
 * 
 * "Detect and find cycles in a graph"
 * -> Idea: For every visited vertex 'v', if there is an adjacent 'u' such that 'u'
 * is already visited and 'u' is not parent of 'v', there there is a cycle in graph.
 * 
 * "Check if a graph is bipartite"
 * -> Bipartite graphs are equivalent to two-colorable graphs i.e.,
 * coloring of the vertices using two colors in such a way that vertices
 * of the same color are never adjacent along an edge.
 * -> Also known as Bigraph such that you can divide the vertext set into 2 disjoint
 * sets such that (1) each vertext belongs to exactly one of the 2 sets; and
 * (2) each edge connects vertices of 2 different sets.
 * 
 * "Find strongly connected components"
 * Topologically sort the nodes of a graph
 * Find bridges and articulation points
 * Find augmenting paths in a flow network
 * Generate mazes
 * Compute a graph's MST
 * 
 * Last Edited on September 6, 2021 18:03:24 (CDT)
 */

#include <iostream>
#include <list>
#include <vector>
#include <stack>
using namespace std;

/*
 * Defining a class to store the grpah in the memory with nodes,
 * vertices, and edges. The data structure is selected as lists.
 */
class DepthFirstSearchAdjacencyList
{
    // Private members of the class
    private:
        int numNodes;
        list<int> *adjList;
        vector<bool> visitedNodes;
        vector<int> parent;
        vector<int> color;
        bool isCyclic;

    public:
        // Constructor that takes the number of nodes as a parameter
        DepthFirstSearchAdjacencyList(int n)
        {
            // The number of nodes in the graph
            numNodes = n;
            // Allocate resources for the list
            adjList = new list<int> [numNodes];
            // Assign all the elements of the visited vector with false
            visitedNodes.resize(numNodes, false);
            // Assign all the elements of the parent vector with -1
            // to show that it's not been explored before
            parent.resize(numNodes, -1);
            // Set the flag value with false
            isCyclic = false;
            // Assign all the colors to -1 first as a clear state
            // However, there will be only two colors: 0 and 1
            color.resize(numNodes, -1);
        }

        // Flush the trace
        void ClearVisitedTrace()
        {
            visitedNodes.clear();
            visitedNodes.resize(numNodes, false);

            parent.clear();
            parent.resize(numNodes, -1);

            color.clear();
            color.resize(numNodes, -1);
        }

        // Adding edge between the two nodes for the undirected graph
        void AddEdge(int src, int dst)
        {
            adjList[src].push_back(dst);
            //adjList[dst].push_back(src);
        }

        // Utility function to perform the DFS operation recursively
        void DfsRecursive(int at)
        {
            // Base condition -- already explored the node
            if (visitedNodes[at])
                return;

            // Visit the node
            visitedNodes[at] = true;
            cout << at << "\t";

            // Explore all the adjancent nodes
            for (auto& adjNode : adjList[at])
                DfsRecursive(adjNode);   // Recursive call
        }

        // Utility function to perform the DFS operation iteratively
        void DfsIterative(int at)
        {
            // A stack to maintain the adjancency nodes
            stack<int> adjNodes;
            // Make arrangements for the first 
            visitedNodes[at] = true;
            adjNodes.push(at);

            // Visit the nodes iteratively
            while(!adjNodes.empty())
            {
                // Point at the last inserted element
                at = adjNodes.top();
                adjNodes.pop();

                cout << at << "\t";
                // Explore all the adjancent nodes
                for (auto& adjNode : adjList[at])
                {
                    // Check if the node visited before
                    if(!visitedNodes[adjNode])
                    {
                        // Now visited
                        visitedNodes[adjNode] = true;
                        // Add the node to the stack
                        adjNodes.push(adjNode);
                    }
                }
            }
        }

        // Detect and find cycles in a graph
        void DetectCycle(int at)
        {
            // Mark the node as visited
            visitedNodes[at] = true;

            // Explore all the adjancent nodes
            for (auto& adjNode : adjList[at])
            {
                // If the node is NOT visited
                if(!visitedNodes[adjNode])
                {
                    // Assigned the parent for the adj node
                    parent[adjNode] = at;
                    // Perform the same operations for the adj node
                    DetectCycle(adjNode);
                }
                // visited AND the adj node isn't the parent of the at node
                else if(visitedNodes[adjNode] && parent[at] != adjNode)
                {
                    isCyclic = true;
                    return;
                }
                // Nothing, pass!
                else
                    continue;
            }
        }

        // An Utility to check if there's any cycle in the graph
        bool isCyclePresent(int src)
        {
            // Call the defined function to perform the task
            DetectCycle(src);
            return isCyclic;
        }

        // Check to see if a graph is bipartite
        bool isBipartite(int at, int c)
        {
            // Mark the node as visited
            visitedNodes[at] = 1;
            // Put the color to the node (either 0 or 1)
            color[at] = c;

            // Iterative scan each node to check the bipartite property
            for (int child : adjList[at])
            {
                // Check if the child is visited before
                if(visitedNodes[child] == false)
                {
                    // Visit the child node in a recursive approach
                    // If the substree rooted at the child node is not bipartite
                    // Return false; otherwise, continue with the operation
                    if(isBipartite(child, !c /*opposite color */) == false)
                        return false;
                }
                else // The child is visited before
                {
                    // Check if the colors are same
                    if(color[child] == color[at])
                    {
                        cout << "Two nodes are found connected in the same set.\n";
                        return false;
                    }
                }
            }
            return true;
        }

        // Free the allocated resources
        ~DepthFirstSearchAdjacencyList()
        {
            visitedNodes.clear();
            delete [] adjList;
        }
};

int main()
{
    /*
     * 0 ---- 3
     * | \
     * |  2 
     * | /  \
     * 1     4
     */

    DepthFirstSearchAdjacencyList dfs(5);
    dfs.AddEdge(0, 1);
    dfs.AddEdge(0, 2);
    dfs.AddEdge(0, 3);
    dfs.AddEdge(1, 2);
    dfs.AddEdge(2, 4);

    dfs.DfsRecursive(0);
    cout << endl;

    dfs.ClearVisitedTrace();

    dfs.DfsIterative(0);
    cout << endl;

    dfs.ClearVisitedTrace();
    if (dfs.isCyclePresent(0))
        cout << "Cycle detected" << endl;
    else
        cout << "No cycle found" << endl;

    dfs.ClearVisitedTrace();
    if (dfs.isBipartite(0, 0))
        cout << "The graph is bipartite." << endl;
    else
        cout << "The graph is NOT bipartite." << endl;

    return 0;
}
