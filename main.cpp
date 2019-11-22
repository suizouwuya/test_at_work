/*
 * main.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: root
 */
#include "CharacterAlgorithm.h"
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include "NormalTest.h"
#include "StlTest.h"
#include "RedBlackTree.h"

int main()
{
	char str[] = "abc123";
	CharacterAlgorithm a;
//	a.LeftRotateString(str, strlen(str), 3);
	a.printAllCombin("13245");


	char bstr[] = "abc def 123";
	a.ReverseWord(bstr, strlen(bstr));


	CHA::CList list1;
	list1.push_back(1);
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(15);
	list1.push_back(25);
	list1.push_back(35);

	list1.m_tail = list1.head();
	list1.m_head = a.LeftRotateList(list1.head(), 3);

	char sc1[] = "abcdef";
	char sc2[] = "bcd";
	char sc3[] = "bc1";
//	printf("%d\n", a.StringContain(sc1, sc2));
//	printf("%d\n", a.StringContain(sc1, sc3));

	char pldm[] = "abcdcba";
	char pldm2[] = "abcddcba";
//	printf("%d\n", a.IsPalindrome(pldm, strlen(pldm)));
//	printf("%d\n", a.IsPalindrome(pldm2, strlen(pldm2)));


	vector<string> vecPalindrome;
	a.FindPalindrome("abccbaaa", vecPalindrome);
//	for (int i=0; i<vecPalindrome.size(); i++)
//		printf("[%d]:%s\n", i, vecPalindrome[i].c_str());
//	printf("%s\n", a.FindMaxPalindrome("abccbaaaaaaap").c_str());

	int pow1 = pow(2, 10);
	int pow2 = log(1024)/log(2);
//	printf("%d %d\n", pow1, pow2);


	NormalTest t;
	t.test1();

	StlTest st1;
	st1.test2();


	RedBlackTest rbtest;
//	rbtest.test();


}



