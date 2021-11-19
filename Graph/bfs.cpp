/**
 * Breadth First Search (BFS) is used to explore nodes and edges of a graph. It runs
 * with a time complexity of O(V+E) and is often used as a building block in other algorithms.
 * 
 * BFS is particularly useful for finding the "shortest path on unweighted graphs."
 * 
 * BFS, exploring in layers while maintaining a queue, starts at some arbitary node
 * of a graph and explores the neighbors at first before moving to the next level neighbors.
 * 
 * Last Edited on September 24, 2021 17:02:24 (CDT)
 */

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class BreadthFirstSearchAdjacencyList
{
    // Private members of the class
    private:
        int numNodes;
        // List containers are implemented as doubly-linked lists
        list<int> *adjList;
        vector<bool> visitedNodes;
        // This queue will track which node to visit next
        queue<int> nodeQueue;
        // This vector will keep track of the parent of the nodes
        vector<int> prev;
    public:
        // Constructor that takes the number of nodes as a parameter
        BreadthFirstSearchAdjacencyList(int n)
        {
            // The number of nodes in the graph
            numNodes = n;
            // Allocate resources for the list
            adjList = new list<int> [numNodes];
            // Assign all the elements of the visited vector with false
            visitedNodes.resize(numNodes, false);

            // Assign all the elements of the visited vector with false
            prev.resize(numNodes, -1);
        }

        // Adding edge between the two nodes for the undirected graph
        void AddEdge(int src, int dst)
        {
            adjList[src].push_back(dst);
        }

        /*
            A BFS starts at some arbitiary node of a graph and explores the neighbor
            nodes first before moving to the next level neighbors.
         */
        // Utility function to perform the DFS operation recursively
        void BfsIterative(int at)
        {
            // Mark the node as visited
            visitedNodes[at] = true;
            // Push the node to the queue
            nodeQueue.push(at);

            while(!(nodeQueue.empty()))
            {
                // Point to the last inserted item in the queue
                at = nodeQueue.front();
                nodeQueue.pop();

                // Print the node visited
                cout << at << " ";

                // Explore all the adjancent nodes
                for (auto& adjNode : adjList[at])
                {
                    // Check if the pointed node visited before
                    if(!visitedNodes[adjNode])
                    {
                        // Now visited
                        visitedNodes[adjNode] = true;
                        // Add the node to the stack
                        nodeQueue.push(adjNode);
                        // Mark the parent node
                        prev[adjNode] = at;
                    }
                } 
            }
            cout << endl;
        }

        void ShortestPath(int src, int dest)
        {
            vector<int> path;
            // Recontruction of the path by going backward from the destination    
            int at = dest;  // Point at the destination
            while(at != -1) // -1 denotes null or doesn't have any parent
            {
                path.push_back(at);
                at = prev[at];  // Going back
            }
            // Reverse the path
            reverse(path.begin(), path.end());

            // Check if src and dest are conntected, show the path
            if(path[0] == src)
            {
                for(int i = 0; i <= path.size()-1; i++)
                {
                    cout << path[i] << " ";
                }
                cout << endl;
            }
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

    BreadthFirstSearchAdjacencyList bfs(5);
    bfs.AddEdge(0, 1);
    bfs.AddEdge(0, 2);
    bfs.AddEdge(0, 3);
    bfs.AddEdge(1, 2);
    bfs.AddEdge(2, 4);
    bfs.AddEdge(4, 5);

    // Traverse the graph iterative following the following 
    bfs.BfsIterative(0);

    // Shortest path between the source and the destination
    bfs.ShortestPath(0, 4);
    
    return 0;
}