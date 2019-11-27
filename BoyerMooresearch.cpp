/*
 * BoyerMooresearch.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: root
 */

#include "BoyerMooresearch.h"

#include "CharacterAlgorithm.h"
#include <algorithm>
#include "TypeBase.h"
#include <tr1/memory>
#include <string.h>

using namespace std;

Boyer_Moore_search::Boyer_Moore_search()
{
	// TODO Auto-generated constructor stub

}

Boyer_Moore_search::~Boyer_Moore_search()
{
	// TODO Auto-generated destructor stub
}


std::vector<int> Boyer_Moore_search::bm_make_delta1(const char* pat)
{
	// delta1 可能会前移，但是此时delta2保证了会后移
	int lenpat = strlen(pat);
	std::vector<int> vint(256, lenpat);
	for (int i=0; i<lenpat; i++)
	{
		vint[pat[i]] = lenpat - 1 - i;
	}
	return vint;
}

std::vector<int> Boyer_Moore_search::bm_make_delta2(const char* pat)
{
	int lenpat = strlen(pat);
	std::vector<int> vint(lenpat, -1);

	int lastcmp = lenpat-1;
	for (int i=lastcmp-1; i>=0; i--)
	{
		if (lastcmp != lenpat-1)
			vint[lastcmp] = lastcmp-i;

		if (pat[i] == pat[lastcmp])
			lastcmp--;
		else
			lastcmp = lenpat-1;
	}

	for (int i=0; i<lenpat; i++)
	{
		if (vint[i] == -1)
			vint[i] = lenpat - i;
	}
	return vint;
}

const char* Boyer_Moore_search::bmsearch(const char* src, const char* pat)
{
	auto delta1 = bm_make_delta1(pat);
	auto delta2 = bm_make_delta2(pat);
	int lensrc = strlen(src);
	int lenpat = strlen(pat);

	int srccmp = lenpat-1;
	while (srccmp < lensrc)
	{
		int patcmp = lenpat-1;
		while (patcmp>=0 && src[srccmp]==pat[patcmp])
		{
			patcmp--;
			srccmp--;
		}

		//find it
		if (patcmp < 0)
			return src + srccmp + 1;

		if (patcmp == lenpat-1)
			srccmp += delta1[src[srccmp]];
		else
			srccmp += std::max(delta1[src[srccmp]], delta2[patcmp]);
	}
	return NULL;
}
const char* Boyer_Moore_search::bmsearchWithLog(const char* src, const char* pat)
{
	auto delta1 = bm_make_delta1(pat);
	auto delta2 = bm_make_delta2(pat);
	int lensrc = strlen(src);
	int lenpat = strlen(pat);

	const char* space = "                                                     "
			"                                                                    ";

	int srccmp = lenpat-1;
	while (srccmp < lensrc)
	{
		DEBUG("%.*s\033[1;31;40m%.*s\033[0m%s",
				srccmp-lenpat+1, src,
				lenpat, src+srccmp-lenpat+1, src+srccmp+1);
		DEBUG("%.*s%s", srccmp-lenpat+1, space, pat);

		int patcmp = lenpat-1;
		while (patcmp>=0 && src[srccmp]==pat[patcmp])
		{
			patcmp--;
			srccmp--;
		}

		//find it
		if (patcmp < 0)
			return src + srccmp + 1;

		if (patcmp == lenpat-1)
			srccmp += delta1[src[srccmp]];
		else
			srccmp += std::max(delta1[src[srccmp]], delta2[patcmp]);
	}
	return NULL;
}
void Boyer_Moore_search::test_of_mine()
{
	const char* pfind = NULL;
	pfind = bmsearchWithLog("eeababababecababc", "ababc");
//	pfind = bmsearch("eabcabc", "abc");
//	pfind = bmsearchWithLog("eabcabc", "abc");
	if (pfind == NULL)
		DEBUG("not found!");
	else
		DEBUG("[found it] %s", pfind);
}

std::vector<int> Boyer_Moore_search::bm_make_delta1_with_zero(const char* pat)
{
	int lenpat = strlen(pat);
	std::vector<int> delta(256, 0);

	for (int i=0; i<lenpat-2; i++)
	{
		delta[pat[i]] = lenpat-1-i;
	}
	return delta;
}

