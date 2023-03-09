#include <iostream>
#include <vector>
#include <windows.h>
#include "GCObject.h"
#include "EngineUtils.h"
using GC = GarbageCollector;

struct ExampleStruct
{
public:
	int value = 0;
};

void ExampleTick()
{
	// make a garbage collected object
	GCObject<ExampleStruct> _gco = GCObject<ExampleStruct>(); 
	// operate on it like a pointer
	(*_gco).value = 3; 
	_gco->value = 3;
	_gco[0].value = 3;
	// leave it uncleared
}

void EngineInit()
{
	std::cout << "Press VK_ESCAPE to exit" << std::endl;
	GarbageCollector::SetCollectionDelay(3);
	EngineUtils::InitDTHandler();
}

void EngineTick()
{
	while ((GetAsyncKeyState(VK_ESCAPE) | 0b10) > 0)
	{
		EngineUtils::ComputeDT();
		GC::RefreshCollectTimer(EngineUtils::DT());
		ExampleTick();
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //feel free to remove that
	EngineInit();
	EngineTick();
	GC::MarkAllUnused();
	GC::Collect();
	return EXIT_SUCCESS;
}

