#include "BinaryHeap.h"

const static int root = 1;

BinaryHeap::BinaryHeap(vector<int> _elements)
{
	//leave 0 position open
	elements.push_back(NULL);

	for (int element : _elements)
	{
		elements.push_back(element);
	}

	for (size_t index = elements.size()/2; index > 0; index--)
	{
		bubbleDown(index, elements.at(index));
	}
}

BinaryHeap::BinaryHeap()
{
	elements.push_back(NULL);
}

void BinaryHeap::insert(int value)
{
	elements.push_back(value);
	bubbleUp(elements.size()-1);
}

int BinaryHeap::deleteMin()
{
	int result = elements.at(root);
	int insertPos = bubbleDown(root, elements.back());
	elements.at(insertPos) = elements.back();
	elements.pop_back();
	return result;
}

int BinaryHeap::size()
{
	return elements.size() - 1;
}

int BinaryHeap::bubbleDown(int position, int value)
{	
	if (invariant(position, value))
		return position;
	int minChild = getMinChild(position);
	swap(elements.at(minChild), elements.at(position));
	return bubbleDown(minChild, value);
}

void BinaryHeap::bubbleUp(int position)
{
	if (getParent(position) < 0) return;
	int parentValue = elements.at((int)getParent(position));

	if (parentValue > elements.at(position))
	{
		swap(elements.at(position), elements.at(getParent(position)));
		bubbleUp(getParent(position));
	}
}

bool BinaryHeap::invariant(int position, int value)
{
	Children children = getChildren(position);
	if (children.left >= 0 &&
		value > elements.at(children.left))
		return false;
	if (children.right >= 0 &&
		value > elements.at(children.right))
		return false;
	return true;
}

BinaryHeap::Children BinaryHeap::getChildren(int position)
{
	int left = position * 2;
	int right = position * 2 + 1;

	if (left >= elements.size()) left = -1;
	if (right >= elements.size()) right = -1;
	return Children(left, right);
}

int BinaryHeap::getParent(int position)
{
	return position / 2;
}

int BinaryHeap::getMinChild(int position)
{
	int minChild = -1;
	auto children = getChildren(position);
	if (children.left >= 0)
		minChild = children.left;
	if (children.right >= 0)
		if (elements.at(children.right) < elements.at(children.left)
			|| children.left < 0)
		{
			minChild = children.right;
		}
	return minChild;
}
