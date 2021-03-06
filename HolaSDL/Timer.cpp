#include "Timer.h"



Timer::Timer()
{
	Reset();
	_TimeScale = 1.0f;
}


Timer::~Timer()
{
}

void Timer::Reset()
{
	_StartTicks = SDL_GetTicks();
	_ElapsedTicks = 0;
	_DeltaTime = 0.0f;
	offset = 0;
}

float Timer::DeltaTime()
{
	return _DeltaTime;
}

void Timer::TimeScale(float t)
{
	_TimeScale = t;
}

float Timer::TimeScale()
{
	return _TimeScale;
}

void Timer::Update()
{
	_ElapsedTicks = SDL_GetTicks() - _StartTicks - offset;
	_DeltaTime = _ElapsedTicks * 0.001f;

}