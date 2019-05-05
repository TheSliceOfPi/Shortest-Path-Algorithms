#include <iostream>
#include <string>
#include <climits>
#include "BinaryHeap.hpp"
using namespace std;

BinaryHeap::BinaryHeap(const double* priorities, int numItems)
{	
	double* tempPrior=new double[numItems];
	heap= new int[numItems];
	positions=new int[numItems];
	membership=new bool[numItems];
	size=numItems;
	for(int i=0;i<numItems;i++)
	{
		heap[i]=i;
		positions[i]=i;
		membership[i]=true;
		tempPrior[i]=priorities[i];
	}
	this->priorities=tempPrior;
	tempPrior=0;
	delete[] tempPrior;
	
	for(int j=numItems-1;j>0;j--)
	{
		heapify(j);
	}
}
void BinaryHeap::heapify(int current)
{
	int parentPos=(current-1)/2;
	if(parentPos>=0 && priorities[heap[parentPos]]>priorities[heap[current]])
	{
		int tempCurNum=heap[current];
		int tempCurPos=current;
		int tempparentPosNum=heap[parentPos];
		int tempparentPos=parentPos;
		
		heap[current]=heap[parentPos];
		heap[parentPos]=tempCurNum;
		positions[tempCurNum]=tempparentPos;
		positions[tempparentPosNum]=tempCurPos;
		
		heapify(parentPos);
	}
}
BinaryHeap::~BinaryHeap()
{
	delete[] heap;
	delete[] priorities;
	delete[] membership;	
	delete[] positions;
}

int BinaryHeap::getMin() const
{
	return heap[0];
}
void BinaryHeap:: popMin()
{
		int min=heap[0];
		heap[0]=heap[size-1];
		positions[heap[0]]=0;
		positions[min]=size-1;
		membership[min]=false;
		size=size-1;
		perculateDown(0);
		
	
	
}
void BinaryHeap::perculateDown(int current)
{
	int smallPos;
	int LeftPos=(2*current)+1;
	int RightPos=(2*current)+2;
	if(LeftPos<=size-1 && priorities[heap[LeftPos]]<priorities[heap[current]])
	{
		smallPos=LeftPos;
	}
	else
	{
		smallPos=current;
	}
	if(RightPos<=size-1 && priorities[heap[RightPos]]<priorities[heap[smallPos]])
	{
		smallPos=RightPos;
	}
	if(smallPos!=current)
	{
		int tempCurNum=heap[current];
		int tempCurPos=current;
		int tempSmallPosNum=heap[smallPos];
		int tempSmallPos=smallPos;
		
		heap[current]=heap[smallPos];
		heap[smallPos]=tempCurNum;
		positions[tempCurNum]=tempSmallPos;
		positions[tempSmallPosNum]=tempCurPos;
		
		perculateDown(smallPos);
		
		
		
	}
}
bool BinaryHeap::contains(int item) const
{
	return membership[item];
}
double BinaryHeap::getPriority(int item) const
{
	return priorities[item];
}
void BinaryHeap::decreasePriority(int item, double newPriority)
{
	if(membership[item]==true && priorities[item]>newPriority)
	{ 
		priorities[item]=newPriority;
		heapify(positions[item]);
	}
	
}
int BinaryHeap::getSize() const
{
	return size;
}
int BinaryHeap::getItem(int pos) const
{
	return heap[pos];
	
	}
int BinaryHeap::getPos(int item) const
{
	return positions[item];
}
