#pragma once

#include <map>
#include <vector>
#include <iostream>

static class GC
{
private:
	static inline std::map<void*, int> refCounts = std::map<void*, int>();
public:
	static void RegisterGCPtr(void* _value)
	{
		if (!_value)
			return;
		if (!refCounts.contains(_value))
			refCounts.insert(std::pair(_value, 0));
		refCounts[_value]++;
	}
	static void UnregisterGCPtr(void* _value)
	{
		if (refCounts.contains(_value))
			refCounts[_value]--;
		else
			throw std::exception("AH");
	}
	static void Collect(bool _debug = false)
	{
		std::vector<void*> _toErase = std::vector<void*>();
		for (std::pair<void*, int> _pair : refCounts)
		{
			if (_pair.second > 0)
				continue;
			delete _pair.first;
			_toErase.push_back(_pair.first);
		}
		for (void* _address : _toErase)
			refCounts.erase(_address);
		if (_debug)
			std::cout << "GC : Cleaned " << _toErase.size() << " Objects from memory." << std::endl;
	}
};

