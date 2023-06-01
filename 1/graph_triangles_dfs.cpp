#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void dfs(vector<vector<int>>& graph, vector<bool>& visited, int v, int depth, int start, vector<int>& path, int& triangleCount) {
    visited[v] = true;
    path.push_back(v);

    if (depth == 3) {
        for (int i = 0; i < graph[v].size(); i++) {
            if (graph[v][i] && i == start) {
                // Triangle found
                cout << "Triangle: ";
                for (int j = 0; j < 3; j++) {
                    cout << path[j] << " ";
                }
                cout << path[0] << endl;
                triangleCount++;
                break;
            }
        }
    } else {
        for (int i = 0; i < graph[v].size(); i++) {
            if (graph[v][i] && !visited[i]) {
                dfs(graph, visited, i, depth + 1, start, path, triangleCount);
            }
        }
    }

    visited[v] = false;
    path.pop_back();
}

void findTriangles(vector<vector<int>>& graph) {
    int numVertices = graph.size();
    vector<bool> visited(numVertices, false);
    vector<int> path;
    int triangleCount = 0;

    for (int i = 0; i < numVertices; i++) {
        dfs(graph, visited, i, 1, i, path, triangleCount);
    }

    cout << "Total number of triangles: " << triangleCount << endl;
}

int main() {
    ifstream inputFile("graph.txt");
    if (!inputFile) {
        cout << "Failed to open the input file." << endl;
        return 1;
    }

    int numVertices, numEdges;
    inputFile >> numVertices >> numEdges;

    vector<vector<int>> graph(numVertices, vector<int>(numVertices, 0));

    int src, dest;
    for (int i = 0; i < numEdges; i++) {
        inputFile >> src >> dest;
        graph[src][dest] = 1;
        graph[dest][src] = 1; // Assuming the graph is undirected
    }
    inputFile.close();

    findTriangles(graph);

    return 0;
}

