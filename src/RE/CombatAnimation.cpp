#include "CombatAnimation.h"
#include "RE/M/MemoryManager.h"

namespace RE
{
	bool CombatAnimation::Execute()
	{
		using func_t = bool(CombatAnimation*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43239, 44440) };
		return func(this);
	}

	CombatAnimation* CombatAnimation::Ctor(Actor* a_actor, ANIM a_anim)
	{
		using func_t = CombatAnimation*(CombatAnimation*, Actor*, ANIM);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43235, 44436) };
		auto combatAnimaiton = func(this, a_actor, a_anim);
		stl::emplace_vtable<CombatAnimation>(combatAnimaiton);
		return combatAnimaiton;
	}

	CombatAnimation* CombatAnimation::Create(Actor* a_actor, CombatAnimation::ANIM a_anim)
	{
		auto combatAnimation = malloc<CombatAnimation>();
		std::memset(reinterpret_cast<void*>(combatAnimation), 0, sizeof(CombatAnimation));
		if (combatAnimation) {
			combatAnimation->Ctor(a_actor, a_anim);
		}
		return combatAnimation;
	}
}
/*
namespace RE
{

	CombatAnimation* CombatAnimation::Ctor(Actor* a_actor, ANIM a_anim)
	{
		using func_t = CombatAnimation*(CombatAnimation*, Actor*, ANIM);
		REL::Relocation<func_t> func{ RELOCATION_ID(43235, 0) };
		auto combatAnimaiton = func(this, a_actor, a_anim);
		stl::emplace_vtable<CombatAnimation>(combatAnimaiton);
		return combatAnimaiton;
	}

	CombatAnimation* CombatAnimation::Ctor(Actor* a_actor, TESObjectREFR* a_target, ANIM a_anim)
	{
		using func_t = CombatAnimation*(CombatAnimation*, Actor*, TESObjectREFR*, ANIM);
		REL::Relocation<func_t> func{ RELOCATION_ID(43236, 0) };
		return func(this, a_actor, a_target, a_anim);
	}

	CombatAnimation* CombatAnimation::Ctor(Actor* a_actor, BGSAction* a_action)
	{
		using func_t = CombatAnimation*(CombatAnimation*, Actor * actor, BGSAction*);
		REL::Relocation<func_t> func{ RELOCATION_ID(43237, 0) };
		return func(this, a_actor, a_action);
	}

	CombatAnimation* CombatAnimation::Create(Actor* a_actor, CombatAnimation::ANIM a_anim)
	{
		auto combatAnimation = malloc<CombatAnimation>();
		std::memset(reinterpret_cast<void*>(combatAnimation), 0, sizeof(CombatAnimation));
		if (combatAnimation) {
			combatAnimation->Ctor(a_actor, a_anim);
		}
		return combatAnimation;
	}

	CombatAnimation* CombatAnimation::Create(Actor* a_actor, BGSAction* a_action)
	{
		auto combatAnimation = malloc<CombatAnimation>();
		std::memset(reinterpret_cast<void*>(combatAnimation), 0, sizeof(CombatAnimation));
		if (combatAnimation) {
			combatAnimation->Ctor(a_actor, a_action);
		}
		return combatAnimation;
	}

	bool CombatAnimation::Execute(Actor* a_actor, CombatAnimation::ANIM a_anim)
	{
		using func_t = bool(Actor*, CombatAnimation::ANIM);
		REL::Relocation<func_t> func{ RELOCATION_ID(43245, 0) };
		return func(a_actor, a_anim);
	}

	bool CombatAnimation::Execute(Actor* a_actor, TESObjectREFR* a_target, CombatAnimation::ANIM a_anim)
	{
		using func_t = bool(Actor*, TESObjectREFR*, CombatAnimation::ANIM);
		REL::Relocation<func_t> func{ RELOCATION_ID(43246, 0) };
		return func(a_actor, a_target, a_anim);
	}

	bool CombatAnimation::Check()
	{
		using func_t = decltype(&CombatAnimation::Check);
		REL::Relocation<func_t> func{ RELOCATION_ID(43238, 0) };
		return func(this);
	}

	bool CombatAnimation::GetEventData(const BSFixedString& event_name, float& event_time)
	{
		using func_t = bool(CombatAnimation*, const BSFixedString&, float&);
		REL::Relocation<func_t> func{ RELOCATION_ID(43240, 0) };
		return func(this, event_name, event_time);
	}

	bool CombatAnimation::GetEventData(const BSFixedString& event_name, float& event_time, NiPoint3& translation)
	{
		using func_t = bool(CombatAnimation*, const BSFixedString&, float&, NiPoint3&);
		REL::Relocation<func_t> func{ RELOCATION_ID(43241, 0) };
		return func(this, event_name, event_time, translation);
	}

	float CombatAnimation::GetEventTime(const BSFixedString& event_name)
	{
		using func_t = decltype(&CombatAnimation::GetEventTime);
		REL::Relocation<func_t> func{ RELOCATION_ID(43243, 0) };
		return func(this, event_name);
	}

	float CombatAnimation::GetLength()
	{
		using func_t = decltype(&CombatAnimation::GetLength);
		REL::Relocation<func_t> func{ RELOCATION_ID(43244, 0) };
		return func(this);
	}

	bool CombatAnimation::GetTranslation(NiPoint3& translation)
	{
		using func_t = decltype(&CombatAnimation::GetTranslation);
		REL::Relocation<func_t> func{ RELOCATION_ID(43242, 0) };
		return func(this, translation);
	}

	bool CombatAnimation::LoadClipData()
	{
		using func_t = decltype(&CombatAnimation::LoadClipData);
		REL::Relocation<func_t> func{ RELOCATION_ID(43247, 0) };
		return func(this);
	}
}
*/