#include <iostream>
#include <fstream>
#include <chrono>
#include "readGraph.hpp"
#include "shortestPath.hpp"

using namespace std;
int main(int argc, char** argv)
{
	string input=argv[1];
	string output=argv[2]; 
	string sourceName=argv[3];
	string destName=argv[4];
	ifstream fin(input);
	int** adj;
	double** weights;
	int* lengths;
	string* vLabels;
	string** eLabels;
	int numVertices= readGraph(fin, adj,weights,lengths,vLabels, eLabels);
	
	double* dist;
	int* prev;
	int* path;
	int source;
	int destination;
	for( int i=0;i<numVertices;i++)
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
	dijkstra(adj,weights, lengths,numVertices,source, dist, prev);
	auto t2=chrono::system_clock::now();
	auto dur=t2-t1;
	auto durMS=chrono::duration_cast<chrono::microseconds>(dur);
	double elapsed=durMS.count();
	
	int totalPath=getPath(source,destination,prev,path);
	ofstream fout(output);
	fout<<numVertices<<" "<<totalPath-1<<endl;
	
	for (int j=0;j<numVertices;j++)
	{
		fout<<vLabels[j]<<endl;
	}
	for(int n=0;n<=totalPath-2;n++)
	{
		int v=path[n];
		int v2=path[n+1];
		int idx;
		
		for (int q=0;q<lengths[v];q++)
		{
			if(adj[v][q]==v2)
			{
				idx=q;
				}
		}
	fout<<v<<" "<<v2<<" "<<weights[v][idx]<<" "<<eLabels[v][idx]<<endl;
	}
	cout<<"totalWeight is: "<<dist[destination]<<endl;
	cout<<"Dijkstra ran in: "<<elapsed<<"Ms"<<endl;
	delete[] adj;
	delete[] weights;
	delete[] lengths;
	delete[] vLabels;
	delete[] eLabels;
	delete[] dist;
	delete[] prev;
	delete[] path;
	
	
}
