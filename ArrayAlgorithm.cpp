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
#include <algorithm>
#include "HeapTest.h"
#include "TypeBase.h"

using namespace std;

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
void ArrayAlgorithm::printVectorByIndex(const std::vector<int>& value, const std::vector<int>& index)
{
	for (int i=0; i<index.size(); i++)
	{
		if (index[i] >= value.size())
			return;
		printf("%d ", value[index[i]]);
	}
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

void ArrayAlgorithm::printSummingTo(const std::vector<int>& v, int sum)
{
	if (v.empty())
		return;

	std::vector<int/*index*/> vmid;
	vmid.push_back(0);
	int cursum = 0;
	int count = 0;
	while (vmid.back() < v.size())
	{
		cursum += v[vmid.back()];

		if (cursum >= sum)
		{
			if (cursum == sum)
				printVectorByIndex(v, vmid);
			cursum -= v[vmid.back()];
			vmid.pop_back();

			if (vmid.empty())
				break;
			cursum -= v[vmid.back()];
			vmid.back()++;
		}
		else
		{
			vmid.push_back(vmid.back()+1);
		}

		DEBUG("%d", ++count);
	}
}
void ArrayAlgorithm::testSumming()
{
	std::vector<int> v;
	for (int i=0; i<100; i++)
		v.push_back(i);
	printSummingTo(v, 10);
}

void ArrayAlgorithm::printMaxWorth(const std::vector<int>& vecWorth, const std::vector<int>& vecSize,
		int capacity, const std::vector<int>& vecLimit)
{
	// 优化：
	// 1、末尾可以直接加到最大
	// 2、可将数量最多的移动到最后,然后是价值最低
	if (vecWorth.size() != vecSize.size() || vecSize.size() > vecLimit.size())
		return ;

	std::vector<int> vecMaxSelect;
	int nMaxWorth = 0;

	std::vector<int> vecSelectNum(vecWorth.size(), 0);
	int nCurWorth = 0;
	int nCurSize = 0;

	int count = 0;

	while (true)
	{
		if (nMaxWorth < nCurWorth)
		{
			nMaxWorth = nCurWorth;
			vecMaxSelect = vecSelectNum;
		}

		int j = vecSelectNum.size() - 1;
		for (; j>=0; j--)
		{
			++count;
			if ((vecLimit[j] == -1 || vecSelectNum[j] < vecLimit[j]) && nCurSize + vecSize[j] <= capacity)
			{
				nCurWorth += vecWorth[j];
				nCurSize += vecSize[j];
				vecSelectNum[j]++;
				break;
			}
			nCurWorth -= (vecWorth[j] * vecSelectNum[j]);
			nCurSize -= (vecSize[j] * vecSelectNum[j]);
			vecSelectNum[j] = 0;
		}
		if (j < 0)
			break;
		// 优化：处理完成后，从后往前加到最大
		for (int i=vecSelectNum.size()-1; i>=0; i--)
		{
			++count;
			int nAdd = (capacity - nCurSize)/vecSize[i];
			if (vecLimit[i] == -1 || vecSelectNum[i]+nAdd < vecLimit[i])
			{
				nCurWorth += (vecWorth[i]*nAdd);
				nCurSize += (vecSize[i]*nAdd);
				vecSelectNum[i] += nAdd;
				if (nCurSize == capacity)
					break;
			}
		}
	}

	DEBUG("count:%d", count);
	DEBUG("max:%d", nMaxWorth);
	printVector(vecMaxSelect);
}
void ArrayAlgorithm::printMaxWorthByDynamicProgramming(const std::vector<int>& vecWorth,
		const std::vector<int>& vecSize, int capacity)
{
	if (vecWorth.size() != vecSize.size())
		return;
	std::vector<std::vector<int> > vvmaxWorth(vecWorth.size(), std::vector<int>(capacity+1, 0));

//	for (int i=0; i<vecWorth.size(); i++)
//	{
//		if (vecSize[i] <= capacity)
//			vvmaxWorth[0][vecSize[i]] = vecWorth[i];
//	}

	// 从1个开始选择
	for (int i=1; i<vecWorth.size(); i++)
	{
		//选择最后一个内容
		for (int j=1; j<=capacity; j++)
		{
			if (j >= vecSize[i])
				vvmaxWorth[i][j] = std::max(vvmaxWorth[i-1][j], vvmaxWorth[i-1][j-vecSize[i]]+vecWorth[i]);
		}
	}

	DEBUG("max:%d", vvmaxWorth[vecWorth.size()-1][capacity+1]);

//	auto& w = vecSize;
//	auto& v = vecWorth;
//	auto& C = capacity;
//	int n = w.size();
//	vector<vector<int>> memo(n, vector<int>(C + 1, 0));
//
//	for (int j = 0; j <= C; j++)
//	{
//		memo[0][j] = (j >= w[0] ? v[0] : 0);
//	}
//
//	for (int i = 1; i < n; i++)
//	{
//		for (int j = 0; j <= C; j++)
//		{
//			// 0~i这些物品容积为j的背包获得的最大值
//			memo[i][j] = memo[i - 1][j];
//			if (j >= w[i])
//			{
//				memo[i][j] = max(memo[i][j], v[i] + memo[i - 1][j - w[i]]);
//			}
//		}
//	}
//
//	DEBUG("max:%d", memo[n-1][C]);
}

void ArrayAlgorithm::testMaxWorth()
{
	std::vector<int> vecWorth = {6,3,5,4,6};
	std::vector<int> vecSize = {2,2,6,5,4};
	std::vector<int> vecLimit = {1,1,1,1,1};
	printMaxWorth(vecWorth, vecSize, 10, vecLimit);
	printMaxWorthByDynamicProgramming(vecWorth, vecSize, 10);

//	std::vector<int> vecWorth = {6,10,12};
//	std::vector<int> vecSize = {1,2,4};
//	std::vector<int> vecLimit = {1,1,1,};
//	printMaxWorth(vecWorth, vecSize, 5, vecLimit);
}

int ArrayAlgorithm::GetMaxSub(const std::vector<int>& v)
{
	if (v.empty())
		return 0;
	int maxsub = v.front();
	int lastsub = v.front();
	for (int i=1; i<v.size(); i++)
	{
		if (lastsub + v[i] < v[i])
			lastsub = v[i];
		else
			lastsub += v[i];
		if (maxsub < lastsub)
			maxsub = lastsub;
	}
	return maxsub;
}
void ArrayAlgorithm::testMaxSubArray()
{
	std::vector<int> v = {1, -2, 3, 10, -4, 7, 2, -5};
	DEBUG("%d", GetMaxSub(v));
}






