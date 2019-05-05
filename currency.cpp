#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
#include "readGraph.hpp"
#include "shortestPath.hpp"

using namespace std;
int main(int argc, char** argv)
{
	string input=argv[1];
	string output=argv[2]; 
	string sourceName=argv[3];
	string destName=argv[4];
	float transCost=atof(argv[5]);
	
	ifstream fin(input);
	int** edgeList;
	double* weights;
	int numEdges;
	string* vLabels;
	string* eLabels;
	
	int numVertices= readGraph(fin,edgeList,weights,numEdges,vLabels,eLabels);
	
	for (int q=0;q<numEdges; q++)
	{
		weights[q]=-log(weights[q]*(1-transCost));
		
	}
	double* dist;
	int* prev;
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
	int vertex=bellmanFord(edgeList,weights,numVertices,numEdges,source,dist,prev);
	auto t2=chrono::system_clock::now();
	auto dur=t2-t1;
	auto durMS=chrono::duration_cast<chrono::microseconds>(dur);
	double elapsed=durMS.count();
	int* cycle;
	int totalPath;
	if(vertex!=-1)
	{
		cout<<"Arbitrage Opportunity Detected!"<<endl; 
		totalPath=getCycle(vertex,prev,numVertices,cycle);
		
	}
	else
	{
		totalPath=getPath(source,destination,prev,cycle);
		
	}
	ofstream fout(output);
	fout<<numVertices<<" "<<totalPath-1<<endl;
	for (int j=0;j<numVertices;j++)
	{
		fout<<vLabels[j]<<endl;
	}
	double weightT=0;
	for(int n=0;n<totalPath-1;n++)
	{
		int v=cycle[n];
		int v2=cycle[n+1];
		int loc=-1;
		for(int k=0;k<numEdges;k++)
		{
			if(edgeList[k][0]==v && edgeList[k][1]==v2)
			{
				loc=k;
			}
		}
		weightT=weightT+weights[loc];
	fout<<v<<" "<<v2<<" "<<exp(-weights[loc])<<" "<<eLabels[loc]<<endl;
}
	cout<<"Effective Exchange Rate: "<<exp(-weightT)<<endl;
	cout<<"RunTime: "<< elapsed <<"Ms"<<endl;
	
	

}
