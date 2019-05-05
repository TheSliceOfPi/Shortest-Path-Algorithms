#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fstream>
#include <cstdlib>
#include <iostream>

#include "shortestPath.hpp"
#include "readGraph.hpp"
#include "BinaryHeap.hpp"

using namespace std;

TEST_CASE("Testing shortestPath function")
{
  SECTION("Testing Matrix dijkstra")
    {
		ifstream fin("graph.txt");
		double** matrix;
		string* vLabels;
		string** eLabels;
		int test= readGraph(fin,matrix, vLabels, eLabels);
		double* dist;
		int* prev;
		int source=0;
		dijkstra(matrix,test,source,dist,prev);
		
		//Test min dist
		REQUIRE(dist[0]==0);
		REQUIRE(dist[1]==4.5);
		REQUIRE(dist[2]==10);
		REQUIRE(dist[3]==3.2);
		
		//Test prev
		REQUIRE(prev[0]==-1);
		REQUIRE(prev[1]==3);
		REQUIRE(prev[2]==1);
		REQUIRE(prev[3]==0);
      
    }
    SECTION("Testing getPath")
    {
		ifstream fin("graph.txt");
		double** matrix;
		string* vLabels;
		string** eLabels;
		int test= readGraph(fin,matrix, vLabels, eLabels);
		double* dist;
		int* prev;
		int source=0;
		dijkstra(matrix,test,source,dist,prev);
		/*int* path;
		REQUIRE(getPath(0,0,prev,path)==0);
		REQUIRE(getPath(0,1,prev,path)==1);
		REQUIRE(getPath(0,2,prev,path)==2);
		REQUIRE(getPath(0,3,prev,path)==0);
		
		dijkstra(matrix,test,2,dist,prev);
		REQUIRE(getPath(2,0,prev,path)==0);
		REQUIRE(getPath(2,1,prev,path)==1);
		REQUIRE(getPath(2,2,prev,path)==0);
		REQUIRE(getPath(2,3,prev,path)==0);*/
		
      
    }
    SECTION("Testing adj dijkstra")
    {
		ifstream fin("graph.txt");
		int** adj;
		double** weights;
		int* lengths;
		string* vLabels;
		string** eLabels;
		int test= readGraph(fin, adj,weights,lengths,vLabels, eLabels);
		double* dist;
		int* prev;
		int source=0;
		dijkstra(adj,weights,lengths,test,source,dist,prev);
		//Test min dist
		REQUIRE(dist[0]==0);
		REQUIRE(dist[1]==4.5);
		REQUIRE(dist[2]==10);
		REQUIRE(dist[3]==3.2);
		
		//Test prev
		REQUIRE(prev[0]==-1);
		REQUIRE(prev[1]==3);
		REQUIRE(prev[2]==1);
		REQUIRE(prev[3]==0);
      
		int* path;
		REQUIRE(getPath(0,0,prev,path)==1);
		REQUIRE(getPath(0,1,prev,path)==3);
		REQUIRE(getPath(0,2,prev,path)==4);
		REQUIRE(getPath(0,3,prev,path)==2);
		
		dijkstra(adj,weights,lengths,test,2,dist,prev);
		REQUIRE(getPath(2,0,prev,path)==2);
		REQUIRE(getPath(2,1,prev,path)==3);
		REQUIRE(getPath(2,2,prev,path)==1);
		REQUIRE(getPath(2,3,prev,path)==2);
		
    }
     SECTION("Testing BellFord Alg")
    {
		ifstream fin("graph2.txt");
		int** edgeList;
		double* weights;
		int numEdges;
		string* vLabels;
		string* eLabels;
		int numVert=readGraph(fin,edgeList,weights,numEdges,vLabels,eLabels);
		double* dist;
		int* prev;
		int cycled=bellmanFord(edgeList,weights,numVert,numEdges,0,dist,prev);
		REQUIRE(cycled==0);
		int* cycle;
		int numLoop=getCycle(cycled,prev,numVert,cycle);
		REQUIRE(numLoop==5);
    }
    SECTION("Testing Parallel Alg")
    {
		ifstream fin("graph.txt");
		double** graph;
		string* vLabels;
		string** eLabels;
		int numVertices= readGraph(fin,graph, vLabels, eLabels);
		double* dist;//=new double[numVertices];
		int*prev;//=new int[numVertices];
		int source=0;
		int numThreads=4;
		dijkstra(graph,numVertices, source, dist, prev, numThreads);
		//Test min dist
		REQUIRE(dist[0]==0.0);
		REQUIRE(dist[1]==4.5);
		REQUIRE(dist[2]==10);
		REQUIRE(dist[3]==3.2);
		
		//Test prev
		REQUIRE(prev[0]==NULL);
		REQUIRE(prev[1]==3);
		REQUIRE(prev[2]==1);
		REQUIRE(prev[3]==0);
    }
    
}
