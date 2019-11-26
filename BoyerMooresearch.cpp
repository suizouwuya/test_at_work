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


std::vector<int> Boyer_Moore_search::bm_make_delta_with_zero(const char* pat)
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

std::vector<int> Boyer_Moore_search::bm_make_delta2(const char* pat)
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

const char* Boyer_Moore_search::bmsearch(const char* src, const char* pat)
{
	auto detal1 = bm_make_delta_with_zero(pat);
	auto detal2 = bm_make_delta2(pat);

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
	const char* pSearch2 = bmsearch(szSearch2, "eeea");
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
	auto detal2 = bm_make_delta2(pat);

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
	char szSearch1[] = "eeababababecababc";
	const char* pSearch = bmsearch2(szSearch1, "ababc");
	const char* pSearchShow = pSearch;
	if (pSearchShow != NULL)
		DEBUG("%s", pSearchShow);
	else
		DEBUG("bm not search");
}


