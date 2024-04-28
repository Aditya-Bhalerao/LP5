#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

void printGraph(const vector<vector<int>> &adj_list)
{
    cout << "\nGraph:" << endl;
    for (int i = 1; i < adj_list.size(); ++i)
    {
        cout << "Vertex " << i << ": ";
        for (int j = 0; j < adj_list[i].size(); ++j)
        {
            cout << adj_list[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int num_vertices, num_edges, source;

    // Take user input for number of vertices, edges, and source vertex
    cout << "Enter the number of vertices: ";
    cin >> num_vertices;
    cout << "Enter the number of edges: ";
    cin >> num_edges;

    // Initialize adjacency list
    vector<vector<int>> adj_list(num_vertices + 1);

    // Take user input for adjacency list
    cout << "Enter the adjacency list:" << endl;
    for (int i = 0; i < num_edges; ++i)
    {
        int from, to;
        cout << "Enter edge " << i + 1 << ": ";
        cin >> from >> to;
        adj_list[from].push_back(to);
        // adj_list[to].push_back(from); // Uncomment this line to make it un-directed graph
    }

    cout << "Enter the source vertex: ";
    cin >> source;

    // Print the graph
    printGraph(adj_list);

    queue<int> q;
    vector<bool> visited(num_vertices + 1, false);

    q.push(source);
    visited[source] = true;

    while (!q.empty())
    {
        int curr_vertex = q.front();
        q.pop();

#pragma omp parallel for shared(adj_list, visited, q) schedule(dynamic)
        for (int i = 0; i < adj_list[curr_vertex].size(); i++)
        {
            int neighbour = adj_list[curr_vertex][i];
            if(!visited[neighbour]) 
            {
            #pragma omp critical
            {
                visited[neighbour] = true;
                q.push(neighbour);
            }
            }
        }
        cout << curr_vertex << " ";
    }

    cout << endl;

    return 0;
}
