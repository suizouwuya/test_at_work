/*
 * HeapTest.cpp
 *
 *  Created on: Dec 3, 2019
 *      Author: root
 */

#include "HeapTest.h"
#include "TypeBase.h"
#include <stdio.h>
#include <algorithm>

HeapTest::HeapTest()
{
	// TODO Auto-generated constructor stub

}

HeapTest::~HeapTest()
{
	// TODO Auto-generated destructor stub
}

int HeapTest::AddHeap(std::vector<int>& v, int n)
{
	v.push_back(n);
	int index = v.size()-1;
	int parent;
	while (index >= 1)
	{
		parent = (index-1)/2;
		if (n <= v[parent])
			break;

		std::swap(v[parent], v[index]);
		index = parent;
	}
	return index;
}

void HeapTest::printVector(const std::vector<int>& v)
{
	for (int i=0; i<v.size(); i++)
		printf("%d ", v[i]);
	puts("");
}

void HeapTest::testMakeHeap()
{
	std::vector<int> v;
	AddHeap(v, 1);
	AddHeap(v, 7);
	AddHeap(v, 5);
	AddHeap(v, 21);
	AddHeap(v, 2);
	AddHeap(v, 3);
	AddHeap(v, 33);
	AddHeap(v, 29);
	printVector(v);
}

void HeapTest::MakeHeapSort(std::vector<int>& v)
{
	int curmax = v.size()-1;
	while (curmax > 0)
	{
		for (int i=curmax; i>0; i--)
		{
			if (v[i] > v[(i-1)/2])
				std::swap(v[i], v[(i-1)/2]);
		}
		std::swap(v.front(), v[curmax--]);
	}
}

void HeapTest::MakeHeap(std::vector<int>& v, int size)
{
	for (int i=size-1; i>0; i--)
	{
		if (v[i] > v[(i-1)/2])
			std::swap(v[i], v[(i-1)/2]);
	}
}

void HeapTest::testHeapSort()
{
	std::vector<int> v = {1,7,5,21,2,3,33,29};
//	MakeHeap(v, v.size());
	std::make_heap(v.begin(), v.end());
//	MakeHeapSort(v);
	printVector(v);
}





