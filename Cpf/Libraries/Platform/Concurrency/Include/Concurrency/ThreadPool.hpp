//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Concurrency/Scheduler.hpp"

namespace Cpf
{
	namespace Concurrency
	{
		/** @brief A thread pool implementation based on the concurrency
		 * scheduler.  The scheduler handles the heavy lifting in terms
		 * of maintaining the threads and waking/sleeping the threads while
		 * this simply pushes work as first one instructions.
		 */
		class ThreadPool
		{
		public:
			ThreadPool();
			~ThreadPool();

			bool Initialize(Platform::Threading::Thread::Group&&);
			void Shutdown();

			// TODO: Make this promise/future based, but it will need to be a
			// custom promise to make it actually useful, C++11 promises are
			// way too primitive.

			using Task = Scheduler::PayloadFunc_t;
			void Enqueue(Task, void* context);

			int GetAvailableThreads() const;
			void SetActiveThreads(int count);

			Scheduler& GetScheduler() { return mScheduler; }

		private:
			Scheduler mScheduler;
			Scheduler::Queue mQueue;
		};
	}
}
