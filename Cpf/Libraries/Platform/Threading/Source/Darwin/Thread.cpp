//////////////////////////////////////////////////////////////////////////
#include "Threading/Thread.hpp"
#include "Functional.hpp"
#include "Move.hpp"
#include <thread>
#include <emmintrin.h>

using namespace Cpf;
using namespace Threading;

namespace
{
	void* OsThreadRunner(void* startData)
	{
		Cpf::Function<void(void)>* tramp =
			reinterpret_cast<Cpf::Function<void(void)>*>(startData);
		(*tramp)();
		delete tramp;
		return nullptr;
	}
}


void Thread::_Start(Cpf::Function<void (void)> && f)
{
	Function<void(void)>* funcData = new Function<void(void)>(Cpf::Move(f));
	pthread_create(&NativeHandle(), nullptr, OsThreadRunner, funcData);
}


/**
@brief Default constructor.  Creates a thread object in an invalid state.
*/
Thread::Thread()
: m_Handle(InvalidThread)
{
}


/**
@brief Destructor.  Does not attempt to validate shutdown of the thread or force it to shutdown.
*/
Thread::~Thread()
{
}


/**
@brief Blocks until the thread exits.
*/
void Thread::Join()
{
	pthread_join(m_Handle, nullptr);
}


/**
@brief Put the thread to sleep for the given time value.
*/
void Thread::Sleep(const Time::Value& tp)
{
	timespec delay;
	timespec rem;
	uint64_t nstime = Time::Ns(tp);
	delay.tv_sec = nstime/1000000000;
	delay.tv_nsec = nstime%1000000000;
	while (nanosleep(&delay, &rem)!=0 && errno==EINTR)
	{
		delay = rem;
	}
}


/**
@brief Put the thread into a pause state momentarily.  Used in spin locks and exponential back off.
*/
void Thread::Pause()
{
	_mm_pause();
}


/**
@brief Get time information about this thread.
@param userTime Time spent in user code.
@param kernelTime Time spent in kernel code.
*/
void Thread::GetThreadTimes(Time::Value& userTime, Time::Value& kernelTime)
{
	struct rusage ruse;
	getrusage(RUSAGE_SELF, &ruse);
	userTime = Time::Ns(ruse.ru_utime.tv_usec + ruse.ru_utime.tv_sec * 1000000000);
	kernelTime = Time::Ns(ruse.ru_stime.tv_usec + ruse.ru_stime.tv_sec * 1000000000);
}


/**
@brief Set the name of the thread for debugging and profiling systems.
*/
void Thread::SetName(const char* name)
{
	pthread_setname_np(name);
}


/**
*/
int Thread::GetHardwareThreadCount()
{
	return std::thread::hardware_concurrency();
}


/**
*/
Thread_t& Thread::NativeHandle()
{
	return m_Handle;
}
