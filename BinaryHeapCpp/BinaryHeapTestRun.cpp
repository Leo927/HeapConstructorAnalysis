#include "BinaryHeapTestRun.h"
#include <algorithm>
#include <fstream>
void BinaryHeapTestRun::runExperiment(int size)
{
	ofstream output;
	output.open("report.csv", ofstream::out | ofstream::trunc);
	if (!output)
		abort();
	output << "Size, Lienar Ascending, Insert Ascending, Linear Descending, Insert Descending, Linear Random, Insert Random\n";
	LinearConstructor linearConstructor;
	InsertConstructor insertConstructor;
	CreateAscending ascendingInput;
	CreateDescending descendingInput;
	CreateRandom randomInput;
	const char COL_END =',';
	for (size_t i = 1; i < size; i*=2)
	{
		output << i << COL_END;
		output << getRunTime(i, linearConstructor, ascendingInput) << COL_END;
		output << getRunTime(i, insertConstructor, ascendingInput) << COL_END;
		output << getRunTime(i, linearConstructor, descendingInput) << COL_END;
		output << getRunTime(i, insertConstructor, descendingInput) << COL_END;
		output << getRunTime(i, linearConstructor, randomInput) << COL_END;
		output << getRunTime(i, insertConstructor, randomInput) << COL_END;
		output << endl;
		cout << "finished analysis for size = " << i << endl;
	}
	output.close();	
}
void BinaryHeapTestRun::constructOneByOne(vector<int>& input)
{
	BinaryHeap heap;
	for (int element: input)
	{
		heap.insert(element);
	}
}

void BinaryHeapTestRun::constructLinear(vector<int>& input)
{
	BinaryHeap heap(input);
}