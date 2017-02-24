//////////////////////////////////////////////////////////////////////////
#include "MovementSystem.hpp"
#include "InstanceSystem.hpp"
#include "ExperimentalD3D12.hpp"
#include "MultiCore/Pipeline.hpp"
#include "Math/Vector3v.hpp"
#include "Math/Matrix33v.hpp"

#include "EntityService/Interfaces/iEntity.hpp"
#include "EntityService/Interfaces/Components/iTransformComponent.hpp"
#include "Threading/ScopedLock.hpp"

using namespace Cpf;
using namespace Math;
using namespace Platform;
using namespace EntityService;

bool MoverSystem::MoverComponent::Install()
{
	return ComponentFactoryInstall(iMoverComponent::kIID, &MoverSystem::MoverComponent::Create);
}

bool MoverSystem::MoverComponent::Remove()
{
	return ComponentFactoryRemove(iMoverComponent::kIID);
}

iComponent* MoverSystem::MoverComponent::Create(MultiCore::System* system)
{
	return static_cast<iComponent*>(new MoverComponent(system));
}

bool MoverSystem::MoverComponent::QueryInterface(InterfaceID id, void** outPtr)
{
	if (id.GetID() == iMoverComponent::kIID.GetID())
	{
		iMoverComponent* mover = static_cast<iMoverComponent*>(this);
		mover->AddRef();
		*outPtr = mover;
		return true;
	}

	*outPtr = nullptr;
	return false;
}



MoverSystem::MoverSystem(const String& name, const Dependencies& deps, const Desc* desc)
	: System(name, deps)
	, mpApp(nullptr)
	, mpInstances(nullptr)
	, mpTime(nullptr)
	, mClockID(desc->mTimerID)
	, mInstanceID(desc->mInstanceID)
	, mEnableMovement(true)
	, mUseEBus(false)
{
	mpThreadStage = MultiCore::Stage::Create<EntityStage>(this, "Mover");
	mpThreadStage->SetDependencies({ { mInstanceID, StageID(InstanceSystem::kBegin.ID) } });
	AddStage(mpThreadStage);

	mpEBusStage = MultiCore::Stage::Create<EntityStage>(this, "Mover EBus");
	mpEBusStage->SetDependencies({ { mInstanceID, StageID(InstanceSystem::kBegin.ID) } });
	AddStage(mpEBusStage);
	mpEBusStage->SetEnabled(false);
}

InstanceSystem* MoverSystem::GetInstanceSystem() const
{
	return mpInstances;
}

bool MoverSystem::Configure()
{
	mpTime = static_cast<Timer*>(GetOwner()->GetSystem(mClockID));
	mpInstances = static_cast<InstanceSystem*>(GetOwner()->GetSystem(mInstanceID));

	return mpTime && mpInstances;
}

bool MoverSystem::Install()
{
	return System::Install(kID, &MoverSystem::_Creator);
}
bool MoverSystem::Remove()
{
	return System::Remove(kID);
}

void MoverSystem::EnableMovement(bool flag)
{
	mEnableMovement = flag;

	mpThreadStage->SetEnabled(flag && !mUseEBus);
	mpEBusStage->SetEnabled(flag && mUseEBus);
}

void MoverSystem::UseEBus(bool flag)
{
	mUseEBus = flag;
	EnableMovement(mEnableMovement);
}

MultiCore::System* MoverSystem::_Creator(const String& name, const System::Desc* desc, const Dependencies& deps)
{
	return new MoverSystem(name, deps, static_cast<const Desc*>(desc));
}


//////////////////////////////////////////////////////////////////////////
MoverSystem::MoverComponent::MoverComponent(MultiCore::System* owner)
	: mpMover(static_cast<MoverSystem*>(owner))
{}

//////////////////////////////////////////////////////////////////////////
ComponentID MoverSystem::MoverComponent::GetID() const
{
	return kID;
}

void MoverSystem::MoverComponent::Activate()
{
	mpMover->mpThreadStage->AddUpdate(mpMover, GetEntity(), &MoverComponent::_Threaded);
	mpMover->mpEBusStage->AddUpdate(mpMover, GetEntity(), &MoverComponent::_EBus);
}

