#pragma once

#include "GC.h"

template<typename T>
class GCPtr
{
private:
	T* address = nullptr;
public:
	GCPtr()
	{
		address = new T();
		GC::RegisterGCPtr(address);
	}
	template<typename T_>
	GCPtr(GCPtr<T_> _other)
	{
		address = _other.address;
		GC::RegisterGCPtr(address);
	}
	~GCPtr()
	{
		GC::UnregisterGCPtr(address);
	}
	T& operator *() { return *address; }
};

