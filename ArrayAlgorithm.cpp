/*
 * ArrayAlgorithm.cpp
 *
 *  Created on: Dec 4, 2019
 *      Author: root
 */

#include "ArrayAlgorithm.h"

#include <set>
#include "Util.h"
#include <stdio.h>
#include "HeapTest.h"

ArrayAlgorithm::ArrayAlgorithm()
{
	// TODO Auto-generated constructor stub

}

ArrayAlgorithm::~ArrayAlgorithm()
{
	// TODO Auto-generated destructor stub
}

std::vector<int> ArrayAlgorithm::FindMinNumbers(const std::vector<int>& vec, int findsize)
{
	std::set<int> s;
	for (int i=0; i<vec.size(); i++)
	{
		if (s.size() >= findsize)
		{
			if (vec[i] < *s.rbegin())
			{
				s.erase(*s.rbegin());
				s.insert(vec[i]);
			}
		}
		else
			s.insert(vec[i]);
	}

	std::vector<int> vout;
	for (auto it=s.begin(); it!=s.end(); it++)
		vout.push_back(*it);
	return vout;
}

void ArrayAlgorithm::printVector(const std::vector<int>& v)
{
	for (int i=0; i<v.size(); i++)
		printf("%d ", v[i]);
	puts("");
}

std::vector<int> ArrayAlgorithm::FindMinNumbers2(const std::vector<int>& vec, int findsize)
{
	Heap<std::greater<int> > hp;
	for (int i=0; i<vec.size(); i++)
	{
		int n = vec[i];
		if (hp.size() < findsize)
			hp.push(n);
		else if (n < hp.top())
			hp.replaceTopHeap(n);
	}
	return hp.m_vec;
}

void ArrayAlgorithm::testMinnums()
{
	std::vector<int> v;
	for (int i=0; i<15; i++)
		v.push_back(Util::Rand(1, 50));


	printVector(v);
	printVector(FindMinNumbers2(v, 3));
}

std::vector<int> ArrayAlgorithm::GetMinSum(const std::vector<int>& va, const std::vector<int>& vb,
		int k)
{
	std::vector<int> vres;
	if (va.empty() || vb.empty())
		return vres;

	vres.push_back(va.front()+vb.front());

	for (int i=0,j=0; i<va.size() && j<vb.size() && vres.size() < k; )
	{
		int next;
		if (j+1 >= vb.size())
		{
			if (i+1 >= va.size())
				break;
			next = va[++i]+vb[j];
		}
		else if (i+1 >= va.size())
		{
			if (j+1 >= vb.size())
				break;
			next = va[i]+vb[++j];
		}
		else
		{
			if (va[i+1]+vb[j] < va[i]+vb[j+1])
				next = va[++i]+vb[j];
			else
				next = va[i]+vb[++j];
		}
		vres.push_back(next);
	}
	return vres;
}

void ArrayAlgorithm::testMinSum()
{
	std::vector<int> va={1,2,3,4,5};
	std::vector<int> vb={1,3,5,7,8,9};

	printVector(GetMinSum(va, vb, 15));
}



