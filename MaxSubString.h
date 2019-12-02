/*
 * MaxSubString.h
 *
 *  Created on: Dec 2, 2019
 *      Author: root
 */

#ifndef MAXSUBSTRING_H_
#define MAXSUBSTRING_H_
#include <string>
#include <vector>

class MaxSubString
{
public:
	MaxSubString();
	virtual ~MaxSubString();

	std::string GetMaxSubString(std::string str);
	void testMaxSubString();

	int GetMaxSubArray(std::vector<int>& vec);
	int GetMaxSubArrayArr(const int* arr, int len);
	void testMaxArray();

	void GetMaxNoRepeatedSubstring(const char* str);
	void testMaxNoRepeatedSubString();
};

#endif /* MAXSUBSTRING_H_ */
