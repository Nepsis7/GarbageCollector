#include "GarbageCollector.h"

void GarbageCollector::RefreshCollectTimer(double _dt)
{
	timer += _dt;
	if (timer < collectionDelay)
		return;
	timer -= collectionDelay;
	Collect();
}

void GarbageCollector::MarkAllUnused()
{
	for (std::pair<void*, int> _pair : valuesRefCounts)
		valuesRefCounts[_pair.first] = 0;
}

void GarbageCollector::Collect(bool _debug)
{
	std::vector<void*> _deletedKeys = std::vector<void*>();
	for (std::pair<void*, int> _pair : valuesRefCounts)
		if (_pair.second == 0)
		{
			//std::cout << "deleted " << _pair.first << std::endl;
			_deletedKeys.push_back(_pair.first);
			delete _pair.first;
		}
	for (void* _key : _deletedKeys)
		valuesRefCounts.erase(_key);
	std::cout << "deleted " << _deletedKeys.size() << " GCObjects." << std::endl;
}
