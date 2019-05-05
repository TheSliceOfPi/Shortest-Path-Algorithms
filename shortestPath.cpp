#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <stack>
#include <vector>
#include <thread>

#include "readGraph.hpp"
#include "shortestPath.hpp"
#include "BinaryHeap.hpp"

using namespace std;
void dijkstra(const double* const * matrix, int numVertices, int source, double*& dist, int*&prev)
{
	
  dist=new double[numVertices];
  prev=new int[numVertices];
  bool inTree[numVertices];
  
  //Initialize all vertices
  for (int i=0;i<numVertices;i++)
    {
      dist[i]=numeric_limits<double>::infinity();
      prev[i]=-1;
      inTree[i]=false;
    }
  //add source into the tree
  inTree[source]=true;
  dist[source]=0;
	
  int n=source;
	
  for (int j=0;j<numVertices;j++)
    {
      for (int x=0;x<numVertices;x++)
	{
	  if(inTree[x]==false && (dist[n]+matrix[n][x])<dist[x])
	    {
	      dist[x]=dist[n]+matrix[n][x];
	      prev[x]=n;
				
	    }
	}
      double min= numeric_limits<double>::infinity();
      for(int h=0;h<numVertices;h++)
	{
	  if(inTree[h]==false && dist[h]<min)
	    {
	      n=h;
	      min=dist[h];
				
	    }
	}
      inTree[n]=true;
    }
}
int getPath(int source, int dest, const int* prev, int*& path)
{
  stack<int> pathStack;
  pathStack.push(dest);
  int acc=1;
  while(dest!=source)
    {
		
      dest=prev[dest];
      pathStack.push(dest);
      acc=acc+1;
    }
	
  path=new int[acc];
  for (int j=0;j<acc;j++)
    {
      int popped=pathStack.top();
      path[j]=popped;
      pathStack.pop();
		
    }
  return acc;
}
void dijkstra(const int* const * adj,const double* const * weights, const int* lengths,int numVertices, int source, double*& dist, int*&prev) //BinaryHeap
{
  dist=new double[numVertices];
  prev=new int[numVertices];
  bool inTree[numVertices];
  
  //Initialize all vertices
  for (int i=0;i<numVertices;i++)
    {
      dist[i]=numeric_limits<double>::infinity();
      prev[i]=-1;
      inTree[i]=false;
    }
    
    BinaryHeap tree=BinaryHeap(dist,numVertices); //Build Heap
  //add source into the tree
  tree.decreasePriority(source,0);
	
  int n=tree.getMin(); 
  tree.popMin();
  dist[n]=0;
  inTree[n]=true;
	
  for (int j=0;j<numVertices;j++)
    {
      for (int x=0;x<lengths[n];x++) 
	{
	  int adjNum=adj[n][x];
	  double weightEdge=weights[n][x];
	  if(inTree[adjNum]==false && dist[n]+weightEdge<tree.getPriority(adjNum))
	    {
	      tree.decreasePriority(adjNum,dist[n]+weightEdge);
	      prev[adjNum]=n;
				
	    }
	}
      n=tree.getMin();
      dist[n]=tree.getPriority(n);
      tree.popMin();
      inTree[n]=true;
    }
}
//Checkpoint 2
int bellmanFord(const int* const * edges, const double* weights, int numVertices, int numEdges, int source, double*& dist, int*& prev)
{
  dist= new double[numVertices];
  prev=new int[numVertices];
  int updated=-1;
	
  for(int i=0; i<numVertices;i++)
    {
      dist[i]=numeric_limits<double>::infinity();
      prev[i]=NULL;
    }
  dist[source]=0;
  for(int j=0;j<numVertices+1;j++)
    {
      for(int k=0;k<numEdges;k++)
	{
	  if(dist[edges[k][0]]+weights[k]<dist[edges[k][1]])
	    {
	      dist[edges[k][1]]=dist[edges[k][0]]+weights[k];
	      prev[edges[k][1]]=edges[k][0];
	    }
	}
    }
      for(int k=0;k<numEdges;k++)
	{
				
	  if(dist[edges[k][0]]+weights[k]<dist[edges[k][1]])
	    {
	      dist[edges[k][1]]=dist[edges[k][0]]+weights[k];
	      prev[edges[k][1]]=edges[k][0];
	      updated=edges[k][1];
	    }
	}
  return updated;
	
}

int getCycle(int vertex,const int* prev, int numVertices, int*& cycle)
{
  /*vector<int> cycleV;
  bool appear[numVertices];
  for(int i=0;i<numVertices;i++)
    {
      appear[i]=false;
    }
  int currentV=vertex;
  cycleV.push_back(currentV);
  while(appear[currentV]==false)
    {
      appear[currentV]=true;
      currentV=prev[currentV];
      cycleV.push_back(currentV);
    }
  int size=cycleV.size();
  cycle= new int[size];
  for(int k=0;k<size;k++)
    {
      cycle[k]=cycleV[size-1-k];
    }
  return size;*/
  
  vector<int> cycleV;
  bool appear[numVertices];
  bool appearCycle[numVertices];
  for(int i=0;i<numVertices;i++)
    {
      appear[i]=false;
      appearCycle[i]=false;
    }
  int currentV=vertex;
  while(appear[currentV]==false)
    {
      appear[currentV]=true;
      currentV=prev[currentV];
    }
    
    cycleV.push_back(currentV); //Add where the cycle began
    while(appearCycle[currentV]==false) //Add the rest of the cycle
    {
      appearCycle[currentV]=true;
      currentV=prev[currentV];
      cycleV.push_back(currentV);
    }
  int size=cycleV.size();
  cycle= new int[size];
  for(int k=0;k<size;k++)
    {
      cycle[k]=cycleV[size-1-k];
    }
  return size;
  
	
}

