/*
 * MapAlgorithm.h
 *
 *  Created on: Dec 10, 2019
 *      Author: root
 */

#ifndef MAPALGORITHM_H_
#define MAPALGORITHM_H_
#include <string>
#include <vector>

class MapAlgorithm
{
public:
	MapAlgorithm();
	virtual ~MapAlgorithm();

	int GetMinDistance(const std::vector<std::string>& vecAllWord,
			int beginIndex, int endIndex);
	void testMinDistance();
};

#endif /* MAPALGORITHM_H_ */
