//////////////////////////////////////////////////////////////////////////
#pragma once


namespace Cpf
{
	namespace Platform
	{
		namespace Threading
		{
			//////////////////////////////////////////////////////////////////////////
			/// Take a lock on the given primitive and release it on scope exit.
			//////////////////////////////////////////////////////////////////////////
			template<typename tPrimitive>
			class ScopedLock
			{
			public:
				//////////////////////////////////////////////////////////////////////////
				ScopedLock(tPrimitive& prim);
				~ScopedLock();

			private:
				//////////////////////////////////////////////////////////////////////////
				ScopedLock(const ScopedLock&) = delete;
				ScopedLock(ScopedLock&&) = delete;
				ScopedLock& operator =(const ScopedLock&) = delete;
				ScopedLock& operator =(ScopedLock&&) = delete;

				//////////////////////////////////////////////////////////////////////////
				tPrimitive* mpPrimitive;
			};


			/**
			 * @brief Create a scoped lock.
			 */
			template<typename tPrimitive> inline
				ScopedLock<tPrimitive>::ScopedLock(tPrimitive& prim)
				: mpPrimitive(&prim)
			{
				mpPrimitive->Acquire();
			}


			/**
			 * @brief Release the primitive on scope exit.
			 */
			template<typename tPrimitive> inline
				ScopedLock<tPrimitive>::~ScopedLock()
			{
				mpPrimitive->Release();
			}
		}
	}
}