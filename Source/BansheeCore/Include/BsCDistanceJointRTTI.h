//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsCorePrerequisites.h"
#include "BsRTTIType.h"
#include "BsCDistanceJoint.h"
#include "BsGameObjectRTTI.h"

namespace BansheeEngine
{
	/** @cond RTTI */
	/** @addtogroup RTTI-Impl-Core
	 *  @{
	 */

	class BS_CORE_EXPORT CDistanceJointRTTI : public RTTIType<CDistanceJoint, CJoint, CDistanceJointRTTI>
	{
		BS_PLAIN_MEMBER_NAMED(mFlag, mDesc.flag)
		BS_PLAIN_MEMBER_NAMED(mMinDistance, mDesc.minDistance)
		BS_PLAIN_MEMBER_NAMED(mMaxDistance, mDesc.maxDistance)
		BS_PLAIN_MEMBER_NAMED(mTolerance, mDesc.tolerance)
		BS_PLAIN_MEMBER_NAMED(mSpringDamping, mDesc.spring.damping)
		BS_PLAIN_MEMBER_NAMED(mSpringStiffness, mDesc.spring.stiffness)

	public:
		CDistanceJointRTTI()
		{
			BS_ADD_PLAIN_FIELD(mFlag, 0);
			BS_ADD_PLAIN_FIELD(mMinDistance, 1);
			BS_ADD_PLAIN_FIELD(mMaxDistance, 2);
			BS_ADD_PLAIN_FIELD(mTolerance, 3);
			BS_ADD_PLAIN_FIELD(mSpringDamping, 4);
			BS_ADD_PLAIN_FIELD(mSpringStiffness, 5);
		}

		const String& getRTTIName() override
		{
			static String name = "CDistanceJoint";
			return name;
		}

		UINT32 getRTTIId() override
		{
			return TID_CDistanceJoint;
		}

		SPtr<IReflectable> newRTTIObject() override
		{
			return GameObjectRTTI::createGameObject<CDistanceJoint>();
		}
	};

	/** @} */
	/** @endcond */
}