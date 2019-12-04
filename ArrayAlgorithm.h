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

	std::vector<int> FindMinNumbers(const std::vector<int>& vec, int findsize);
	std::vector<int> FindMinNumbers2(const std::vector<int>& vec, int findsize);
	void testMinnums();

	std::vector<int> GetMinSum(const std::vector<int>& va, const std::vector<int>& vb, int k);
	void testMinSum();
};

#endif /* ARRAYALGORITHM_H_ */
