#pragma once
#include <chrono>
#include <ctime>
#include <ratio>
#include <iostream>
#include <vector>
#include "BinaryHeap.h"
using namespace std;
using namespace std::chrono;
static class BinaryHeapTestRun
{

public:
	static void runExperiment(int size);
private:
	template<typename Constructor, typename Input>
	static double getRunTime(int size, Constructor construct, Input inputFunction);
	static void constructOneByOne(vector<int> & input);
	static void constructLinear(vector<int> & input);
	struct LinearConstructor
	{
		void operator()(vector<int> input)
		{
			constructLinear(input);
		}
	};

	struct InsertConstructor
	{
		void operator()(vector<int> input)
		{
			constructOneByOne(input);
		}
	};

	struct CreateRandom
	{
		vector<int> operator()(int size)
		{
			vector<int> result;
			for (size_t i = 0; i < size; i++)
			{
				result.push_back(rand() % 10000);
			}
			return result;
		}
	};

	struct CreateAscending
	{
		vector<int> operator()(int size)
		{
			vector<int> result;
			for (size_t i = 0; i < size; i++)
			{
				result.push_back(i);
			}
			return result;
		}
	};

	struct CreateDescending
	{
		vector<int> operator()(int size)
		{
			vector<int> result;
			for (size_t i = 0; i < size; i++)
			{
				result.push_back(size - i + 1);
			}
			return result;
		}
	};
};
template<typename Constructor, typename Input>
inline double BinaryHeapTestRun::getRunTime(int size, Constructor construct, Input inputFunction)
{
	auto input = inputFunction(size);
	using namespace std::chrono;
	high_resolution_clock::time_point start = high_resolution_clock::now();
	construct(input);
	high_resolution_clock::time_point end = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(end - start);
	return time_span.count();
}