//Checkpoint3          
void dijkstra(const double* const * graph, int numVertices, int source, double*& dist, int*&prev,int numThreads)
{
	dist=new double[numVertices];
	prev=new int[numVertices];

  bool* inTree= new bool[numVertices];
  initialize(0,numVertices,dist,prev,inTree,numThreads);
  //add source into the tree
  dist[source]=0;
	for (int i=0;i<numVertices;i++)
	{
		double minDist=numeric_limits<double>::infinity();
		int minVertex=-1;
		int min=getMinVertex(0,numVertices,&minDist,&minVertex,dist,prev,inTree,numThreads);
		inTree[min]=true;
		updateDistance(graph,0,numVertices, dist, prev, inTree, numThreads,min);
		
	}
	delete[] inTree;
}
void initialize( int start, int end, double* dist, int* prev,bool* inTree,int numThreads)
{
  if(end == start + 1)
    {
      dist[start]=numeric_limits<double>::infinity();
      prev[start]=NULL;
      inTree[start]=false;
    }
  else
    {
      if(numThreads == 1)
	{
	  int midway = (start + end)/2;
	  initialize(start,midway,dist,prev,inTree,1);
	  initialize(midway,end,dist,prev,inTree,1);
	}
      else
	{
	  int halfNumThreads = numThreads/2;
	 
	  int mid = (end + start)/2; //The other way didnt work for 4 threads.
	  thread leftThread(initialize,start,mid,dist,prev,inTree,halfNumThreads);
	 
	  initialize(mid,end,dist,prev,inTree,numThreads-halfNumThreads);
	  leftThread.join();
	}
    }
}
int getMinVertex( int start, int end,double* minDist, int* minVertex, double* dist, int* prev,bool* inTree,int numThreads)
{
  if(end == start + 1)
  {
	  
	  if(dist[start]<*minDist && inTree[start]==false)
	  {
	*minVertex=start;
	*minDist=dist[start];
		
		}
		return *minVertex;
    }
  else
    {
      double leftMinDist=numeric_limits<double>::infinity();
      double rightMinDist=numeric_limits<double>::infinity();
      int leftMinVertex=-1;
      int rightMinVertex=-1;
      
      if(numThreads == 1) 
	{
	  int midway = (start + end)/2;
	  getMinVertex(start, midway,&leftMinDist, &leftMinVertex, dist,prev,inTree,1);
	  getMinVertex(midway,end,&rightMinDist, &rightMinVertex, dist,prev,inTree,1);
	}
      else
	{
	  int halfNumThreads = numThreads/2;
	  int mid = (start + end)/2;
	 
	  thread leftThread(getMinVertex,start, mid,&leftMinDist, &leftMinVertex, dist,prev,inTree,halfNumThreads);
	  getMinVertex(mid,end,&rightMinDist, &rightMinVertex, dist,prev,inTree,numThreads - halfNumThreads);
	 
	  leftThread.join();
	}	 
	
		
	  if(leftMinVertex!=-1 &&inTree[leftMinVertex]==false)
	  {
	  *minDist = dist[leftMinVertex];
	  *minVertex=leftMinVertex;
	  if(rightMinVertex!=-1 && dist[rightMinVertex] < dist[leftMinVertex]&& inTree[rightMinVertex]==false)
	{
	  *minDist = dist[rightMinVertex];
	  *minVertex=rightMinVertex;
	  
	}
	}
	 else if(rightMinVertex!=-1 &&dist[rightMinVertex]<*minDist && inTree[rightMinVertex]==false)
	{
	  *minDist = dist[rightMinVertex];
	  *minVertex=rightMinVertex;
	  
	}

	return *minVertex;
		  
	
    }
    
}
void updateDistance(const double* const * graph,int start, int end, double* dist, int* prev, bool* inTree, int numThreads,int adjV)
{
  if(end == start + 1)
    {
		if(inTree[start]==false && dist[start]>dist[adjV]+graph[adjV][start])
	   {
		   dist[start]=dist[adjV]+graph[adjV][start];
		   prev[start]=adjV;
		}
    }
  else
    {
      if(numThreads == 1)
	{
	  int midway = (start + end)/2;
	  updateDistance(graph,start,midway,dist,prev,inTree,1,adjV);
	  updateDistance(graph,midway,end,dist,prev,inTree,1,adjV);
	}
      else
	{
	  int halfNumThreads = numThreads/2;
	 
	  int mid = (end + start)/2; //The other way didnt work for 4 threads.
	  thread leftThread(updateDistance,graph,start,mid,dist,prev,inTree,halfNumThreads,adjV);
	 
	  updateDistance(graph,mid,end,dist,prev,inTree,numThreads-halfNumThreads,adjV);
	  leftThread.join();
	}
    }
	
	}

	

