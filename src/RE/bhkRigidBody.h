#pragma once

#include "RE/H/hkQuaternion.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class bhkRigidBodyT : bhkRigidBody
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkRigidBodyT;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkRigidBodyT;

		hkQuaternion rotation;  // 40
		hkVector4 translation;  // 50
	};
	static_assert(sizeof(bhkRigidBodyT) == 0x60);
}