#pragma once
#include <vector>
#include <iostream>
using namespace std;

class BinaryHeap
{
	struct Children
	{
		int left;
		int right;
		Children(int _left, int _right)
		{
			left = _left;
			right = _right;
		}
	};
private:
	vector<int> elements;
public:
	BinaryHeap(vector<int> _elements);
	BinaryHeap();
	void insert(int value);
	int deleteMin();
	int size();
private:
	int bubbleDown(int position, int value);
	void bubbleUp(int position);
	bool invariant(int position, int value);
	
	BinaryHeap::Children getChildren(int position);
	int getParent(int position);
	int getMinChild(int position);
};
