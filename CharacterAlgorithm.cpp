/*
 * CharacterAlgorithm.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: root
 */

#include "CharacterAlgorithm.h"
#include <algorithm>

using namespace CHA;

CharacterAlgorithm::CharacterAlgorithm()
{
	// TODO Auto-generated constructor stub

}

CharacterAlgorithm::~CharacterAlgorithm()
{
	// TODO Auto-generated destructor stub
}

void CharacterAlgorithm::LeftRotateString(char* str, int len, int m)
{
	if (len <= 1 || m <= 1)
		return;
	m %= len;
	ReverseString(str, 0, m-1);
	ReverseString(str, m, len-1);
	ReverseString(str, 0, len-1);
}

void CharacterAlgorithm::ReverseWord(char* str, int len)
{
	for (int m=0, lastbegin=0; m <= len; m++)
	{
		if (m == len || str[m] == ' ' || str[m] == '\t')
		{
			ReverseString(str, lastbegin, m-1);
			while (m != len && (str[m] == ' ' || str[m] == '\t'))
				m++;
			if (m == len)
				break;
			lastbegin = m;
		}
	}
	ReverseString(str, 0, len-1);
}

void CharacterAlgorithm::ReverseString(char* str, int from, int to)
{
	while (from < to)
	{
		std::swap(str[from++], str[to--]);
	}
}

Node* CharacterAlgorithm::ReserverList(CHA::Node* pHead, CHA::Node* pEnd/*=NULL*/)
{
	if (pHead == NULL || pHead->next == pEnd)
		return pHead;

	Node* pNewHead = pHead->next;
	Node* pOldNode = pEnd;
	while (pNewHead != pEnd)
	{
		pHead->next = pOldNode;
		pOldNode = pHead;
		pHead = pNewHead;
		pNewHead = pNewHead->next;
	}

	pHead->next = pOldNode;
	return pHead;
}


CHA::Node* CharacterAlgorithm::LeftRotateList(CHA::Node* pHead, int m)
{
	if (m < 1 || pHead == NULL)
		return pHead;
	Node* pNextFront = pHead;
	for (int i=0; i<m-1; i++)
		pNextFront = pNextFront->next;
	Node* pNextHead = pNextFront->next;

	//new head is pNextFront
	pNextFront->next = ReserverList(pHead, pNextFront);
	pHead->next = ReserverList(pNextHead);
	return ReserverList(pNextFront);
}

Node* CHA::CList::push_back(int data)
{
	if (m_tail == NULL)
	{
		m_head = new Node;
		m_tail = m_head;
	}
	else
	{
		m_tail->next = new Node;
		m_tail = m_tail->next;
	}
	m_tail->data = data;
	return m_tail;
}

bool CharacterAlgorithm::StringContain(char* src, char* dest)
{
	bool word[256];
	memset(word, 0, sizeof(word));
	for (int i=0; src[i]!='\0'; i++)
		word[src[i]] = 1;
	for (int i=0; dest[i]!='\0'; i++)
	{
		if (word[dest[i]] != 1)
			return false;
	}
	return true;
}

bool CharacterAlgorithm::IsPalindrome(const char* src, int len)
{
	if (len == 0)
		return false;
	int last = len-1;
	for (int i=0; i<last-i; i++)
	{
		if (src[i] != src[last-i])
			return false;
	}
	return true;
}

bool CharacterAlgorithm::FindPalindrome(std::string str, std::vector<std::string>& vecPldm)
{
	const char* src = str.c_str();
	for (int i=0; i<str.length(); i++)
	{
		const char* cur = src+i;
		int len = FindPalinedromeOddLen(cur, i+1);
		vecPldm.push_back(std::string(cur-len+1, len*2-1));
		len = FindPalinedromeEvenLen(cur, i+1);
		if (len > 0)
			vecPldm.push_back(std::string(cur-len+1, len*2));
	}
	return !vecPldm.empty();
}

int CharacterAlgorithm::FindPalinedromeOddLen(const char* src, int maxlen)
{
	int len = 1;
	for (; len<maxlen && *(src+len) != '\0'; len++)
	{
		if (*(src-len) != *(src+len))
			return len;
	}
	return len;
}

string CharacterAlgorithm::FindMaxPalindrome(std::string str)
{
	std::string strMaxPldm;
	const char* src = str.c_str();
	for (int i=0; i<str.length(); i++)
	{
		const char* cur = src+i;
		int maxlen = std::min(i+1, (int)str.length()-i);
		if (maxlen*2-1 <= strMaxPldm.length())
			break;
		int len = FindPalinedromeOddLen(cur, maxlen);
		const char* begin = cur-len+1;
		int lenPldm = len*2-1;
		if (lenPldm > strMaxPldm.length())
			strMaxPldm.assign(begin, lenPldm);


		maxlen = std::min(i+1, (int)str.length()-i-1);
		if (maxlen*2 <= strMaxPldm.length())
			break;
		len = FindPalinedromeEvenLen(cur, i+1);
		begin = cur-len+1;
		lenPldm = len*2;
		if (lenPldm > strMaxPldm.length())
			strMaxPldm.assign(begin, lenPldm);
	}
	return strMaxPldm;
}

int CharacterAlgorithm::FindPalinedromeEvenLen(const char* srcleft, int maxlen)
{
	int len = 0;
	for (; len<maxlen && *(srcleft+len+1) != '\0'; len++)
	{
		if (*(srcleft-len) != *(srcleft+len+1))
			return len;
	}
	return len;
}









