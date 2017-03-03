//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCount.hpp"
#include "EntityService/Types.hpp"

namespace Cpf
{
	namespace EntityService
	{
		struct iEntity;

		struct iComponent : public iUnknown
		{
			static constexpr auto kIID = InterfaceID("iComponent Interface"_crc64);

			virtual iEntity* GetEntity() const = 0;
			virtual void SetEntity(iEntity* entity) = 0;

			virtual void Initialize() = 0;
			virtual void Shutdown() = 0;

			virtual void Activate() = 0;
			virtual void Deactivate() = 0;
		};
	}
}