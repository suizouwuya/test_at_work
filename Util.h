/*
 * Util.h
 *
 *  Created on: Dec 4, 2019
 *      Author: root
 */

#ifndef UTIL_H_
#define UTIL_H_


class Util
{
public:
	Util();
	virtual ~Util();

	static void Init();

	static int Rand(int max, int min=0);
};

#endif /* UTIL_H_ */
