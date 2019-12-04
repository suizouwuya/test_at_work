/*
 * Util.cpp
 *
 *  Created on: Dec 4, 2019
 *      Author: root
 */

#include "Util.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

Util::Util()
{
	// TODO Auto-generated constructor stub

}

Util::~Util()
{
	// TODO Auto-generated destructor stub
}

void Util::Init()
{
	srand(time(0));
}

int Util::Rand(int max, int min)
{
	if ( min == max - 1 ) return min;
	if ( min == max ) return max;
	if ( min > max ) std::swap( min, max );
	int nRand = rand() % ( max - min );
	return nRand + min;
}


