/*
 * BinMap.h
 *
 *  Created on: Nov 30, 2017
 *      Author: root
 */

#ifndef BINMAP_H_
#define BINMAP_H_
#include <map>
#include <functional>
#include <stddef.h>

namespace BIN
{

template <typename T1, typename T2, typename _Compare = std::less<T1> >
class mgmap : public std::map<T1, T2, _Compare>
{
public:
	typedef typename std::map<T1, T2, _Compare> Type;
	typedef typename Type::const_iterator const_iterator;
	typedef typename Type::iterator iterator;
	typedef typename std::pair<iterator, bool> TypeInsertRes;

	T2& Set(const T1& k)
	{ return this->insert(std::make_pair(k, T2())).first->second; }
	T2& Set(const T1& k, const T2& v);
	T2& SetDefault(const T1& k, const T2& v_default=T2())
	{ return this->insert(std::make_pair(k, v_default)).first->second; }

	//todo Get should not call insert
	//const T2& Get(const T1& k, const T2& v_default=T2()) const
	//T2& Get(const T1& k, T2& v_default=T2())
	T2& Get(const T1& k, const T2& v_default=T2())
	{ return this->insert(std::make_pair(k, v_default)).first->second; }

	const T2& Front(const T2& v_default) const;
	const T2* Find(const T1& k) const;
	T2* Find(const T1& k);
	T2 Value_Default(const T1& k, const T2& v_default=T2()) const;
	bool exist(const T1& k) const
	{ return (!(this->find(k) == this->end())); }

	const_iterator FindLeftOrEqualIterator(const T1& k) const;
	iterator FindLeftOrEqualIterator(const T1& k);
	//查找小于等于该值的最小值，补充lower_bound
	const T2* FindLeftOrEqual(const T1& k) const;
	T2* FindLeftOrEqual(const T1& k);

	const_iterator FindLeftIterator(const T1& k) const;
	iterator FindLeftIterator(const T1& k);
	const T2* FindLeft(const T1& k) const;
	T2* FindLeft(const T1& k);

	mgmap& operator+=(const mgmap& m);
	mgmap& merge(const mgmap& m); //if repeat then ignore
};

//安全的map，更新时，会删除旧的数据
template <typename KeyType, typename ValueType>
class SafeMap
{
protected:
	typedef std::map<KeyType, ValueType> _MapData;
	typedef std::multimap<ValueType, KeyType> _MapLink;
	_MapData	m_mapData;
	_MapLink	m_mapLink;
public:
	//<KeyType, ValueType>
	typedef typename _MapData::const_iterator	const_iterator;
	//<ValueType, KeyType>
	typedef typename _MapLink::const_iterator	const_link_iterator;
	typedef typename _MapLink::const_reverse_iterator	const_link_reverse_iterator;
public:
	const ValueType& Set(const KeyType& key, const ValueType& value);
	bool erase(const KeyType& key)
	{ return _delByKey(key); }
	void clear()
	{
		m_mapData.clear();
		m_mapLink.clear();
	}

	const ValueType* at(const KeyType& key);
	const ValueType& Get(const KeyType& key, const ValueType& valueNull);
	const_iterator find(const KeyType& key) const
	{ return m_mapData.find(key); }
	const_iterator begin() const
	{ return m_mapData.begin(); }
	const_iterator end() const
	{ return m_mapData.end(); }
	const_link_iterator link_begin() const
	{ return m_mapLink.begin(); }
	const_link_iterator link_end() const
	{ return m_mapLink.end(); }
	const_link_reverse_iterator link_rbegin() const
	{ return m_mapLink.rbegin(); }
	const_link_reverse_iterator link_rend() const
	{ return m_mapLink.rend(); }
	const_link_iterator link_find(const ValueType& value) const
	{ return m_mapLink.find(value); }
	//<=value
	const_link_iterator link_find_lfeq(const ValueType& value) const;
	//>=value
	const_link_iterator link_find_lower_bound(const ValueType& value) const
	{ return m_mapLink.lower_bound(value); }
	bool empty() const
	{ return m_mapLink.empty(); }
	int size() const
	{ return m_mapLink.size(); }
private:
	const ValueType* _getValue(const KeyType& key);
	bool _delByKey(const KeyType& key);
	const ValueType& _setValue(const KeyType& key, const ValueType& value);
};

}

