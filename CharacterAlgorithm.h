/*
 * CharacterAlgorithm.h
 *
 *  Created on: Nov 11, 2019
 *      Author: root
 */

#ifndef CHARACTERALGORITHM_H_
#define CHARACTERALGORITHM_H_
#include <string.h>
#include <string>
#include <vector>
#include <list>
#include <tr1/memory>

using namespace std;

namespace CHA
{
struct Node
{
	int				data;
	struct Node*	next;
	Node():data(0),next(NULL){}
};
class CList
{
public:
	CList():m_head(NULL),m_tail(NULL){}
	Node* head() { return m_head; }
	Node* end() { return NULL; }
	Node* push_back(int data);
	Node*	m_head;
	Node*	m_tail;
};
}

class CharacterAlgorithm
{
public:
	CharacterAlgorithm();
	virtual ~CharacterAlgorithm();

	void ReverseWord(char* str, int len);
	void LeftRotateString(char* str, int len, int m);
	void ReverseString(char* str, int from, int to);
	void testReverseWord();


	//@return HEAD
	CHA::Node* ReserverList(CHA::Node* pHead, CHA::Node* pEnd=NULL);
	CHA::Node* LeftRotateList(CHA::Node* pHead, int m);
	void testLeftRotateList();

	bool StringContain(char* src, char* dest);

	bool IsPalindrome(const char* src, int len);
	bool FindPalindrome(std::string str, std::vector<std::string> &vecPldm);
	std::string FindMaxPalindrome(std::string str);
	// 奇数回文
	int FindPalinedromeOddLen(const char* src, int maxlen);
	// 偶数回文
	int FindPalinedromeEvenLen(const char* srcleft, int maxlen);
	void testFindpalindrome();

	// 全排列1
	void printVector(const std::vector<char> & vec);
	void printFromVector(const char* src, const std::vector<int> & vec);
	void printAllArangeVector(std::vector<char> & vecHave, std::vector<char> & vecNeed);
	void printAllArange(const char* src);

	// 全排列2
	//from: 0~len-1
	void reverseVector(std::vector<char> & vc, int from, int to);
	bool next_permutation(std::vector<char> & vc);
	void printAllArange2(const char* src);

	// 全排列 - 含子排列
	void printAllCombin(const char* src);

	//size(arrDelta)==lenpat*2
	std::vector<int> kmp_make_delta(const char* pat);
	const char* kmpsearch(const char* src, const char* pat);

	// 坏字符
	std::vector<int> bm_make_delta1(const char* pat);
	// 好后缀
	std::vector<int> bm_make_delta2(const char* pat);
	const char* bmsearch(const char* src, const char* pat);

};

#endif /* CHARACTERALGORITHM_H_ */
