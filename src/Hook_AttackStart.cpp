#include "Hook_AttackStart.h"
#include "DataHandler.h"
#include "Function.h"

namespace SCAR
{
	static bool PerformSCARAttack(RE::Actor* a_attacker, RE::Actor* a_targ, RE::hkbClipGenerator* a_clip, RE::CombatBehaviorContextMelee* a_context)
	{
		if (!a_clip || !a_targ || !a_attacker || !a_context || !a_context->combatattackdatas.size())
			return false;

		const auto delayTime = "fCombatAttackAnimationDrivenDelayTime"_gs;
		const float delayTimeValue = delayTime.has_value() ? *delayTime : 1.5f;

		//Reproduce bethesda 's stupid cooldown timer
		if (RE::AITimer::QTimer() - a_context->finishedAttackTime.timeStamp <= delayTimeValue && a_attacker->IsPathing()) {
			return false;
		}

		if (a_attacker->GetActorRuntimeData().currentProcess && !a_attacker->IsPlayerRef() && std::to_underlying(a_attacker->CalculateLOS(a_targ, RE::NI_TWO_PI)) > 0 && AttackRangeCheck::CheckPathing(a_attacker, a_targ)) {
			SKSE::log::debug("Find SCAR Action Data in clip \"{}\" of \"{}\"", a_clip->animationName.c_str(), a_attacker->GetName());

			auto dataArr = DataHandler::GetSCARActionData(a_clip);
			std::ranges::sort(dataArr.begin(), dataArr.end(), SCARActionData::SortByWeight);
			for (auto& data : dataArr) {
				if (data.PerformSCARAction(a_attacker, a_targ, a_context, a_clip))
					return true;
			}
		}

		return false;
	}

	// something is wrong in clib ng with these, but I don't care about fixing AI slop
	static RE::Actor* GetAttacker()
	{
		using func_t = decltype(&GetAttacker);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46264, 47519) };
		return func();
	}

	static RE::Actor* GetTarget()
	{
		using func_t = decltype(&GetTarget);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46265, 47520) };
		return func();
	}

	bool AIAttackStartHook::StartAttack(RE::CombatBehaviorContextMelee* a_context)
	{
		const auto attacker = GetAttacker();
		const auto target = GetTarget();
		const auto scarClip = attacker ? DataHandler::GetSCARDataClip(attacker) : nullptr;
		if (scarClip && target) {
			return PerformSCARAttack(attacker, target, scarClip, a_context);
		}

		return _StartAttack(a_context);
	}
}