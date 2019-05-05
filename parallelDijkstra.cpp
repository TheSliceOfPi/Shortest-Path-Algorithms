#include <iostream>
#include <fstream>
#include <chrono>
#include "shortestPath.hpp"
#include "readGraph.hpp"

using namespace std;
int main(int argc, char** argv)
{
	string input=argv[1];
	string output=argv[2]; 
	string sourceName=argv[3];
	string destName=argv[4];
	int numThreads=atoi(argv[5]);
	
	
	ifstream fin(input);
	double** graph;
	string* vLabels;
	string** eLabels;
	int numVert= readGraph(fin,graph, vLabels, eLabels);
	double* dist;//=new double[numVert];
	int*prev;//=new int[numVert];
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
	
	
	auto start = chrono::system_clock::now();
   auto startCPU = clock();
   dijkstra(graph,numVert, source, dist, prev, numThreads);
   auto end = chrono::system_clock::now();
  auto endCPU = clock();
  auto dur = end - start;
  auto durCPU = endCPU - startCPU;
  auto durS = chrono::duration_cast<chrono::microseconds>(dur);
   long long serialTime = durS.count();
	
	int* path;
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
		fout<<v<<" "<<v2<<" "<<graph[v][v2]<<" "<<eLabels[v][v2]<<endl;
	}
	cout<<"Total Distance: "<<dist[destination]<<endl;
	cout<<"CPU time: "<< (durCPU)*(1000000/CLOCKS_PER_SEC)<<" microseconds"<<endl;
	cout<<"Wall clock time: "<< serialTime<<" microseconds"<<endl;
	
	delete[] graph;
	delete[] vLabels;
	delete[] eLabels;
	delete[] dist;
	delete[] prev;
	delete[] path;
	
	
	
	
}
