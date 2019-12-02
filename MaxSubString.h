/*
 * MaxSubString.h
 *
 *  Created on: Dec 2, 2019
 *      Author: root
 */

#ifndef MAXSUBSTRING_H_
#define MAXSUBSTRING_H_
#include <string>

class MaxSubString
{
public:
	MaxSubString();
	virtual ~MaxSubString();

	std::string GetMaxSubString(std::string str);
	void testMaxSubString();
};

#endif /* MAXSUBSTRING_H_ */
