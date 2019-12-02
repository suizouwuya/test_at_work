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

int main()
{
	CharacterAlgorithm a;
//	a.testReverseWord();
//	a.testLeftRotateList();
//	a.testFindpalindrome();
//	a.testWubi();
	a.testSuffixString();


	Boyer_Moore_search bms;
//	bms.test1_of_error1();
//	bms.test2_of_error2();
//	bms.test_of_mine();


	NormalTest t;
//	t.testMath();
//	t.test1();

	StlTest st1;
//	st1.test2();


	RedBlackTest rbtest;
//	rbtest.test();

	BoostTime bt;
//	bt.testDiffDay();

	MaxSubString ms;
//	ms.testMaxNoRepeatedSubString();

}



