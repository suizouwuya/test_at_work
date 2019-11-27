/*
 * BoyerMooresearch.h
 *
 *  Created on: Nov 25, 2019
 *      Author: root
 */

#ifndef BOYERMOORESEARCH_H_
#define BOYERMOORESEARCH_H_
#include <vector>
#include <map>

class Boyer_Moore_search
{
public:
	Boyer_Moore_search();
	virtual ~Boyer_Moore_search();

public:
	std::vector<int> bm_make_delta1(const char* pat);
	std::vector<int> bm_make_delta2(const char* pat);
	const char* bmsearch(const char* src, const char* pat);
	void test_of_mine();

public: // error1
	bool is_prefix(const char *word, int wordlen, int pos);
	int suffix_length(const char *word, int wordlen, int pos);
	// 坏字符
	std::vector<int> bm_make_delta1_with_zero(const char* pat);
	// 好后缀
	std::vector<int> bm_make_delta2_of_error(const char* pat);
	const char* bmsearch1(const char* src, const char* pat);
	void test1_of_error1();

public: // error2
	// 坏字符
	std::vector<int> bm_make_delta1_withlen(const char* pat);
	const char* bmsearch2(const char* src, const char* pat);
	void test2_of_error2();
};

#endif /* BOYERMOORESEARCH_H_ */
