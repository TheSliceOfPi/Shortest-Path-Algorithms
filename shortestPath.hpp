#ifndef SHORTPATH
#define SHORTPATH
#include <limits>
using namespace std;

void dijkstra(const double* const * matrix, int numVertices, int source, double*& dist, int*&prev);
int getPath(int source, int dest, const int* prev, int*& path);

void dijkstra(const int* const * adj,const double* const * weights, const int* lengths,int numVertices, int source, double*& dist, int*&prev);

int bellmanFord(const int* const * edges, const double* weights, int numVertices, int numEdges, int source, double*& dist, int*& prev);

int getCycle(int vertex,const int* prev, int numVertices, int*& cycle);


void dijkstra(const double* const * graph, int numVertices, int source, double*& dist, int*& prev, int numThreads);
void initialize( int start, int end, double* dist, int* prev,bool* inTree,int numThreads);
int getMinVertex( int start, int end,double* minDist, int* minVertex, double* dist, int* prev,bool* inTree,int numThreads);
void updateDistance(const double* const * graph,int start, int end, double* dist, int* prev, bool* inTree, int numThreads,int adjV);

#endif
