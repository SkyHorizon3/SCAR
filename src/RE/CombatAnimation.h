#pragma once

//#include "RE/A/AnimationSystemUtils.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/T/TESActionData.h"

namespace RE
{
	class Actor;
	class BGSAction;
	class NiPoint3;

	class CombatAnimation : public TESActionData
	{
	public:
		virtual ~CombatAnimation() override;  // 00

		enum class ANIM : uint32_t
		{
			kActionRightAttack,
			kActionRightRelease,
			kActionRightPowerAttack,
			kActionLeftAttack,
			kActionLeftRelease,
			kActionRightAttack2,   // ranged?
			kActionRightRelease2,  // ranged?
			kActionRightInterrupt,
			kActionSneak,
			kActionActivate
		};

		enum class LoadedStatus : uint32_t
		{
			kNone,
			kSuccess,
			kFail
		};

		/*
		CombatAnimation* Ctor(Actor* a_actor, ANIM a_anim);
		CombatAnimation* Ctor(Actor* a_actor, TESObjectREFR* a_target, ANIM a_anim);
		CombatAnimation* Ctor(Actor* a_actor, BGSAction* a_action);

		static CombatAnimation* Create(Actor* a_actor, ANIM a_anim);
		static CombatAnimation* Create(Actor* a_actor, BGSAction* a_action);

		static bool Execute(Actor* a_actor, CombatAnimation::ANIM a_anim);
		static bool Execute(Actor* a_actor, TESObjectREFR* target, CombatAnimation::ANIM a_anim);

		bool Check();
		bool Execute();  // { return Process(); }
		bool GetEventData(const BSFixedString& event_name, float& event_time);
		bool GetEventData(const BSFixedString& event_name, float& event_time, NiPoint3& translation);
		float GetEventTime(const BSFixedString& event_name);
		float GetLength();
		bool GetTranslation(NiPoint3& translation);
		bool LoadClipData();
		*/

		bool Execute();
		CombatAnimation* Ctor(Actor* a_actor, ANIM a_anim);
		static CombatAnimation* Create(Actor* a_actor, ANIM a_anim);

		// members
		std::array<std::uint64_t, 4> data;
		LoadedStatus status;
		uint32_t pad84;  //84
	};
	static_assert(sizeof(CombatAnimation) == 0x88);
}

namespace RE
{
	class hkbNode;

	struct hkbNodeInfo
	{
		void* unk00;            //00
		int64_t unk08;          //08
		int64_t unk10;          //10
		void* unk18;            //18
		char unk20[48];         //20
		hkbNode* nodeTemplate;  //50
		hkbNode* nodeClone;     //58
		hkbNode* behavior;      //60
		int64_t unk68;          //68
		int64_t unk70;          //70
		int64_t unk78;          //78
		int64_t unk80;          //80
		bool unk88;             //88
	};
	static_assert(sizeof(hkbNodeInfo) == 0x90);

	class hkCustomAttributes;

	/// Reflection information for any reflected type.
	class hkClass
	{
	public:
		enum FlagValues
		{
			kFlagsNone = 0,
			kFlagsNotSerializable = 1
		};
		using Flags = stl::enumeration<FlagValues, std::uint32_t>;

		const char* name;                            // 00
		const hkClass* parent;                       // 08
		std::int32_t objectSize;                     // 10
		std::int32_t numImplementedInterfaces;       // 14
		const class hkClassEnum* declaredEnums;      // 18
		std::int32_t numDeclaredEnums;               // 20
		std::uint32_t pad24;                         // 24
		const class hkClassMember* declaredMembers;  // 28
		std::int32_t numDeclaredMembers;             // 30
		std::uint32_t pad34;                         // 34
		const void* defaults;                        // 38
		const hkCustomAttributes* attributes;        // 40
		Flags flags;                                 // 48
		std::int32_t describedVersion;               // 4C
	};
	static_assert(sizeof(hkClass) == 0x50);
}