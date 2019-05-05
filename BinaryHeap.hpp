#ifndef BINARYHEAP
#define BINARYHEAP

#include <string>
#include <ostream>

using namespace std;

class BinaryHeap
{
  private:
	double* priorities;
	int* positions;
	int size;
	bool* membership;
	int* heap;
	
	
	void heapify(int current);
	void perculateDown(int current);
	

  public:
  BinaryHeap(const double* priorities, int numItems);
  ~BinaryHeap();
  int getMin() const;
  void popMin();
  bool contains(int item) const;
  double getPriority(int item) const;
  void decreasePriority(int item,double newPriority);
  int getSize() const;
  int getItem(int pos) const;
  int getPos(int item) const;
};
  

#endif
