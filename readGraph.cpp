#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <vector>

#include "readGraph.hpp"
using namespace std;
int readGraph(ifstream& fin, double**& matrix, string*& vLabels,string**& eLabels)
{
	int numVert;
	int numEdge;
	fin >> numVert;
	fin >> numEdge;
	matrix=new double*[numVert];
	vLabels= new string[numVert];
	eLabels= new string*[numVert];
	for (int i=0;i<numVert;i++)
	{
		fin>>vLabels[i];
		matrix[i]= new double[numVert];
		eLabels[i]=new string[numVert];
		for (int j=0;j<numVert;j++)
		{
			matrix[i][j]=numeric_limits<double>::infinity();
			eLabels[i][j]="";
			if(i==j)
			{
				matrix[i][j]=0;
			}
		}
		
	}
	for(int k=0;k<numEdge;k++)
	{
		int x;
		int y;
		double dist;
		string label;
		fin>>x;
		fin>>y;
		fin>>dist;
		fin>>label;
		matrix[x][y]=dist;
		eLabels[x][y]=label;
		}
	
	
	return numVert;
  
}
int readGraph(ifstream& fin, int**& adj, double**& weights,int*& lengths,string*& vLabels, string**& eLabels)
{
	int numVert;
	int numEdge;
	fin >> numVert;
	fin >> numEdge;
	
	adj=new int*[numVert];
	weights=new double*[numVert];
	eLabels=new string*[numVert];
	lengths= new int[numVert];
	vLabels=new string[numVert];
	vector<vector<int>> adjV(numVert);
	vector<vector<string>> eLabelV(numVert);
	vector<vector<double>> weightV(numVert);
	for (int i=0;i<numVert;i++) //O(v)
	{
		fin>>vLabels[i];
		lengths[i]=0;
		vector<int> adjA;
		vector<string> eLabelA;
		vector<double> weightA;
		adjV.push_back(adjA);
		eLabelV.push_back(eLabelA);
		weightV.push_back(weightA);
	}
	for(int j=0;j<numEdge;j++)//O(e)
	{
		int x;
		int y;
		double dist;
		string label;
		fin>>x;
		fin>>y;
		fin>>dist;
		fin>>label;
		adjV[x].push_back(y);
		weightV[x].push_back(dist);
		eLabelV[x].push_back(label);
		lengths[x]=lengths[x]+1;
	}
	
	//Set into the arrays
	for (int k=0;k<numVert;k++)
	{
		adj[k]=new int[lengths[k]];
		eLabels[k]= new string[lengths[k]];
		weights[k]=new double[lengths[k]];
		for (int l=0;l<lengths[k];l++)
		{
			adj[k][l]=adjV[k][l];
			eLabels[k][l]=eLabelV[k][l];
			weights[k][l]= weightV[k][l];
		}
		
	}
	
	
	return numVert; 
}
int readGraph(ifstream& fin, int**& edgeList, double*& weights,int& numEdges,string*& vLabels,string*& eLabels)
{
	int numVert;
	fin >> numVert;
	fin >> numEdges;
	
	edgeList=new int*[numEdges];
	weights=new double[numEdges];
	eLabels=new string[numEdges];
	vLabels=new string[numVert];
	
	for (int i=0;i<numVert;i++)
	{
		fin>>vLabels[i];
	}
	for(int k=0;k<numEdges;k++)
	{
		edgeList[k]= new int[2];
		int x;
		int y;
		fin>>x;
		fin>>y;
		edgeList[k][0]=x;
		edgeList[k][1]=y;
		fin>>weights[k];
		fin>>eLabels[k];
	}
	return numVert;
	
	
	
}
