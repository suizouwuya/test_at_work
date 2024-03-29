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
#include "TypeBase.h"
#include "BoyerMooresearch.h"
#include "BoostTime.h"
#include "MaxSubString.h"
#include "HeapTest.h"
#include "ArrayAlgorithm.h"
#include "MapAlgorithm.h"

int main()
{
	DEBUG("===============");
	DEBUG("===============");
	CharacterAlgorithm a;
//	a.testReverseWord();
//	a.testLeftRotateList();
//	a.testFindpalindrome();
//	a.testWubi();
//	a.testAllPalinedrome();
//	a.testMeregeN();


	Boyer_Moore_search bms;
//	bms.test1_of_error1();
//	bms.test2_of_error2();
//	bms.test_of_mine();


	NormalTest t;
//	t.testMath();
//	t.test1();
//	t.testThrow();

	StlTest st1;
//	st1.test2();


	RedBlackTest rbtest;
//	rbtest.test();

	BoostTime bt;
//	bt.testDiffDay();

	MaxSubString ms;
//	ms.testMaxNoRepeatedSubString();

	HeapTest ht;
//	ht.testHeapSort();

	ArrayAlgorithm aa;
//	aa.testMaxSubArray();

	MapAlgorithm ma;
	ma.testMinDistance();

}



