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


	//@return HEAD
	CHA::Node* ReserverList(CHA::Node* pHead, CHA::Node* pEnd=NULL);
	CHA::Node* LeftRotateList(CHA::Node* pHead, int m);

	bool StringContain(char* src, char* dest);

	bool IsPalindrome(const char* src, int len);
	bool FindPalindrome(std::string str, std::vector<std::string> &vecPldm);
	std::string FindMaxPalindrome(std::string str);
	// 奇数回文
	int FindPalinedromeOddLen(const char* src, int maxlen);
	// 偶数回文
	int FindPalinedromeEvenLen(const char* srcleft, int maxlen);

	void printVector(const std::vector<char> & vec);
	void printAllArangeVector(std::vector<char> & vecHave, std::vector<char> & vecNeed);
	void printAllArange(const char* src);

	//from: 0~len-1
	void reverseVector(std::vector<char> & vc, int from, int to);
	bool next_permutation(std::vector<char> & vc);
	void printAllArange2(const char* src);

};

#endif /* CHARACTERALGORITHM_H_ */
