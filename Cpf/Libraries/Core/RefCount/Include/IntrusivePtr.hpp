/**
* @brief Declares the stream class.
*/
#pragma once
#include <RefCounted.hpp>


namespace CPF
{
	/**
	 * @brief An intrusive reference pointer.
	 * @tparam TARGET Type of the target.
	 * @tparam BASE Storage pointer type.
	 */
	template<typename TARGET>
	class IntrusivePtr
	{
	public:
		IntrusivePtr();
		explicit IntrusivePtr(TARGET* rhs);
		IntrusivePtr(const IntrusivePtr& rhs);
		template<typename SRC>
		explicit IntrusivePtr(const IntrusivePtr<SRC>& rhs) : mpTarget(rhs) {_AddRef();}
		IntrusivePtr(IntrusivePtr&& rhs) noexcept;
		~IntrusivePtr();

		IntrusivePtr& operator = (const IntrusivePtr& rhs);
		IntrusivePtr& operator = (IntrusivePtr&& rhs) noexcept;

		bool operator ==(const IntrusivePtr& rhs) const;
		bool operator !=(const IntrusivePtr& rhs) const;
		bool operator <(const IntrusivePtr& rhs) const;
		bool operator <=(const IntrusivePtr& rhs) const;
		bool operator >(const IntrusivePtr& rhs) const;
		bool operator >=(const IntrusivePtr& rhs) const;

		operator bool() const;

		TARGET& operator * () const;
		TARGET* operator -> () const;

		operator TARGET*() const;

		// Manipulate internal pointer with modification of ref count.
		void Assign(TARGET* rhs);

		// Manipulate internal pointer without modification of ref count.
		void Adopt(TARGET* rhs);
		void Abandon();

		// Internal access.
		TARGET* Ptr() const { return mpTarget; }

		// 
		void** AsVoidPP() { return reinterpret_cast<void**>(&mpTarget); }
		TARGET** AsTypePP() { return &mpTarget; }
		template <typename TYPE>
		TYPE* As() { return static_cast<TYPE*>(Cast()); }
		template <typename TYPE>
		TYPE** AsPP() { return reinterpret_cast<TYPE**>(&mpTarget); }

		// Safe variations.
		void AddRef() { _AddRef(); }
		void Release() { _Release(); }

	private:
		void _AddRef();
		void _Release();

		TARGET* Cast() const;

		TARGET* mpTarget;
	};


	template<typename TARGET>
	IntrusivePtr<TARGET>::IntrusivePtr()
		: mpTarget(nullptr)
	{}


	template<typename TARGET>
	IntrusivePtr<TARGET>::IntrusivePtr(TARGET* rhs)
		: mpTarget(rhs)
	{
	}


	template<typename TARGET>
	IntrusivePtr<TARGET>::IntrusivePtr(const IntrusivePtr& rhs)
		: mpTarget(reinterpret_cast<TARGET*>(rhs.mpTarget))
	{
		if (mpTarget)
			Cast()->AddRef();
	}


	template<typename TARGET>
	IntrusivePtr<TARGET>::IntrusivePtr(IntrusivePtr&& rhs) noexcept
		: mpTarget(rhs.mpTarget)
	{
		rhs.mpTarget = nullptr;
	}


	template<typename TARGET>
	IntrusivePtr<TARGET>::~IntrusivePtr()
	{
		_Release();
	}

	template<typename TARGET>
	IntrusivePtr<TARGET>& IntrusivePtr<TARGET>::operator = (const IntrusivePtr& rhs)
	{
		if (rhs.mpTarget == mpTarget)
			return *this;
		_Release();
		mpTarget = rhs.mpTarget;
		_AddRef();
		return *this;
	}


	template<typename TARGET>
	IntrusivePtr<TARGET>& IntrusivePtr<TARGET>::operator = (IntrusivePtr&& rhs) noexcept
	{
		if (rhs.mpTarget == mpTarget)
		{
			rhs.mpTarget = nullptr;
			_Release();
			return *this;
		}
		_Release();
		mpTarget = rhs.mpTarget;
		rhs.mpTarget = nullptr;
		return *this;
	}


	template<typename TARGET>
	bool IntrusivePtr<TARGET>::operator ==(const IntrusivePtr& rhs) const
	{
		return mpTarget == rhs.mpTarget;
	}


	template<typename TARGET>
	bool IntrusivePtr<TARGET>::operator !=(const IntrusivePtr& rhs) const
	{
		return mpTarget != rhs.mpTarget;
	}


	template<typename TARGET>
	bool IntrusivePtr<TARGET>::operator <(const IntrusivePtr& rhs) const
	{
		return mpTarget < rhs.mpTarget;
	}


	template<typename TARGET>
	bool IntrusivePtr<TARGET>::operator <=(const IntrusivePtr& rhs) const
	{
		return mpTarget <= rhs.mpTarget;
	}


	template<typename TARGET>
	bool IntrusivePtr<TARGET>::operator >(const IntrusivePtr& rhs) const
	{
		return mpTarget > rhs.mpTarget;
	}


	template<typename TARGET>
	bool IntrusivePtr<TARGET>::operator >=(const IntrusivePtr& rhs) const
	{
		return mpTarget >= rhs.mpTarget;
	}


	template<typename TARGET>
	IntrusivePtr<TARGET>::operator bool() const
	{
		return mpTarget != nullptr;
	}

	template<typename TARGET>
	TARGET& IntrusivePtr<TARGET>::operator * () const
	{
		return *Cast();
	}


	template<typename TARGET>
	TARGET* IntrusivePtr<TARGET>::operator -> () const
	{
		return Cast();
	}


	template<typename TARGET>
	IntrusivePtr<TARGET>::operator TARGET*() const
	{
		return Cast();
	}

	template<typename TARGET>
	void IntrusivePtr<TARGET>::Assign(TARGET* rhs)
	{
		if (rhs == mpTarget)
			return;
		_Release();
		mpTarget = rhs;
		_AddRef();
	}

	template<typename TARGET>
	void IntrusivePtr<TARGET>::Adopt(TARGET* rhs)
	{
		if (rhs == mpTarget)
			return;
		_Release();
		mpTarget = rhs;
	}


	template<typename TARGET>
	void IntrusivePtr<TARGET>::Abandon()
	{
		mpTarget = nullptr;
	}


	template<typename TARGET>
	void IntrusivePtr<TARGET>::_AddRef()
	{
		if (mpTarget)
		{
			Cast()->AddRef();
		}
	}


	template<typename TARGET>
	void IntrusivePtr<TARGET>::_Release()
	{
		if (mpTarget)
		{
			if (Cast()->Release() == 0)
				mpTarget = nullptr;
		}
	}

	template<typename TARGET>
	TARGET* IntrusivePtr<TARGET>::Cast() const
	{
		return reinterpret_cast<TARGET*>(mpTarget);
	}
}
