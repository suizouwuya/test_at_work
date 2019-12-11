/*
 * MapAlgorithm.cpp
 *
 *  Created on: Dec 10, 2019
 *      Author: root
 */

#include "MapAlgorithm.h"
#include "BinMap.h"
#include "TypeBase.h"

using namespace BIN;

MapAlgorithm::MapAlgorithm()
{
	// TODO Auto-generated constructor stub

}

MapAlgorithm::~MapAlgorithm()
{
	// TODO Auto-generated destructor stub
}

class MapWithSearch
{
	class MapNode
	{
		struct DistanceInfo
		{
			int			distance;
			std::string	strFrom;
			DistanceInfo():distance(0){}
		};
	public:
		std::string		str;
		typedef mgmap<std::string, DistanceInfo/*distance*/> _MapDistance;
		_MapDistance	mapDistance;
		bool empty() { return str.empty(); }
	};

	mgmap<std::string, MapNode>	m_mapNode;

	void AddDistanceTo(const std::string& to, const std::string& of, int distance, const std::string& strFrom)
	{
		if (to == of)
			return;
		auto pNode = m_mapNode.Find(to);
		if (pNode == NULL)
			return;
		auto& oldDistance = pNode->mapDistance.Get(of);
		if (oldDistance.distance != 0 && oldDistance.distance < distance)
			return;

		DEBUG("[add distance] %s %s %d, from:%s", to.c_str(), of.c_str(), distance, strFrom.c_str());
		oldDistance.distance = distance;
		oldDistance.strFrom = strFrom;
		FOR_EACH_FROWARD(it, pNode->mapDistance)
		{
			if (it->second.distance == 1)
				AddDistanceTo(it->first, of, distance+1, to);
		}
	}
public:
	void AddNode(const std::string& str)
	{
		if (m_mapNode.exist(str))
			return;
		DEBUG("[add node] %s-------------", str.c_str());
		MapNode node;
		node.str = str;
		FOR_EACH_FROWARD(it, m_mapNode)
		{
			if (it->first == str)
				continue;

			int countDiff = 0;
			for (int i=0; i<str.length() && i<it->first.length() && countDiff<=1; i++)
			{
				if (str[i] != it->first[i])
					countDiff++;
			}
			if (countDiff == 1)
			{
				node.mapDistance = it->second.mapDistance;
				FOR_EACH_FROWARD(it2, node.mapDistance)
				{
					it2->second.distance++;
					it2->second.strFrom = it->first;
				}
				auto& infoDistance = node.mapDistance.Set(it->first);
				infoDistance.distance = 1;
				infoDistance.strFrom = it->first;
				AddDistanceTo(it->first, str, 1, str);
			}
		}
		m_mapNode.Set(str, node);
	}
	int GetMinDistance(const std::string& str1, const std::string& str2)
	{
		auto pNode1 = m_mapNode.Find(str1);
		if (pNode1 == NULL)
			return 0;

		auto pDistance = pNode1->mapDistance.Find(str2);
		if (pDistance == NULL)
			return 0;

		while (true)
		{
			DEBUG("%s", pNode1->str.c_str());
			auto itDistance = pNode1->mapDistance.find(str2);
			if (itDistance == pNode1->mapDistance.end() || itDistance->second.strFrom == str2)
				break;
			pNode1 = m_mapNode.Find(itDistance->second.strFrom);
		}
		DEBUG("%s", str2.c_str());

		return pDistance->distance;
	}
};

int MapAlgorithm::GetMinDistance(const std::vector<std::string>& vecAllWord, int beginIndex, int endIndex)
{
	MapWithSearch ms;
	FOR_EACH_FROWARD(it, vecAllWord)
		ms.AddNode(*it);

	return ms.GetMinDistance(vecAllWord[beginIndex], vecAllWord[endIndex]);
}

void MapAlgorithm::testMinDistance()
{
	std::vector<std::string> vs = {"hit","hot","dot","dog","lot","log","cog"};
	DEBUG("%d", GetMinDistance(vs, 0, 6));

}


