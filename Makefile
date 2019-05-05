OPTS= -g -Wall -std=c++11 -pthread

all:  matrixDijkstra listDijkstra bellmanFord currency parallelDijkstra mapqueue

tests: shortestPath_TEST readGraph_TEST BinaryHeap_TEST

shortestPath.o: shortestPath.cpp shortestPath.hpp 
	g++ ${OPTS} -c shortestPath.cpp 
shortestPath_TEST: shortestPath_TEST.cpp shortestPath.o readGraph.o BinaryHeap.o catch.hpp 
	g++ ${OPTS} --coverage -o shortestPath_TEST shortestPath_TEST.cpp shortestPath.o readGraph.o BinaryHeap.o

matrixDijkstra: matrixDijkstra.cpp shortestPath.o readGraph.o BinaryHeap.o
	g++ ${OPTS} -o matrixDijkstra matrixDijkstra.cpp shortestPath.o readGraph.o BinaryHeap.o
	
	
readGraph.o: readGraph.cpp readGraph.hpp
	g++ ${OPTS} -c readGraph.cpp

readGraph_TEST: readGraph_TEST.cpp readGraph.o catch.hpp 
	g++ ${OPTS} --coverage -o readGraph_TEST readGraph_TEST.cpp readGraph.o

BinaryHeap.o: BinaryHeap.cpp BinaryHeap.hpp
	g++ ${OPTS} -c BinaryHeap.cpp

BinaryHeap_TEST: BinaryHeap_TEST.cpp BinaryHeap.o catch.hpp
	g++ ${OPTS} --coverage -o BinaryHeap_TEST BinaryHeap_TEST.cpp BinaryHeap.o
	
listDijkstra: listDijkstra.cpp shortestPath.o readGraph.o BinaryHeap.o
	g++ ${OPTS} -o listDijkstra listDijkstra.cpp shortestPath.o readGraph.o BinaryHeap.o
	
bellmanFord:bellmanFord.cpp shortestPath.o readGraph.o BinaryHeap.o
	g++ ${OPTS} -o bellmanFord bellmanFord.cpp shortestPath.o readGraph.o BinaryHeap.o
	
currency:currency.cpp shortestPath.o readGraph.o BinaryHeap.o
	g++ ${OPTS} -o currency currency.cpp shortestPath.o readGraph.o BinaryHeap.o
	
parallelDijkstra: parallelDijkstra.cpp shortestPath.o readGraph.o BinaryHeap.o
	g++ ${OPTS} -o parallelDijkstra parallelDijkstra.cpp shortestPath.o readGraph.o BinaryHeap.o

mapqueue:mapqueue.cpp 
	g++ ${OPTS} -o mapqueue mapqueue.cpp 
