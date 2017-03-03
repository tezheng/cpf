//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Hash/HashString.hpp"
#include "MultiCore/System.hpp"
#include "EntityService/Types.hpp"
#include "EntityService/Interfaces/Stages/iEntityStage.hpp"
#include "EntityService/Interfaces/iSystem.hpp"

namespace Cpf
{
	namespace EntityService
	{
		struct iTimerSystem : iSystem
		{
			virtual Platform::Time::Value GetTime() const = 0;
			virtual float GetDeltaTime() const = 0;
		};

		class Timer
			: public MultiCore::System
		{
		public:
			//
			static constexpr auto kID = "Timer System"_hashString;
			static constexpr auto kUpdate = "Update"_hashString;

			// Registration.
			static bool Install();
			static bool Remove();

			// Timer interface.
			Platform::Time::Value GetTime() const;
			float GetDeltaTime() const;
			bool IsPaused() const;
			void SetPause(bool flag);
			void Pause();
			void Resume();

		private:
			// Construction/Destruction.
			Timer(MultiCore::Pipeline* owner, const char* name);
			~Timer() override;

			//
			static System* Creator(MultiCore::Pipeline* owner, const char* name, const Desc*);

			// Internal update function.
			static void _Update(Concurrency::ThreadContext&, void*);

			// Implementation data.
			Platform::Time::Value mTime;
			Platform::Time::Value mStart;
			Platform::Time::Value mDelta;
			bool mPaused;

			// The internal update stage.
			IntrusivePtr<MultiCore::SingleUpdateStage> mpUpdate;
		};
	}
}