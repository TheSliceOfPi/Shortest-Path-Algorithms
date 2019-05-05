#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fstream>
#include <cstdlib>
#include <iostream>

#include "readGraph.hpp"
using namespace std;

TEST_CASE("Testing readGraph function")
{
  SECTION("Testing readGraph")
    {
		
		ifstream fin("graph.txt");
		int** adj;
		double** weights;
		int* lengths;
		string* vLabels;
		string** eLabels;
		int numVert=readGraph(fin,adj,weights,lengths,vLabels,eLabels);
		REQUIRE(numVert==4);
		
		//Test adj
		REQUIRE(adj[0][0]==3);
		REQUIRE(adj[1][0]==2);
		REQUIRE(adj[2][1]==1);
		REQUIRE(adj[2][0]==0);
		REQUIRE(adj[2][2]==3);
		REQUIRE(adj[3][0]==1);
		//Test Weights
		REQUIRE(weights[0][0]==3.2);
		REQUIRE(weights[1][0]==5.5);
		REQUIRE(weights[2][0]==2.7);
		REQUIRE(weights[2][1]==5.5);
		REQUIRE(weights[2][2]==2.9);
		REQUIRE(weights[3][0]==1.3);
		
		//Test Lengths
		REQUIRE(lengths[0]==1);
		REQUIRE(lengths[1]==1);
		REQUIRE(lengths[2]==3);
		REQUIRE(lengths[3]==1);
		
		//Test eLabels
		REQUIRE(eLabels[0][0]=="MolassesSwamp");
		REQUIRE(eLabels[1][0]=="GumdropMountains");
		REQUIRE(eLabels[2][0]=="IceCreamSea");
		REQUIRE(eLabels[2][1]=="GumdropMountains");
		REQUIRE(eLabels[2][2]=="LollipopWoods");
		REQUIRE(eLabels[3][0]=="PeppermintForest");
		
		
		//Test vLabels
		REQUIRE(vLabels[0]=="GingerbreadPlumTrees");
		REQUIRE(vLabels[1]=="CandyCastle");
		REQUIRE(vLabels[2]=="LicoriceCastle");
		REQUIRE(vLabels[3]=="PeanutBrittleHouse");
    }
    SECTION("Testing readGraph Adj")
    {
		ifstream fin("graph.txt");
		double** matrix;
		string* vLabels;
		string** eLabels;
		int test= readGraph(fin,matrix, vLabels, eLabels);
		REQUIRE(test==4);
		//Test Matrix
		REQUIRE(matrix[0][0]==0);
		//REQUIRE(matrix[0][1]== inf);
		//REQUIRE(matrix[0][2]==inf);
		REQUIRE(matrix[0][3]==3.2);
		//REQUIRE(matrix[1][0]==inf);
		REQUIRE(matrix[1][1]==0);
		REQUIRE(matrix[1][2]==5.5);
		//REQUIRE(matrix[1][3]==inf);
		REQUIRE(matrix[2][0]==2.7);
		REQUIRE(matrix[2][1]==5.5);
		//REQUIRE(matrix[2][2]==inf);
		REQUIRE(matrix[2][3]==2.9);
		//REQUIRE(matrix[3][0]==inf);
		REQUIRE(matrix[3][1]==1.3);
		//REQUIRE(matrix[3][2]==inf);
		REQUIRE(matrix[3][3]==0);
		
		//Test eLabels
		REQUIRE(eLabels[0][0]=="");
		REQUIRE(eLabels[0][1]== "");
		REQUIRE(eLabels[0][2]=="");
		REQUIRE(eLabels[0][3]=="MolassesSwamp");
		REQUIRE(eLabels[1][0]=="");
		REQUIRE(eLabels[1][1]=="");
		REQUIRE(eLabels[1][2]=="GumdropMountains");
		REQUIRE(eLabels[1][3]=="");
		REQUIRE(eLabels[2][0]=="IceCreamSea");
		REQUIRE(eLabels[2][1]=="GumdropMountains");
		REQUIRE(eLabels[2][2]=="");
		REQUIRE(eLabels[2][3]=="LollipopWoods");
		REQUIRE(eLabels[3][0]=="");
		REQUIRE(eLabels[3][1]=="PeppermintForest");
		REQUIRE(eLabels[3][2]=="");
		REQUIRE(eLabels[3][3]=="");
		
		//Test vLabels
		REQUIRE(vLabels[0]=="GingerbreadPlumTrees");
		REQUIRE(vLabels[1]=="CandyCastle");
		REQUIRE(vLabels[2]=="LicoriceCastle");
		REQUIRE(vLabels[3]=="PeanutBrittleHouse");
      
    }
    SECTION("Testing readGraph BellFord")
    {
		
		ifstream fin("graph.txt");
		int** edgeList;
		double* weights;
		int numEdges;
		string* vLabels;
		string* eLabels;
		int numVert=readGraph(fin,edgeList,weights,numEdges,vLabels,eLabels);
		REQUIRE(numVert==4);
		
		//Test edgeList
		REQUIRE(edgeList[0][0]==0);
		REQUIRE(edgeList[0][1]==3);
		REQUIRE(edgeList[1][0]==1);
		REQUIRE(edgeList[1][1]==2);
		REQUIRE(edgeList[2][0]==2);
		REQUIRE(edgeList[2][1]==0);
		REQUIRE(edgeList[3][0]==2);
		REQUIRE(edgeList[3][1]==1);
		REQUIRE(edgeList[4][0]==2);
		REQUIRE(edgeList[4][1]==3);
		REQUIRE(edgeList[5][0]==3);
		REQUIRE(edgeList[5][1]==1);
		
		//Test Weights
		REQUIRE(weights[0]==3.2);
		REQUIRE(weights[1]==5.5);
		REQUIRE(weights[2]==2.7);
		REQUIRE(weights[3]==5.5);
		REQUIRE(weights[4]==2.9);
		REQUIRE(weights[5]==1.3);
		
		
		//Test eLabels
		REQUIRE(eLabels[0]=="MolassesSwamp");
		REQUIRE(eLabels[1]=="GumdropMountains");
		REQUIRE(eLabels[2]=="IceCreamSea");
		REQUIRE(eLabels[3]=="GumdropMountains");
		REQUIRE(eLabels[4]=="LollipopWoods");
		REQUIRE(eLabels[5]=="PeppermintForest");
		
		
		//Test vLabels
		REQUIRE(vLabels[0]=="GingerbreadPlumTrees");
		REQUIRE(vLabels[1]=="CandyCastle");
		REQUIRE(vLabels[2]=="LicoriceCastle");
		REQUIRE(vLabels[3]=="PeanutBrittleHouse");
    }
}
