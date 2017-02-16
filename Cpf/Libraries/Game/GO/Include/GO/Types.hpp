//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "RefCounted.hpp"
#include "Vector.hpp"
#include "Pair.hpp"
#include "Threading/Mutex.hpp"
#include "Threading/ScopedLock.hpp"
#include "Concurrency/ThreadContext.hpp"

namespace Cpf
{
	namespace GO
	{
		using ObjectID = int64_t;
		constexpr ObjectID kInvalidObjectID = int64_t(-1);

		using ComponentID = int64_t;
		constexpr ComponentID kInvalidComponentID = int64_t(-1);

		using SystemID = int64_t;
		constexpr ComponentID kInvalidSystemID = int64_t(-1);

		class Object;
		class Component;
		class Service;
		class System;

		// Stages within the service are update loops.  They work in a similar fashion to
		// 3D pipeline stages though Stages can be merged and/or executed in parallel
		// when there are no direct conflicts in data descriptions.
		// TODO: Decide where to put this, may not want it in GO.
		// TODO: This is a really bad implementation which will be important to fix later.
		class Stage : public tRefCounted<iRefCounted>
		{
		public:
			using FuncType_t = void(*)(Object*);

			void AddUpdate(Object* o, FuncType_t f)
			{
				Platform::Threading::ScopedLock<Platform::Threading::Mutex> lock(mLock);
				mUpdates.push_back({ f, o });
			}
			void RemoveUpdate(Object* o, FuncType_t f)
			{
				Platform::Threading::ScopedLock<Platform::Threading::Mutex> lock(mLock);
				UpdatePair_t p(f, o);
				for (auto ibegin = mUpdates.begin(), iend = mUpdates.end(); ibegin!=iend; ++ibegin)
				{
					if (*ibegin == p)
					{
						mUpdates.erase(ibegin);
						return;
					}
				}
				// Should be in the list.
				CPF_ASSERT_ALWAYS;
			}

			static void Update(Concurrency::ThreadContext& tc, void* context)
			{
				Stage& self = *reinterpret_cast<Stage*>(context);

				int32_t threadIndex = tc.ThreadId();
				int32_t threadCount = tc.ThreadCount();
				int32_t workCount = int32_t(self.mUpdates.size());
				int32_t partitionSize = int32_t(workCount) / threadCount;
				int32_t start = threadIndex * partitionSize;
				int32_t end = start + partitionSize;
				int32_t overflow = workCount - (threadCount*partitionSize);
				if (overflow > 0 && threadIndex == 0)
					end += overflow;

				for (int i = start; i < end; ++i)
				{
					const UpdatePair_t& up = self.mUpdates[i];
					(*up.first)(up.second);
				}
			}

		private:
			using UpdatePair_t = Pair<FuncType_t, Object*>;
			Vector<UpdatePair_t> mUpdates;
			Platform::Threading::Mutex mLock;
		};
	}
}
