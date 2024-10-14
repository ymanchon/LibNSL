/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_MULTITHREADING_INL
#define NSL_MULTITHREADING_INL

# include "../MultiThreading.hpp"

template <typename TRet>
TRet
MultiThreading::GetOne(const String& threadToWait) noexcept
{
	return (MultiThreading::threads.at(threadToWait).Get<TRet>());
}

template <typename TRet, typename TObject, typename... TArgs>
void
Create(const String& threadName, TRet (TObject::*memFun)(TArgs...), TObject* objInstance, TArgs... args) noexcept
{
	MultiThreading::threads.insert(std::make_pair<const String&, Thread>(threadName, Thread(memFun, objInstance, args...)));
}

template <typename TRet, typename... TArgs>
void
MultiThreading::Create(const String& threadName, TRet (*fun)(TArgs...), TArgs... args) noexcept
{
	MultiThreading::threads.insert(std::make_pair<const String&, Thread>(threadName, Thread(fun, args...)));
}

template <typename TRet>
void
MultiThreading::Create(const String& threadName, TRet (*fun)()) noexcept
{
	MultiThreading::threads.insert(std::make_pair<const String&, Thread>(threadName, Thread(fun)));
}

FORCEINLINE bool
MultiThreading::IsAlive(const String& threadName) noexcept
{
	return (MultiThreading::__isExist__(threadName));
}

FORCEINLINE bool
MultiThreading::IsExist(const String& threadName) noexcept
{
	return (MultiThreading::__isExist__(threadName));
}

FORCEINLINE bool
MultiThreading::IsAlive(String&& threadName) noexcept
{
	return (MultiThreading::__isExist__(Memory::Move(threadName)));
}

FORCEINLINE bool
MultiThreading::IsExist(String&& threadName) noexcept
{
	return (MultiThreading::__isExist__(Memory::Move(threadName)));
}

FORCEINLINE bool
MultiThreading::__isExist__(String&& threadName) noexcept
{
	return (MultiThreading::threads.contains(Memory::Move(threadName)));
}

FORCEINLINE bool
MultiThreading::__isExist__(const String& threadName) noexcept
{
	return (MultiThreading::threads.contains(threadName));
}

#endif
