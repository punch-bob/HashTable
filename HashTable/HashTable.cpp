#include "pch.h"
#include <functional>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include"HashTable.h"

HashTable::HashTable()
{
	//1009 - простое число
	tsize = 1009;
	real_size = 0;
	table = HTable(tsize);
}

HashTable::~HashTable()
{
	table.clear();
}

HashTable::HashTable(const HashTable& b)
{
	tsize = b.tsize;
	real_size = b.real_size;
	table = HTable(tsize);
	for (int i = 0; i < tsize; i++)
	{
		table[i] = b.table[i];
	}
}

HashTable::HashTable(HashTable&& b)
{
	tsize = b.tsize;
	real_size = b.real_size;
	b.real_size = 0;
	b.tsize = 0;
	table = std::move(b.table);
}

HashTable& HashTable::operator=(const HashTable& b)
{
	if (*this == b)
	{
		return *this;
	}
	tsize = b.tsize;
	real_size = b.real_size;
	table.clear();
	table = HTable(tsize);
	for (int i = 0; i < tsize; i++)
	{
		table[i] = b.table[i];
	}
	return *this;
}

HashTable& HashTable::operator=(HashTable&& b)
{
	if (*this == b)
	{
		return *this;
	}
	real_size = b.real_size;
	tsize = b.tsize;
	b.real_size = 0;
	b.tsize = 0;
	table = std::move(b.table);
	return *this;
}

void HashTable::swap(HashTable& b)
{
	std::swap(real_size, b.real_size);
	std::swap(tsize, b.tsize);
	std::swap(table, b.table);
}

void HashTable::clear()
{
	table.clear();
	tsize = 0;
	real_size = 0;
}

bool HashTable::erase(const Key& k)
{
	std::hash<Key> hash_key;
	int del_id = hash_key(k) % tsize;
	if (table[del_id].empty())
	{
		return false;
	}
	auto list_id = std::find_if(table[del_id].begin(), table[del_id].end(),
		[&k](const std::pair<Key, Value>& element) { return element.first == k;});
	table[del_id].erase(list_id);
	real_size--;
	return true;
}

bool HashTable::insert(const Key& k, const Value& v)
{
	std::hash<Key> hash_key;
	int insert_id = hash_key(k) % tsize;
	auto list_id = std::find_if(table[insert_id].begin(), table[insert_id].end(),
		[&k](const std::pair<Key, Value>& element) { return element.first == k;});
	if (list_id != table[insert_id].end())
	{
		return false;
	}
	table[insert_id].emplace_back(k, v);
	real_size++;
	return true;
}

bool HashTable::contains(const Key& k) const
{
	std::hash<Key> hash_key;
	int find_id = hash_key(k) % tsize;
	auto list_id = std::find_if(table[find_id].begin(), table[find_id].end(),
		[&k](const std::pair<Key, Value>& element) { return element.first == k;});
	if (list_id == table[find_id].end())
	{
		return false;
	}
	return true;
}

Value& HashTable::operator[](const Key& k)
{
	std::hash<Key> hash_key;
	int find_id = hash_key(k) % tsize;
	auto list_id = std::find_if(table[find_id].begin(), table[find_id].end(),
		[&k](const std::pair<Key, Value>& element) { return element.first == k;});
	if (list_id == table[find_id].end())
	{
		Value v;
		v.age = 0, v.weight = 0;
		table[find_id].emplace_back(k, v);
		real_size++;
	}
	list_id = std::find_if(table[find_id].begin(), table[find_id].end(),
		[&k](const std::pair<Key, Value>& element) { return element.first == k;});
	return list_id->second;
}

Value& HashTable::at(const Key& k)
{
	std::hash<Key> hash_key;
	int find_id = hash_key(k) % tsize;
	auto list_id = std::find_if(table[find_id].begin(), table[find_id].end(),
		[&k](const std::pair<Key, Value>& element) { return element.first == k;});	
	if (list_id == table[find_id].end())
	{
		throw std::range_error("The range is in error!");
	}
	return list_id->second;
}

const Value& HashTable::at(const Key& k) const
{
	std::hash<Key> hash_key;
	int find_id = hash_key(k) % tsize;
	auto list_id = std::find_if(table[find_id].begin(), table[find_id].end(),
		[&k](const std::pair<Key, Value>& element) { return element.first == k;});
	if (list_id == table[find_id].end())
	{
		throw std::range_error("The range is in error!");
	}
	return list_id->second;
}

size_t HashTable::size() const
{
	return real_size;
}

bool HashTable::empty() const
{
	return real_size == 0;
}

bool operator==(const HashTable& a, const HashTable& b)
{
	if (a.real_size != b.real_size)
	{
		return false;
	}
	for (int i = 0; i < a.tsize; ++i)
	{
		for (auto& list_id : a.table[i])
		{
			if (b.contains(list_id.first))
			{
				Value v_1 = a.at(list_id.first),
					  v_2 = b.at(list_id.first);
				if ((v_1.age != v_2.age) || (v_1.weight != v_2.weight))
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		for (auto& list_id : b.table[i])
		{
			if (a.contains(list_id.first))
			{
				Value v_1 = a.at(list_id.first),
					  v_2 = b.at(list_id.first);
				if ((v_1.age != v_2.age) || (v_1.weight != v_2.weight))
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

bool operator!=(const HashTable& a, const HashTable& b)
{
	return !(a == b);
}
