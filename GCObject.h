#pragma once

#include "GarbageCollector.h"

using GC = GarbageCollector;

template<typename T>
class GCObject
{
private:
	T* value = nullptr;
public:
	GCObject(T _value = T())
	{
		value = new T(_value);
		GC::RegisterValue(value);
	}
	~GCObject()
	{
		GC::UnregisterValue(value);
	}
	inline T& operator*() { return *value; }
	inline T* operator->() { return value; }
	inline T& operator[](int _index) { return value[_index]; }
};

