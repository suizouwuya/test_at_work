/*
 * NormalTest.cpp
 *
 *  Created on: Nov 14, 2019
 *      Author: root
 */

#include "NormalTest.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "TypeBase.h"
#include <float.h>

using namespace std;

#define DOUBLE_IS_ZERO(VAR) (((VAR) > 0) ? (VAR<1e-6) : (-VAR<1e-6))
#define DOUBLE_IS_GREATER(VAR1, VAR2) ((VAR1) > (VAR2+1e-6))

#define UINT_SAFE_MINUS(a, b) (((a) > (b)) ? ((a) - (b)) : 0)

NormalTest::NormalTest()
{
	// TODO Auto-generated constructor stub

}

NormalTest::~NormalTest()
{
	// TODO Auto-generated destructor stub
}

class A
{
public:
	std::vector<char> v;
	char* p;
	A():p(new char(5)),v(5){}
	void set() const
	{
		p[0] = 'b';
//		v[0] = 'a';
	}
};
void NormalTest::test1()
{
//	A a;
//	a.set();
//	DEBUG("%c", a.p[0]);
}

void NormalTest::testMath()
{
	int pow1 = pow((float)2, 10);
	int pow2 = log(1024)/log(2);
//	printf("%d %d\n", pow1, pow2);
}



