#include "Hook_AttackCombo.h"
#include "DataHandler.h"
#include "Function.h"

namespace SCAR
{
	static bool ShouldNextAttack(const std::string& a_payload)
	{
		if (a_payload.empty())
			return true;

		clib_util::RNG rng;
		return std::atoi(a_payload.c_str()) >= rng.generate(0.f, 100.f);
	}

	static bool PerformSCARAttack(RE::Actor* a_attacker, RE::Actor* a_targ, RE::hkbClipGenerator* a_clip, RE::CombatBehaviorContextMelee* a_context)
	{
		if (a_clip) {
			if (a_targ && a_attacker->GetActorRuntimeData().currentProcess && !a_attacker->IsPlayerRef() && std::to_underlying(a_attacker->CalculateLOS(a_targ, RE::NI_TWO_PI)) > 0 && AttackRangeCheck::CheckPathing(a_attacker, a_targ)) {
				SKSE::log::debug("Find SCAR Action Data in clip \"{}\" of \"{}\"", a_clip->animationName.c_str(), a_attacker->GetName());

				auto dataArr = DataHandler::GetSCARActionData(a_clip);
				std::ranges::sort(dataArr.begin(), dataArr.end(), SCARActionData::SortByWeight);
				for (auto& data : dataArr) {
					if (data.PerformSCARAction(a_attacker, a_targ, a_context, a_clip))
						return true;
				}
			}
		}

		return false;
	}

	EventResult AnimEventHook::ProcessEvent(RE::BSTEventSink<RE::BSAnimationGraphEvent>* a_sink, RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource)
	{
		const auto holder = a_event->holder;
		auto actor = holder ? holder->As<RE::Actor>() : nullptr;
		if (!a_event || !actor)
			return _ProcessEvent(a_sink, a_event, a_eventSource);

		auto& actorRuntime = actor->GetActorRuntimeData();
		auto combatTarg = actorRuntime.currentCombatTarget.get();
		auto highProcess = actorRuntime.currentProcess ? actorRuntime.currentProcess->high : nullptr;

		if (highProcess && combatTarg && _strcmpi("SCAR_ComboStart", a_event->tag.c_str()) == 0 && actor->IsAttacking() && ShouldNextAttack(a_event->payload.c_str())) {
			auto scarClip = DataHandler::GetSCARDataClip(actor);
			auto combatbehaviorCtrl = actorRuntime.combatController ? actorRuntime.combatController->behaviorController : nullptr;
			if (scarClip && combatbehaviorCtrl) {
				for (auto thread : combatbehaviorCtrl->activeThreads) {
					auto currentNode = const_cast<RE::CombatBehaviorTreeNode*>(thread->currentNode);
					if (thread && currentNode) {
						const auto nodeName = currentNode->GetName();
						if (_strcmpi(nodeName.c_str(), "attack") == 0) {
							auto context = thread->GetCurrentObject<RE::CombatBehaviorContextMelee>();
							if (context) {
								PerformSCARAttack(actor, combatTarg.get(), scarClip, context);
								break;
							}
						}
					}
				}
			}
		}

		return _ProcessEvent(a_sink, a_event, a_eventSource);
	}

}
