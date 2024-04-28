#include <iostream>
#include <omp.h>
#include <vector>
#include <stack>

using namespace std;

void dfs(int startVertex, vector<bool>& visited, vector<vector<int>>& g)
{
    stack<int> stk;
    stk.push(startVertex);

    while (!stk.empty())
    {
        int vertex = stk.top();
        stk.pop();

        if (!visited[vertex])
        {
            cout << vertex << " ";
            visited[vertex] = true;

            #pragma omp parallel for
            for (int i = 0; i < g[vertex].size(); ++i)
            {
                #pragma omp critical
                {
                    int child = g[vertex][i];
                    stk.push(child);
                }
            }
        }
    }
}

int main()
{
    int vertices = 4;
    int edges = 3;
    int arr[] = {1, 3, 1, 2, 2, 4};

    vector<vector<int>> g(vertices + 1);
    vector<bool> visited(vertices + 1, false);

    for (int i = 0; i < 6; i = i + 2)
    {
        int v1 = arr[i];
        int v2 = arr[i + 1];
        g[v1].push_back(v2);
    }

    cout << "DFS: ";
    dfs(1, visited, g);

    return 0;
}
