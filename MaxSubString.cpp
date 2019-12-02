/*
 * MaxSubString.cpp
 *
 *  Created on: Dec 2, 2019
 *      Author: root
 */

#include "MaxSubString.h"
#include <stdio.h>
#include "TypeBase.h"
#include <map>
#include <set>

MaxSubString::MaxSubString()
{
	// TODO Auto-generated constructor stub

}

MaxSubString::~MaxSubString()
{
	// TODO Auto-generated destructor stub
}

struct CompareParam
{
	const std::string*	pstr;
	int					nmax;
	const char*			pmax;
	CompareParam(const std::string* p):pstr(p),nmax(0),pmax(NULL){}
};
class _MapCompare
{
public:
	CompareParam*		pParam;
	_MapCompare(CompareParam* p):pParam(p){}
public:
	// a is front ?
	bool operator()(const int& a, const int& b)
	{
		if (a>=pParam->pstr->length() || b>=pParam->pstr->length())
			return true;

		int i = 0;
		for (; i<pParam->pstr->length()-b && i<pParam->pstr->length()-a; i++)
		{
			int diff = pParam->pstr->at(a+i) - pParam->pstr->at(b+i);
			if (diff < 0)
				return true;
			if (diff > 0)
				return false;
			if (i+1 > pParam->nmax)
			{
				pParam->nmax = i+1;
				pParam->pmax = pParam->pstr->c_str()+a;
			}
		}
		return (a < b);
	}
};

std::string MaxSubString::GetMaxSubString(std::string str)
{
	CompareParam cp(&str);
	_MapCompare comp(&cp);
	// 说明：传入的comp会被拷贝一份，所以如果不用指针，里面的数据无法被获取出来
	std::set<int, _MapCompare> setSubstring(comp);
	for (int i=0; i<str.length(); i++)
		setSubstring.insert(i);

	return std::string(cp.pmax, cp.nmax);
}

void MaxSubString::testMaxSubString()
{
	const char* p = "aabaaba";
	auto str = GetMaxSubString(p);
	DEBUG("%s", str.c_str());
}

int MaxSubString::GetMaxSubArray(std::vector<int>& vec)
{
	if (vec.empty())
		return 0;
	int max = vec[0];
	int maxindex = 0;
	int maxsize = 1;

	int cur = max;
	int curindex1 = 0;
	int cursize = 1;
	for (int i=1; i<vec.size(); i++)
	{
		if (cur > 0)
		{
			cur += vec[i];
			cursize++;
		}
		else
		{
			cur = vec[i];
			curindex1 = i;
			cursize = 1;
		}
		if (cur > max)
		{
			max = cur;
			maxindex = curindex1;
			maxsize = cursize;
		}
	}

	DEBUG("[max:%d]", max);
	for (int i=0; i<maxsize; i++)
		printf("%d ", vec[maxindex+i]);
	puts("");
	return max;
}
int MaxSubString::GetMaxSubArrayArr(const int* arr, int len)
{
	std::vector<int> v;
	for (int i=0; i<len; i++)
	{
		v.push_back(arr[i]);
		printf("%d ", arr[i]);
	}
	puts("");
	return GetMaxSubArray(v);
}

void MaxSubString::testMaxArray()
{
	int a[] = {1, -2, 3, -4, 5, 6, -7};
	GetMaxSubArrayArr(a, sizeof(a)/sizeof(int));
}

void MaxSubString::GetMaxNoRepeatedSubstring(const char* str)
{
	if (str == NULL)
		return;
	int len = strlen(str);
	if (len == 0)
		return;
	std::vector<bool> v(256, false);

	int maxbegin = 0;
	int maxsize = 1;
	int curbegin = maxbegin;
	int cursize = 1;
	v[str[0]] = true;
	for (int i=1; i<len; i++)
	{
		char ci = str[i];
		if (!v[ci])
		{
			cursize++;
			v[ci] = true;
		}
		else
		{
			int j = curbegin;
			for (; j<i; j++)
			{
				char cj = str[j];
				if (cj == ci)
					break;
				v[cj] = false;
			}
			curbegin = j+1;
			cursize = i-j;
		}

		if (cursize > maxsize)
		{
			maxbegin = curbegin;
			maxsize = cursize;
		}
	}

	DEBUG("%.*s", maxsize, str+maxbegin);
}

void MaxSubString::testMaxNoRepeatedSubString()
{
	const char* p = "abcabcbb";
	GetMaxNoRepeatedSubstring(p);
}




