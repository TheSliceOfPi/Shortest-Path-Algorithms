#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fstream>
#include <cstdlib>
#include <iostream>

#include "BinaryHeap.hpp"
using namespace std;

TEST_CASE("Testing createGraph function")
{
  SECTION("Testing createGraph")
    {
      int numItems=4;
      double* priorities=new double[numItems];
      priorities[0]=1.0;
      priorities[1]=0;
      priorities[2]=1.0;
      priorities[3]=2.0;
      BinaryHeap tree=BinaryHeap(priorities,numItems);
      REQUIRE(tree.getMin()==1);
      REQUIRE(tree.contains(3)==true);
      REQUIRE(tree.getPriority(2)==1.0);
      REQUIRE(tree.getSize()==4);
      REQUIRE(tree.getItem(0)==1);
      REQUIRE(tree.getPos(3)==3);
      tree.popMin();
      REQUIRE(tree.getMin()==0);
      REQUIRE(tree.contains(1)==false);
      REQUIRE(tree.getPriority(2)==1.0);
      REQUIRE(tree.getSize()==3);
      REQUIRE(tree.getItem(0)==0);
      REQUIRE(tree.getPos(0)==0);
      REQUIRE(tree.getPos(2)==2);
      REQUIRE(tree.getPos(3)==1);
      tree.decreasePriority(3,0);
      REQUIRE(tree.getItem(0)==3);
      REQUIRE(tree.getPos(0)==1);
      REQUIRE(tree.getPos(2)==2);
      REQUIRE(tree.getPos(3)==0);
      tree.popMin();
      REQUIRE(tree.getMin()==2);
      REQUIRE(tree.contains(1)==false);
      REQUIRE(tree.contains(3)==false);
      REQUIRE(tree.getPriority(2)==1.0);
      REQUIRE(tree.getSize()==2);
      REQUIRE(tree.getItem(0)==2);
      REQUIRE(tree.getPos(0)==1);
      REQUIRE(tree.getPos(2)==0);
      
      
      
      
      
    }
}
