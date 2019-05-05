
Edith Flores
CPS222 Project 3

Files Submitted:
readGraph.hpp
readGraph.hpp
shortestPath.hpp
shortestPath.cpp
BinaryHeap.hpp
BinaryHeap.cpp
matrixDijkstra.cpp
listDijkstra.cpp
bellmanFord.cpp
currency.cpp
parallelDijkstra.cpp
mapqueue.cpp
readGraph_TEST.cpp
shortestPath_TEST.cpp
BinaryHeap_TEST.cpp
MakeFile
analysis.pdf
mapqueuefix.txt
readme.txt
Homework Cover Sheet Proj3.pdf


This project contains six main programs with many components.
The commans 'make' will compile the entire project.Alternatively, you may compile according to the directions below.

---matrixDijkstra---
To compile: make matrixDijkstra
To run:./matrixDijkstra <input file> <output file> <source vertex> <destination vertex>
Description:
matrixDijkstra determines the shortest path from the source vertex to the destination vertex using adjacency matrices. matrixDijkstra generates a file representing the shortest path and prints out the final weight and runtime on to the terminal.
Known issues:
-None that I know of.

---listDijkstra---
To compile: make listDijkstra
To run:./listDijkstra <input file> <output file> <source vertex> <destination vertex>
Description:
listDijkstra determines the shortest path from the source vertex to the destination vertex using adjacency lists and a Binary Heap. listDijkstra generates a file representing the shortest path and prints out the final weight and runtime on to the terminal.
Known issues:
-None that I know of.
---bellmanFord---
To compile: make bellmanFord
To run:./bellmanFord  <input file> <output file> <source vertex> <destination vertex>
Description:
bellmanFord determines the shortest path from the source vertex to the destination vertex if no negative cycle is found. However, if a cycle is found bellmanFord will determine the negative cycle.  bellmanFord then generates a file representing the shortest path, or cycle, and prints out whether a cycle was detected and the final weight and runtime on to the terminal.
Known issues:
-None that I know of.
---currency---
To compile: make currency
To run:./currency  <input file> <output file> <source currency> <destination currency> <transaction cost>
Description:
currency uses the BellmanFord algorithm to determine the best exchange rate between two given currencies. If not negative cycle is detected, currency should generate a file representing the best exchange sequence from the source currency to the destination currency and prints out the effective exchange rate on the terminal. If a negative cycle is detected, currency generate a file representing the cycle and prints out a warning of an Arbitrage Opportunity and prints out the effective exchange rate and runtime  on the terminal. 
Known issues:
-None that I know of.
---parallelDijkstra---
To compile: make parallelDijkstra
To run:./parallelDijkstra <input file> <output file> <source vertex> <destination vertex> <number of Threads>
Description:
parallelDijkstra determines the shortest path from the source vertex to the destination vertex using adjacency matrices, and implementing parallel programming. parallelDijkstra generates a file representing the shortest path and prints out the final weight,CPU time, and Wall clock time on to the terminal.
Known issues:
-None that I know of.
---mapqueue---
To compile: make mapqueue
To run:./mapqueue <number of servers>
Description:
mapqueue is a form of scheduler stimulation where one thread acts as a producer of jobs (creates jobs), and the rest of the thread acts as the consumers of the jobs (takes and does the jobs). mapqueue uses mutex in order to prevent threads from overlapping and having to deal with Race Condition.
Known issues:
-None that I know of.