//Implement
namespace BIN
{

template <typename T1, typename T2, typename _Compare>
T2& mgmap<T1,T2,_Compare>::Set(const T1& k, const T2& v)
{
	TypeInsertRes pairRes = this->insert(std::make_pair(k, v));
	if (pairRes.second)
		return pairRes.first->second;
	pairRes.first->second = v;
	return pairRes.first->second;
}
template <typename T1, typename T2, typename _Compare>
const T2& mgmap<T1,T2,_Compare>::Front(const T2& v_default) const
{
	if (this->empty())
		return v_default;
	return this->begin()->second;
}
template <typename T1, typename T2, typename _Compare>
const T2* mgmap<T1,T2,_Compare>::Find(const T1& k) const
{
	typename Type::const_iterator it = this->find(k);
	if (it == this->end())
		return NULL;
	return &(it->second);
}
template <typename T1, typename T2, typename _Compare>
T2* mgmap<T1,T2,_Compare>::Find(const T1& k)
{
	typename Type::iterator it = this->find(k);
	if (it == this->end())
		return NULL;
	return &(it->second);
}
template <typename T1, typename T2, typename _Compare>
T2 mgmap<T1,T2,_Compare>::Value_Default(const T1& k, const T2& v_default/*=T2()*/) const
{
	const T2* p = Find(k);
	if (p != NULL)
		return *p;
	return v_default;
}
template <typename T1, typename T2, typename _Compare>
typename mgmap<T1,T2,_Compare>::const_iterator mgmap<T1,T2,_Compare>::FindLeftOrEqualIterator(const T1& k) const
{
	const_iterator it = this->lower_bound(k);
	if (it == this->end())
	{ //begin() && end() cannot -- (Segmentation fault)
		if (it != this->begin())
			it--;
		return it;
	}
	if (!(it->first < k || k < it->first))
		return it;
	if (it == this->begin()) //Cannot --it;
		return this->end();
	return --it; //begin()-- ==> end()
}
template <typename T1, typename T2, typename _Compare>
typename mgmap<T1,T2,_Compare>::iterator mgmap<T1,T2,_Compare>::FindLeftOrEqualIterator(const T1& k)
{
	iterator it = this->lower_bound(k);
	if (it == this->end())
	{
		if (it != this->begin())
			it--;
		return it;
	}
	if (!(it->first < k || k < it->first))
		return it;
	if (it == this->begin())
		return this->end();
	return --it;
}
template <typename T1, typename T2, typename _Compare>
const T2* mgmap<T1,T2,_Compare>::FindLeftOrEqual(const T1& k) const
{
	const_iterator it = FindLeftOrEqualIterator(k);
	if (it == this->end())
		return NULL;
	return &(it->second);
}
template <typename T1, typename T2, typename _Compare>
T2* mgmap<T1,T2,_Compare>::FindLeftOrEqual(const T1& k)
{
	iterator it = FindLeftOrEqualIterator(k);
	if (it == this->end())
		return NULL;
	return &(it->second);
}

template <typename T1, typename T2, typename _Compare>
mgmap<T1,T2,_Compare>& mgmap<T1,T2,_Compare>::operator+=(const mgmap& m)
{
	TypeInsertRes pairRes;
	typename mgmap::const_iterator it;
	for (it=m.begin(); it!=m.end(); it++)
	{
		pairRes = this->insert(std::make_pair(it->first, it->second));
		if (pairRes.second)
			continue;
		else
			pairRes.first->second += it->second;
	}
	return *this;
}
template <typename T1, typename T2, typename _Compare>
mgmap<T1,T2,_Compare>& mgmap<T1,T2,_Compare>::merge(const mgmap& m) //if repeat then ignore
{
	typename mgmap::const_iterator it = m.begin();
	for (; it!=m.end(); it++)
	{
		Get(it->first, it->second);
	}
	return *this;
}

template <typename T1, typename T2, typename _Compare>
typename mgmap<T1,T2,_Compare>::const_iterator mgmap<T1,T2,_Compare>::FindLeftIterator(const T1& k) const
{
	const_iterator it = this->lower_bound(k);
	if (it == this->end())
	{
		if (it == this->begin())
			return this->end();
		--it;
		return it;
	}
	if (it == this->begin())
		return this->end();
	--it;
	if (it->first < k)
		return it;
	return this->end();
}
template <typename T1, typename T2, typename _Compare>
typename mgmap<T1,T2,_Compare>::iterator mgmap<T1,T2,_Compare>::FindLeftIterator(const T1& k)
{
	iterator it = this->lower_bound(k);
	if (it == this->end())
	{
		if (it == this->begin())
			return this->end();
		--it;
		return it;
	}
	if (it == this->begin())
		return this->end();
	--it;
	if (it->first < k)
		return it;
	return this->end();
}
template <typename T1, typename T2, typename _Compare>
const T2* mgmap<T1,T2,_Compare>::FindLeft(const T1& k) const
{
	const_iterator it = FindLeftIterator(k);
	if (it == this->end())
		return NULL;
	return &(it->second);
}
template <typename T1, typename T2, typename _Compare>
T2* mgmap<T1,T2,_Compare>::FindLeft(const T1& k)
{
	iterator it = FindLeftIterator(k);
	if (it == this->end())
		return NULL;
	return &(it->second);
}

}

