/*
 * BoostTime.cpp
 *
 *  Created on: Nov 26, 2019
 *      Author: root
 */

#include "BoostTime.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <time.h>
#include <vector>
#include <string>
#include "TypeBase.h"

typedef unsigned int uint32;
typedef unsigned char uint8;


BoostTime::BoostTime()
{
	// TODO Auto-generated constructor stub

}

BoostTime::~BoostTime()
{
	// TODO Auto-generated destructor stub
}

int GetTime()
{
	return time(NULL);
}

//拆分src中的内容，拆分符号为sep，放入vecRes
void StrSplit(const std::string & src, const std::string & sep, std::vector<std::string>& tokens )
{
	tokens.clear();

	 std::string::size_type pos1, pos2;
	 pos2 = src.find(sep);
	 pos1 = 0;
//		 IME_ERROR("%s",src.c_str());
	 while(std::string::npos != pos2)
	 {
	    tokens.push_back(src.substr(pos1, pos2-pos1));
//			IME_ERROR("%s",src.substr(pos1, pos2-pos1).c_str());
	    pos1 = pos2 + sep.size();
	    pos2 = src.find(sep, pos1);
	 }
	 if(pos1 != src.length())
	 {
		 tokens.push_back(src.substr(pos1));
	 }
}
uint32 ConvertDateToTime(std::string strTime, std::string sep)
{
	struct tm stcCur;
	std::vector<std::string> vecStr;
	StrSplit(strTime,sep,vecStr);


	stcCur.tm_year 	= atoi( vecStr[0].c_str() ) - 1900;
	stcCur.tm_mon	= atoi( vecStr[1].c_str() ) - 1;
	stcCur.tm_mday	= atoi( vecStr[2].c_str() );
	stcCur.tm_hour 	= ( vecStr.size() >= 4 ? atoi( vecStr[3].c_str() ) : 0 );
	stcCur.tm_min 	= ( vecStr.size() >= 5 ? atoi( vecStr[4].c_str() ) : 0 );
	stcCur.tm_sec 	= ( vecStr.size() >= 6 ? atoi( vecStr[5].c_str() ) : 0 );
	stcCur.tm_isdst = -1;
	return mktime(&stcCur);
}

uint32 GetTimeOfDay(uint32 dwNow, uint8 byClock/*=0*/, uint8 byMin/*=0*/, uint8 bySec/*=0*/)
{
	struct tm stcInput;
	time_t timeInput = dwNow;
	localtime_r( &timeInput, &stcInput );

	stcInput.tm_hour = byClock;
	stcInput.tm_min = byMin;
	stcInput.tm_sec = bySec;
	stcInput.tm_isdst = -1; //系统自动选择夏令时
	return mktime(&stcInput);
	//return timeInput - stcInput.tm_hour * HOUR - stcInput.tm_min * MINUTE - stcInput.tm_sec + byClock * HOUR;
}
uint32 GetTimeOfDayByTime(uint32 dwNow, uint32 dwReferTime)
{
	struct tm stcInput;
	time_t timeInput = dwReferTime;
	localtime_r( &timeInput, &stcInput );
	return GetTimeOfDay(dwNow, stcInput.tm_hour, stcInput.tm_min, stcInput.tm_sec);
}
uint32 GetDayOffsetMax(uint32 dwTime1, uint32 dwTime2/*=0*/)
{
	if (dwTime2 == 0)
		dwTime2 = GetTime();
	if (dwTime1 > dwTime2)
		return GetDayOffsetMax(dwTime2, dwTime1);

	using namespace boost::posix_time;
	using namespace boost::gregorian;
	struct tm tmNow, tmStartTime;

	time_t tTime = dwTime1;
	localtime_r(&tTime, &tmNow);
	tTime = dwTime2;
	localtime_r(&tTime, &tmStartTime);
	return abs((ptime_from_tm(tmNow).date() - ptime_from_tm(tmStartTime).date()).days());
}
uint32 GetDayOffsetMin(uint32 dwTime1, uint32 dwTime2/*=0*/)
{
	if (dwTime2 == 0)
		dwTime2 = GetTime();
	if (dwTime1 > dwTime2)
		return GetDayOffsetMin(dwTime2, dwTime1);

	int nDayOffset = GetDayOffsetMax(dwTime1, dwTime2);
	uint32 dwDay2Relative = GetTimeOfDayByTime(dwTime2, dwTime1);
	if (dwDay2Relative > dwTime2)
		nDayOffset = nDayOffset - 1;
	if (nDayOffset < 0)
		return 0;
	return nDayOffset;
}

void BoostTime::testDiffDay()
{
	int tm1 = ConvertDateToTime("2019-11-23-1", "-");
	int tm2 = ConvertDateToTime("2019-11-25-2", "-");

	DEBUG("[time diff]:%d", GetDayOffsetMax(tm1, tm2));
}


