#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void findTriangles(vector<vector<int>>& graph) {
    int numVertices = graph.size();
    int count = 0;

    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            if (graph[i][j]) {
                for (int k = j + 1; k < numVertices; k++) {
                    if (graph[i][k] && graph[j][k]) {
                        cout << i << " -> " << j << " -> " << k << " -> " << i << endl;
                        count++;
                    }
                }
            }
        }
    }

    cout << "Total number of triangles: " << count << endl;
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

