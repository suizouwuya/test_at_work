/*
 * ArrayAlgorithm.h
 *
 *  Created on: Dec 4, 2019
 *      Author: root
 */

#ifndef ARRAYALGORITHM_H_
#define ARRAYALGORITHM_H_

#include <vector>
#include <string>

class ArrayAlgorithm
{
public:
	ArrayAlgorithm();
	virtual ~ArrayAlgorithm();

	void printVector(const std::vector<int>& v);
	void printVectorByIndex(const std::vector<int>& value, const std::vector<int>& index);

	std::vector<int> FindMinNumbers(const std::vector<int>& vec, int findsize);
	std::vector<int> FindMinNumbers2(const std::vector<int>& vec, int findsize);
	void testMinnums();

	std::vector<int> GetMinSum(const std::vector<int>& va, const std::vector<int>& vb, int k);
	void testMinSum();

	//v is sort from lesser to greater
	void printSummingTo(const std::vector<int>& v, int sum);
	void testSumming();

	void printMaxWorth(const std::vector<int>& vecWorth, const std::vector<int>& vecSize,
			int capacity,
			const std::vector<int>& vecLimit);
	void printMaxWorthByDynamicProgramming(const std::vector<int>& vecWorth, const std::vector<int>& vecSize,
			int capacity);
	void testMaxWorth();

	int GetMaxSub(const std::vector<int>& v);
	void testMaxSubArray();
};

#endif /* ARRAYALGORITHM_H_ */
