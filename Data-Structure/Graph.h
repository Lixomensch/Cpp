#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> *g; // Adjacency list
    
public:
    Graph(int V) {
        this->V = V;
        g = new vector<vector<int>>[V];
    }
    
    void addEdge_undirect(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    void addEdge(int u, int v) {
        g[u].push_back(v);
    }
    
    void BFS(int s) {
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;
        queue<int> q;
        visited[s] = true;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";
            for (int i = 0; i < g[u].size(); i++) {
                int v = g[u][i];
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }
    
    void DFS(int v) {
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;

        DFSUtil(v, visited);
    }

    void DFSUtil(int v, bool visited[]) {
        visited[v] = true;
        cout << v << " ";

        for (int i = 0; i < g[v].size(); i++) {
            int u = g[v][i];
            if (!visited[u]) {
                DFSUtil(u, visited);
            }
        }
    }

};
