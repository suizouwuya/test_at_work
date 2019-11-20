/*
 * StlTest.cpp
 *
 *  Created on: Nov 15, 2019
 *      Author: root
 */

#include "StlTest.h"
#include <tr1/memory>
#include <stdio.h>
#include "TypeBase.h"

using namespace std;

StlTest::StlTest()
{
	// TODO Auto-generated constructor stub

}

StlTest::~StlTest()
{
	// TODO Auto-generated destructor stub
}

/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////
class B;
class A
{
public:
	std::tr1::weak_ptr<B> ptrb;
	~A()
	{
		DEBUG("~A()");
	}
};

class B
{
public:
	std::tr1::weak_ptr<A> ptra;
	~B()
	{
		DEBUG("~B()");
	}
};

void StlTest::test1()
{
	std::tr1::shared_ptr<B> ptrb(new B);
	std::tr1::shared_ptr<A> ptra(new A);

	ptrb->ptra = ptra;
	ptra->ptrb = ptrb;
	DEBUG("[a]:%ld [b]:%ld\n", ptra.use_count(), ptrb.use_count());
}

/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////
class C : public std::tr1::enable_shared_from_this<C>
{
public:
	~C()
	{
		DEBUG("~C");
	}
	std::tr1::shared_ptr<C> getShared()
	{
		return shared_from_this();
	}
};
void StlTest::test2()
{
	std::tr1::shared_ptr<C> a(new C);
	auto b = a->getShared();
}

