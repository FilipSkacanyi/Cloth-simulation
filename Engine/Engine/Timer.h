#pragma once
#include <chrono>
class Timer
{


public:
	static Timer* Instance();
	static void Release();
	float DeltaTime();
	void Reset();

	void TimeScale(float f = 1.0f);
	float TimeScale();

	void Tick();

private:

	Timer();
	~Timer();
	static Timer* sInstance;
	std::chrono::system_clock::time_point m_start_time;
	std::chrono::duration<float> m_delta_time;
	float m_time_scale;

};