void MoverSystem::MoverComponent::Deactivate()
{
	mpMover->mpThreadStage->RemoveUpdate(mpMover, GetEntity(), &MoverComponent::_Threaded);
	mpMover->mpEBusStage->RemoveUpdate(mpMover, GetEntity(), &MoverComponent::_EBus);
}

void MoverSystem::MoverComponent::_Threaded(System* system, iEntity* object)
{
	MoverSystem* mover = static_cast<MoverSystem*>(system);
	const Timer* timer = mover->mpTime;

	int i = int(object->GetID().GetID());
	int count = ExperimentalD3D12::kInstancesPerDimension;
	int xc = (i % count);
	int yc = (i / count) % count;
	int zc = (i / (count * count)) % count;

	Vector3fv pos((xc - count / 2) * 1.5f, (yc - count / 2) * 1.5f, (zc - count / 2) * 1.5f);
	float magnitude = Magnitude(pos + Vector3f(0.0f, 50.0f, 0.0f)) * 0.03f;
	magnitude *= magnitude;
	float time = float(Time::Seconds(timer->GetTime()));
	float angle = sinf(0.25f * time);
	pos.x = sinf(angle * magnitude) * pos.x - cosf(angle * magnitude) * pos.z;
	pos.y = (sinf(angle) + 0.5f) * pos.y * magnitude;
	pos.z = cosf(angle * magnitude) * pos.x + sinf(angle * magnitude) * pos.z;

	iTransformComponent* transform = object->GetComponent<iTransformComponent>();

	Matrix33fv orientation = Matrix33fv::AxisAngle(Vector3fv(0.0f, 1.0f, 0.0f), time);

	Instance* instances = mover->GetInstanceSystem()->GetInstances();
	instances[i].mScale = Vector3f(1.0f, 1.0f, 1.0f);
	instances[i].mOrientation0 = orientation[0].xyz;
	instances[i].mOrientation1 = orientation[1].xyz;
	instances[i].mOrientation2 = orientation[2].xyz;
	instances[i].mTranslation = Vector3f(pos.xyz);
}

void MoverSystem::MoverComponent::_EBus(System* system, iEntity* object)
{
	MoverSystem* mover = static_cast<MoverSystem*>(system);
	Threading::ScopedLock<Threading::Mutex> lock(mover->mMutex);

	const Timer* timer = mover->mpTime;

	int i = int(object->GetID().GetID());
	int count = ExperimentalD3D12::kInstancesPerDimension;
	int xc = (i % count);
	int yc = (i / count) % count;
	int zc = (i / (count * count)) % count;

	Vector3fv pos((xc - count / 2) * 1.5f, (yc - count / 2) * 1.5f, (zc - count / 2) * 1.5f);
	float magnitude = Magnitude(pos + Vector3f(0.0f, 50.0f, 0.0f)) * 0.03f;
	magnitude *= magnitude;
	float time = float(Time::Seconds(timer->GetTime()));
	float angle = sinf(0.25f * time);
	pos.x = sinf(angle * magnitude) * pos.x - cosf(angle * magnitude) * pos.z;
	pos.y = (sinf(angle) + 0.5f) * pos.y * magnitude;
	pos.z = cosf(angle * magnitude) * pos.x + sinf(angle * magnitude) * pos.z;

	iTransformComponent* transform = object->GetComponent<iTransformComponent>();

	Matrix33fv orientation = Matrix33fv::AxisAngle(Vector3fv(0.0f, 1.0f, 0.0f), time);

	Instance* instances = mover->GetInstanceSystem()->GetInstances();
	instances[i].mScale = Vector3f(1.0f, 1.0f, 1.0f);
	instances[i].mOrientation0 = orientation[0].xyz;
	instances[i].mOrientation1 = orientation[1].xyz;
	instances[i].mOrientation2 = orientation[2].xyz;
	instances[i].mTranslation = Vector3f(pos.xyz);
}