namespace BIN
{
template<typename KeyType, typename ValueType>
const ValueType& SafeMap<KeyType,ValueType>::Set(const KeyType& key, const ValueType& value)
{
	const ValueType* pValue = _getValue(key);
	if (pValue != NULL && !(*pValue < value || value < *pValue))
		return *pValue;
	_delByKey(key);
	return _setValue(key, value);
}
template<typename KeyType, typename ValueType>
const ValueType* SafeMap<KeyType,ValueType>::at(const KeyType& key)
{
	return _getValue(key);
}
template<typename KeyType, typename ValueType>
const ValueType& SafeMap<KeyType,ValueType>::Get(const KeyType& key, const ValueType& valueNull)
{
	const ValueType* pValue = _getValue(key);
	if (pValue != NULL)
		return *pValue;
	return valueNull;
}
//查找小于等于value的最大值
template<typename KeyType, typename ValueType>
typename SafeMap<KeyType,ValueType>::const_link_iterator
	SafeMap<KeyType,ValueType>::link_find_lfeq(const ValueType& value) const
{
	const_link_iterator it = m_mapLink.lower_bound(value);
	if (it == m_mapLink.end())
	{
		if (it != m_mapLink.begin())
			it--;
		return it;
	}
	if (!(it->first < value || value < it->first))
		return it;
	if (it == m_mapLink.begin())
		return m_mapLink.end();
	return --it;
}
template<typename KeyType, typename ValueType>
const ValueType* SafeMap<KeyType,ValueType>::_getValue(const KeyType& key)
{
	typename _MapData::iterator it = m_mapData.find(key);
	if (it == m_mapData.end())
		return NULL;
	return &(it->second);
}
template<typename KeyType, typename ValueType>
bool SafeMap<KeyType,ValueType>::_delByKey(const KeyType& key)
{
	typename _MapData::iterator it = m_mapData.find(key);
	if (it == m_mapData.end())
		return false;
	typename _MapLink::iterator it2 = m_mapLink.find(it->second);
	while (it2 != m_mapLink.end() && it2->second != it->first)
		it2++;
	while (it2 != m_mapLink.end() && !(it2->second < it->first || it->first < it2->second))
		m_mapLink.erase(it2++);
	m_mapData.erase(it);
	return true;
}
template<typename KeyType, typename ValueType>
const ValueType& SafeMap<KeyType,ValueType>::_setValue(const KeyType& key, const ValueType& value)
{
	typename _MapData::iterator it = m_mapData.insert(MK(key, value)).first;
	m_mapLink.insert(MK(value, key));
	return it->second;
}
}


#endif /* BINMAP_H_ */
