#include <limits.h> 
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Número de vértices do grafo
#define V 48

int distanciaMinima(float dist[], bool sptSet[]) {
    float min = INT_MAX;
    int min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

void printPath(float parent[], int j) {
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);
    printf("%d ", j);
}

void imprimirResultados(float dist[], float parent[V]) {
    printf("Vertex\tDistancia\tCaminho");

    float src = 0.0;
    for (int i = 0; i < V; i++) {
        printf("\n%f -> %d \t %f\t\t%f ", src, i, dist[i], src);
        printPath(parent, i);
    }
}

void printResult(float dist[]) {
    printf("Vertex\tDistancia\n");

    for (int i = 0; i < V; i++) {
        printf("%d\t%f\n", i, dist[i]);
    }
}

void dijkstra(float grafo[V][V], int src) {
    float dist[V];
    bool sptSet[V];
    float parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0.0;
    parent[0] = -1;

    for (int i = 0; i < V - 1; i++) {
        int u = distanciaMinima(dist, sptSet);
 
        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && grafo[u][v] && dist[u] != INT_MAX &&
                dist[u] + grafo[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo[u][v];

                parent[v] = u;
            }   
        }
    }
    printResult(dist);
    //imprimirResultados(dist, parent);
}

vector<string> split(string text, string delimiter) {
    size_t pos = 0;
    vector<string> newArr;
    while ((pos = text.find(delimiter)) != string::npos) {
        newArr.push_back(text.substr(0, pos));
        text.erase(0, pos + delimiter.length());
    }
    newArr.push_back(text);
    return newArr;
}

void loadDataToArray(vector<vector<string>> &arr, string fileName) {
    ifstream inFile;
    inFile.open(fileName);

    if (!inFile) {
        cout << "Não foi possível abrir o arquivo";
        exit(1);
    }

    string fileLine;
    while (inFile >> fileLine) {
        arr.push_back(split(fileLine, ","));
    }

    inFile.close();
}

void createGraph(float (&graphAtt48)[V][V], vector<vector<string>> &cordn) {
    for (size_t i = 0; i < cordn.size(); i++) {

        for (size_t j = 0; j < cordn.size(); j++){
            int x = stoi(cordn[j][1]) - stoi(cordn[i][1]);
            int y = stoi(cordn[j][2]) - stoi(cordn[i][2]);
            float euclideanDistance = sqrt(pow(x, 2) + pow(y, 2));
            graphAtt48[i][j] = euclideanDistance;
        }
    }
}

int main() {
    vector<vector<string>> coordenates;
    float graphAtt48[V][V];

    string fileName = "databaseAtt48.txt";
    loadDataToArray(coordenates, fileName);

    createGraph(graphAtt48, coordenates);

    dijkstra(graphAtt48, 0);

    return 0;
}
