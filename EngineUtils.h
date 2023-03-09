#pragma once

#include <chrono>

#define NOW _CHRONO steady_clock::now()
#define ELAPSED_TIME(last, now) ((_CHRONO duration<double>) (now - last)).count()

class EngineUtils
{
private:
	static inline std::chrono::steady_clock::time_point _last = {};
	static inline double dt = .0; //deltatime
public:
	static inline void InitDTHandler() { _last = NOW; }
	static inline void ComputeDT()
	{
		_CHRONO steady_clock::time_point _now = NOW;
		dt = ELAPSED_TIME(_last, _now);
		_last = _now;
	}
	static inline double DT() { return dt; }
};
