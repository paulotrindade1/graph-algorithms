#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

#define V 48
#define INF 99999

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

void printSolution(float dist[][V], int src);
void floydWarshall(float graph[][V], int src)
{

	float dist[V][V];
	int i, j, k;

	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			dist[i][j] = graph[i][j];

	for (k = 0; k < V; k++)
	{
		for (i = 0; i < V; i++)
		{
			for (j = 0; j < V; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	printSolution(dist, src);
}

void printSolution(float dist[][V], int src)
{
	printf("The following matrix shows the shortest distances between every pair of vertices \n");
	printf("%f\n", dist[src][V - 1]);
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

void loadDataToArray(vector<vector<string>>& arr, string fileName) {
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

void createGraph(float(&graphAtt48)[V][V], vector<vector<string>>& cordn) {
	for (size_t i = 0; i < cordn.size(); i++) {

		for (size_t j = 0; j < cordn.size(); j++) {
			int x = stoi(cordn[j][0]) - stoi(cordn[i][0]);
			int y = stoi(cordn[j][1]) - stoi(cordn[i][1]);
			float euclideanDistance = sqrt(pow(x, 2) + pow(y, 2));
			graphAtt48[i][j] = euclideanDistance;
		}
	}
}

int main()
{
	vector<vector<string>> coordenates;
	float graphAtt48[V][V];

	string fileName = "databaseAtt48.txt";
	loadDataToArray(coordenates, fileName);

	createGraph(graphAtt48, coordenates);

	floydWarshall(graphAtt48, 0);

	return 0;
}
