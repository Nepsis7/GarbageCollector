#pragma once
#include <iostream>
#include <map>
#include <vector>

class GarbageCollector
{
private:
	static inline double timer = .0;
	static inline int collectionDelay = 5;
	static inline std::map<void*, int> valuesRefCounts = std::map<void*, int>();
public:
	static inline void SetCollectionDelay(int _delay) { collectionDelay = _delay; }
	static void RefreshCollectTimer(double _dt);
	static void MarkAllUnused();
	static void Collect(bool _debug = false);
	template<typename T>
	static void RegisterValue(T* _ptr)
	{
		void* _vPtr = (void*)_ptr;
		if (valuesRefCounts.contains(_vPtr))
		{
			valuesRefCounts[_vPtr]++;
			return;
		}
		valuesRefCounts.insert(std::pair(_vPtr, 1));
	}
	template<typename T>
	static void UnregisterValue(T* _ptr)
	{
		void* _vPtr = (void*)_ptr;
		if (valuesRefCounts.contains(_vPtr))
		{
			valuesRefCounts[_vPtr]--;
			if (valuesRefCounts[_vPtr] < 0)
				throw std::exception("t'es con");
		}
	}
};

