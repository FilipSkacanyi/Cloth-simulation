#include "Timer.h"

Timer* Timer::sInstance = nullptr;

Timer::Timer()
{
	Reset();
	TimeScale(1.0f);
	m_delta_time = std::chrono::duration<float>(0.0f);
}


Timer::~Timer()
{
}

Timer * Timer::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new Timer();
	}


	return sInstance;
}

void Timer::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

float Timer::DeltaTime()
{
	return m_delta_time.count();
}

void Timer::Reset()
{
	m_start_time = std::chrono::system_clock::now();
}

void Timer::TimeScale(float f)
{
	m_time_scale = f;
}

float Timer::TimeScale()
{
	return m_time_scale;
}

void Timer::Tick()
{
	m_delta_time = std::chrono::system_clock::now() - m_start_time;
}