// true if the suffix of word starting from word[pos] is a prefix
// of word
bool Boyer_Moore_search::is_prefix(const char *word, int wordlen, int pos)
{
	int suffixlen = wordlen - pos;
	// could also use the strncmp() library function here
	// return ! strncmp(word, &word[pos], suffixlen);
	for (int i = 0; i < suffixlen; i++)
	{
		if (word[i] != word[pos + i])
		{
			return false;
		}
	}
	return true;
}

// length of the longest suffix of word ending on word[pos].
// suffix_length("dddbcabc", 8, 4) = 2
int Boyer_Moore_search::suffix_length(const char *word, int wordlen, int pos)
{
	int i;
	// increment suffix length i to the first mismatch or beginning
	// of the word
	for (i = 0; (word[pos - i] == word[wordlen - 1 - i]) && (i < pos); i++)
		;
	return i;
}

std::vector<int> Boyer_Moore_search::bm_make_delta2_of_error(const char* pat)
{
	const int lenpat = strlen(pat);
	std::vector<int> delta(lenpat);

	int last_prefix_index = lenpat-1;
	for (int i=lenpat-1; i>=0; i--)
	{
		if (is_prefix(pat, lenpat, i + 1))
			last_prefix_index = i + 1;
		delta[i] = last_prefix_index + (lenpat - 1 - i);
	}

	// second loop
	for (int i = 0; i < lenpat - 1; i++)
	{
		size_t slen = suffix_length(pat, lenpat, i);
		if (pat[i - slen] != pat[lenpat - 1 - slen])
			delta[lenpat - 1 - slen] = lenpat - 1 - i + slen;
	}
	return delta;
}

const char* Boyer_Moore_search::bmsearch1(const char* src, const char* pat)
{
	auto detal1 = bm_make_delta1_with_zero(pat);
	auto detal2 = bm_make_delta2_of_error(pat);

	const int lenpat = strlen(pat);
	const int lensrc = strlen(src);


	int srccmp = lenpat-1;
	while (srccmp < lensrc)
	{
		int patcmp = lenpat-1;
		while (patcmp>=0 && src[srccmp] == pat[patcmp])
		{
			srccmp--;
			patcmp--;
		}
		if (patcmp < 0)
			return src+srccmp+1;
		srccmp += std::max(detal1[src[srccmp]], detal2[patcmp]);
	}
	return NULL;
}

void Boyer_Moore_search::test1_of_error1()
{
	char szSearch2[] = "eeababababecabeeeababceeee";
	const char* pSearch2 = bmsearch1(szSearch2, "eeea");
	const char* pSearchShow = pSearch2;
	if (pSearchShow != NULL)
		DEBUG("%s", pSearchShow);
	else
		DEBUG("bm not search");
}


std::vector<int> Boyer_Moore_search::bm_make_delta1_withlen(const char* pat)
{
	int lenpat = strlen(pat);
	std::vector<int> delta(256, lenpat);

	for (int i=0; i<lenpat-2; i++)
	{
		delta[pat[i]] = lenpat-1-i;
	}
	return delta;
}
const char* Boyer_Moore_search::bmsearch2(const char* src, const char* pat)
{
	auto detal1 = bm_make_delta1_withlen(pat);
	auto detal2 = bm_make_delta2_of_error(pat);

	const int lenpat = strlen(pat);
	const int lensrc = strlen(src);


	int srccmp = lenpat-1;
	while (srccmp < lensrc)
	{
		int patcmp = lenpat-1;
		while (patcmp>=0 && src[srccmp] == pat[patcmp])
		{
			srccmp--;
			patcmp--;
		}
		if (patcmp < 0)
			return src+srccmp+1;
		srccmp += std::max(detal1[src[srccmp]], detal2[patcmp]);
	}
	return NULL;
}

void Boyer_Moore_search::test2_of_error2()
{
	// 这是维基百科使用的一种代码实现方案，在进行如下搜索时发生错误
	char szSearch1[] = "eeababababecababc";
	const char* pSearch = bmsearch2(szSearch1, "ababc");
	const char* pSearchShow = pSearch;
	if (pSearchShow != NULL)
		DEBUG("%s", pSearchShow);
	else
		DEBUG("bm not search");
}


