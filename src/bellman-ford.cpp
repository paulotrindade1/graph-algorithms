#include <climits>
#include <iostream>
#include <ctime>
#include <limits.h> 
#include <stdio.h>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

#define V 48
#define E 2304

void BellmanFord(float graph[E][3], int src)
{
	float dis[E];
	for (int i = 0; i < E; i++)
	{
		dis[i] = INT_MAX;
	}

	dis[src] = 0;

	for (int i = 0; i < E - 1; i++)
	{
		for (int j = 0; j < V; j++)
		{
			if (dis[(int)graph[j][0]] + graph[j][2] < dis[(int)graph[j][1]])
			{
				dis[(int)graph[j][1]] = dis[(int)graph[j][0]] + graph[j][2];
			}
		}
	}
 
	for (int i = 0; i < V; i++)
	{
		int x = graph[i][0];
		int y = graph[i][1];
		int weight = graph[i][2];
		if (dis[x] != INT_MAX && dis[x] + weight < dis[y])
		{
			printf("Graph contains negative weight cycle\n");
		}
	}

	printf("Vertex Distance from Source\n");
	for (int i = 0; i < V; i++)
	{
		printf("%d \t\t %f\n", i, dis[i]);
	}
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

void createGraph(float(&graph)[E][3], vector<vector<string>>& cordn)
{
	size_t cont = 0;
	for (size_t i = 0; i < cordn.size(); i++)
	{
		for (size_t j = 0; j < cordn.size(); j++)
		{
			int x = stoi(cordn[j][0]) - stoi(cordn[i][0]);
			int y = stoi(cordn[j][1]) - stoi(cordn[i][1]);
			float euclideanDistance = sqrt(pow(x, 2) + pow(y, 2));
			graph[cont][0] = i;
			graph[cont][1] = j;
			graph[cont][2] = euclideanDistance;
			cont++;
		}
	}
}

int main()
{
	vector<vector<string>> coordenates;
	float graph[E][3];

	string fileName = "databaseAtt48.txt";
	loadDataToArray(coordenates, fileName);

	createGraph(graph, coordenates);

	clock_t Ticks[2];
	Ticks[0] = clock();

	BellmanFord(graph, 0);

	Ticks[1] = clock();
	double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
	printf("\nTempo gasto: %f ms.", Tempo);

	return 0;
}
