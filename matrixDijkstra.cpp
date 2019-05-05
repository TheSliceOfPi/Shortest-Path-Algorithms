#include <iostream>
#include <fstream>
#include <chrono>
#include "shortestPath.hpp"
#include "readGraph.hpp"
#include "BinaryHeap.hpp"

using namespace std;
int main(int argc, char** argv)
{
	string input=argv[1];
	string output=argv[2]; 
	string sourceName=argv[3];
	string destName=argv[4];
	ifstream fin(input);
	double** matrix;
	string* vLabels;
	string** eLabels;
	int* prev;
	int* path;
	double* dist;
	int numVert= readGraph(fin,matrix, vLabels, eLabels);
	int source;
	int destination;
	for( int i=0;i<numVert;i++)
	{
		if(vLabels[i]==sourceName)
		{
			source=i;
		}
		if(vLabels[i]==destName)
		{
			destination=i;
		}
	}
	auto t1=chrono::system_clock::now();
	dijkstra(matrix,numVert,source,dist,prev);
	auto t2=chrono::system_clock::now();
	auto dur=t2-t1;
	auto durMS=chrono::duration_cast<chrono::microseconds>(dur);
	double elapsed=durMS.count();
	
	
	int totalPath=getPath(source,destination,prev,path);
	ofstream fout(output);
	fout<<numVert<<" "<<totalPath-1<<endl;
	for (int j=0;j<numVert;j++)
	{
		fout<<vLabels[j]<<endl;
	}
	
	for(int n=0;n<=totalPath-2;n++)
	{
		int v=path[n];
		int v2=path[n+1];
		fout<<v<<" "<<v2<<" "<<matrix[v][v2]<<" "<<eLabels[v][v2]<<endl;
	}
	cout<<"totalWeight is: "<<dist[destination]<<endl;
	cout<<"Dijkstra ran in: "<<elapsed<<"Ms"<<endl;
	delete[] matrix;
	delete[] vLabels;
	delete[] eLabels;
	delete[] prev;
	delete[] path;
	delete[] dist;
	
	
	
	
}
