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

class _MapCompare
{
public:
	const std::string*	m_pstr;
public:
	// a is front ?
	bool operator()(const int& a, const int& b) const
	{
		if (a>=m_pstr->length() || b>=m_pstr->length())
			return true;

		int i = 0;
		for (; i<m_pstr->length()-b && i<m_pstr->length()-a; i++)
		{
			int diff = m_pstr->at(a+i) - m_pstr->at(b+i);
			if (diff < 0)
				return true;
			if (diff > 0)
				return false;
		}
		return (a < b);
	}
};

std::string MaxSubString::GetMaxSubString(std::string str)
{
	_MapCompare comp;
	comp.m_pstr = &str;
	std::set<int, _MapCompare> setSubstring(comp);
	for (int i=0; i<str.length(); i++)
		setSubstring.insert(i);

	auto it = setSubstring.begin();
	if (it == setSubstring.end())
		return str;
	auto itnext = it;
	itnext++;

	int maxsame = 1;
	auto itMax = it;

	while (itnext != setSubstring.end())
	{
		int i = 0;
		for (; i<str.length()-*itnext && str.at(*it+i)==str.at(*itnext+i); i++);
		if (i > maxsame)
		{
			maxsame = i;
			itMax = it;
		}

		it = itnext++;
	}
	std::string res(str.c_str()+*itMax, maxsame);
	return res;
}

void MaxSubString::testMaxSubString()
{
	const char* p = "aabaaba";
	auto str = GetMaxSubString(p);
	DEBUG("%s", str.c_str());
}


