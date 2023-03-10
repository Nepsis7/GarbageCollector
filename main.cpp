#include <iostream>
#include <chrono>
#include "GCPtr.h"

void ManualCollectExample()
{
	while (true)
	{
		for (size_t i = 0; i < 1000000; i++)
		{
			GCPtr<int> ptr; //memory allocated, refCount : 1
			{
				GCPtr<int> ptr2(ptr); //refCount : 2
				{
					GCPtr<int> ptr3(ptr2); //refCount : 3
				} //ptr3 is Destroyed, refCount : 2
			} //ptr2 is Destroyed, refCount : 1
		} //ptr is Destroyed, refCount : 0
		GC::Collect(true);
	}
}

#define NOW std::chrono::steady_clock::now()
#define DURATION_MS(now, last) std::chrono::duration_cast<std::chrono::microseconds>(now - last).count()
#define TIMEPOINT std::chrono::time_point<std::chrono::steady_clock>

void AutomatedCollectExample()
{
	double _delay = 5.;
	double _timer = 0.;
	double _deltatime = 0.f;
	TIMEPOINT _last = NOW;
	TIMEPOINT _now = _last;
	while (true)
	{
		_now = NOW;
		_deltatime = DURATION_MS(_now, _last) / 1000000.;
		_last = _now;
		_timer += _deltatime;
		if (_timer >= _delay)
		{
			_timer -= _delay;
			GC::Collect(true);
		}
		//std::cout << _deltatime << std::endl;
		GCPtr<int> ptr; //memory allocated, refCount : 1
		{
			GCPtr<int> ptr2(ptr); //refCount : 2
			{
				GCPtr<int> ptr3(ptr2); //refCount : 3
			} //ptr3 is Destroyed, refCount : 2
		} //ptr2 is Destroyed, refCount : 1
	} //ptr is Destroyed, refCount : 0
}

int main()
{
	//use your IDE's memory visualizer
	//ManualCollectExample();
	AutomatedCollectExample();
}

