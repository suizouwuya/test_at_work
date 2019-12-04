/*
 * HeapTest.h
 *
 *  Created on: Dec 3, 2019
 *      Author: root
 */

#ifndef HEAPTEST_H_
#define HEAPTEST_H_
#include <vector>
#include <string>
#include <algorithm>

template <typename _CompareTop = std::greater<int> >
class Heap
{
public:
	std::vector<int>	m_vec;
	_CompareTop			m_compTop;

	Heap():m_compTop(){}

	//@return index
	int push(int n);
	int replaceTopHeap(int n);
	const int& top() const { return m_vec[0];}
	int size() const {return m_vec.size();}
};

class HeapTest
{
public:
	HeapTest();
	virtual ~HeapTest();

	void printVector(const std::vector<int>& v);

	//@return index
	int AddHeap(std::vector<int>& v, int n);
	void testMakeHeap();

	void MakeHeap(std::vector<int>& v, int size);
	void MakeHeapSort(std::vector<int>& v);
	void testHeapSort();
};




template <typename _CompareTop>
int Heap<_CompareTop>::push(int n)
{
	m_vec.push_back(n);
	int index = m_vec.size()-1;
	int parent;
	while (index >= 1)
	{
		parent = (index-1)/2;
		if (m_compTop(m_vec[parent], n))
			break;

		std::swap(m_vec[parent], m_vec[index]);
		index = parent;
	}
	return index;
}

template <typename _CompareTop>
int Heap<_CompareTop>::replaceTopHeap(int n)
{
	if (m_vec.empty())
	{
		m_vec.push_back(n);
		return m_vec.size()-1;
	}

	int curindex = 0;
	m_vec[curindex] = n;

	while (m_vec.size() > curindex*2+1)
	{
		int maxchild = curindex*2+1;
		if (curindex*2+2 < m_vec.size() && !m_compTop(m_vec[curindex*2+1], m_vec[curindex*2+2]))
			maxchild = curindex*2+2;
		if (m_compTop(n, m_vec[maxchild]))
			break;
		std::swap(m_vec[curindex], m_vec[maxchild]);
		curindex = maxchild;
	}
	return curindex;
}

#endif /* HEAPTEST_H_ */
