#include "Function.h"
#include "DataHandler.h"
#include "DebugAPI/DebugAPI.h"

namespace SCAR
{
	static bool CheckStraightPath(RE::TESObjectREFR* a_ref, const RE::NiPoint3& a_startPos, RE::NiPoint3& a_endPos, float a_speed, float a_minDistance)
	{
		using func_t = decltype(&CheckStraightPath);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46050, 47314) };
		return func(a_ref, a_startPos, a_endPos, a_speed, a_minDistance);
	}

	bool AttackRangeCheck::CheckPathing(RE::Actor* a_attacker, RE::Actor* a_target)
	{
		if (!a_attacker || !a_target)
			return false;

		const auto& targetRuntime = a_target->GetActorRuntimeData();
		const auto& attackerRuntime = a_attacker->GetActorRuntimeData();
		const auto target3D = a_target->Get3D();
		const auto attacker3D = a_attacker->Get3D();
		if (!attacker3D || !target3D || !targetRuntime.currentProcess || !attackerRuntime.currentProcess)
			return false;

		constexpr auto GetMeleeWeaponRange = [](const RE::Actor::ACTOR_RUNTIME_DATA& a_actorRuntime) -> float {
			float result = 0.0f;

			auto combatCtrl = a_actorRuntime.combatController;
			auto combatInv = combatCtrl ? combatCtrl->inventory : nullptr;
			if (combatInv) {
				for (const auto& item : combatInv->equippedItems) {
					if (item.item && item.item->GetType() == RE::CombatInventoryItem::TYPE::kMelee) {
						auto range = item.item->GetMaxRange();
						if (range > result)
							result = range;
					}
				}
			}

			return result;
		};

		auto attackerPos = attacker3D->world.translate;
		auto targPos = a_target->Is3rdPersonVisible() ? target3D->world.translate : a_target->GetPosition();
		auto matrix = attacker3D->world.rotate;

		RE::NiMatrix3 invMatrix = matrix.Transpose();

		auto localVector = invMatrix * (targPos - attackerPos);
		auto localDistance = std::sqrtf(localVector.x * localVector.x + localVector.y * localVector.y);
		if (localDistance <= GetMeleeWeaponRange(attackerRuntime) + a_target->GetBoundRadius())
			return true;

		return CheckStraightPath(a_attacker, a_attacker->GetPosition(), a_target->data.location, 2.0f, a_attacker->GetBoundRadius());
	}

	bool AttackRangeCheck::WithinAttackRange(RE::Actor* a_attacker, RE::Actor* a_targ, float max_distance, float min_distance, float a_startRadian, float a_endRadian)
	{
		if (!a_attacker || !a_targ || !a_attacker->Get3D() || !a_targ->Get3D())
			return false;

		max_distance += a_targ->GetBoundRadius();
		if (min_distance > 0.f)
			min_distance += a_targ->GetBoundRadius() + a_attacker->GetBoundRadius();

		auto attackerPos = a_attacker->Get3D()->world.translate;
		auto targPos = a_targ->Is3rdPersonVisible() ? a_targ->Get3D()->world.translate : a_targ->GetPosition();
		auto matrix = a_attacker->Get3D()->world.rotate;

		RE::NiMatrix3 invMatrix = matrix.Transpose();

		auto GetAabbTopBottomHeight = [](RE::Actor* a_actor, float& TopHeight, float& BottomHeight) -> bool {
			if (a_actor->Is3rdPersonVisible()) {
				ObjectBound bound;
				if (Util::GetBBCharacter(a_actor, bound)) {
					TopHeight = std::max(bound.worldBoundMin.z, bound.worldBoundMax.z);
					BottomHeight = std::min(bound.worldBoundMin.z, bound.worldBoundMax.z);
					return true;
				}
			} else {
				TopHeight = a_actor->GetPositionZ() + a_actor->GetBoundMax().z;
				BottomHeight = a_actor->GetPositionZ();
				return true;
			}

			return false;
		};

		float attackerBottomHeight, attackerTopHeight, targBottomHeight, targTopHeight;
		if (!GetAabbTopBottomHeight(a_attacker, attackerTopHeight, attackerBottomHeight) || !GetAabbTopBottomHeight(a_targ, targTopHeight, targBottomHeight))
			return false;

		auto CheckHeight = [](const float attackerBottomHeight, const float attackerTopHeight, const float targBottomHeight, const float targTopHeight) -> bool {
			return (attackerTopHeight >= targTopHeight && attackerBottomHeight <= targTopHeight) || (attackerTopHeight >= targBottomHeight && attackerBottomHeight <= targBottomHeight) || (attackerTopHeight <= targTopHeight && attackerBottomHeight >= targBottomHeight);
		};

		if (!CheckHeight(attackerBottomHeight, attackerTopHeight, targBottomHeight, targTopHeight))
			return false;

		auto localVector = invMatrix * (targPos - attackerPos);

		auto localDistance = std::sqrtf(localVector.x * localVector.x + localVector.y * localVector.y);
		auto localAngle = std::atan2f(localVector.x, localVector.y);
		if (localAngle < -RE::NI_PI)
			localAngle += 2 * RE::NI_PI;
		else if (localAngle > RE::NI_PI)
			localAngle -= 2 * RE::NI_PI;

		const bool withInAngle = a_startRadian < a_endRadian ? localAngle >= a_startRadian && localAngle <= a_endRadian : !(localAngle >= a_endRadian && localAngle <= a_startRadian);

		return localDistance <= max_distance && localDistance >= min_distance && withInAngle;
	}

	void AttackRangeCheck::DrawOverlay(RE::Actor* a_attacker, RE::Actor* a_targ, float max_distance, float min_distance, float a_startRadian, float a_endRadian)
	{
		auto dataHandler = DataHandler::GetSingleton();
		if (!dataHandler || !dataHandler->settings || !dataHandler->settings->enableDebugOverlay || REL::Module::IsVR() || !dataHandler->trueHUD_API)
			return;

		if (!a_attacker || !a_targ || !a_attacker->Get3D() || !a_targ->Get3D())
			return;

		constexpr float time = 1.f;
		constexpr uint32_t redColor = 0xFF0000FF;
		constexpr uint32_t greenColor = 0x00FF00FF;
		constexpr uint32_t yellowColor = 0xFFFF00FF;

		auto attackerPos = a_attacker->Get3D()->world.translate;
		auto targPos = a_targ->Is3rdPersonVisible() ? a_targ->Get3D()->world.translate : a_targ->GetPosition();
		auto matrix = a_attacker->Get3D()->world.rotate;

		RE::NiMatrix3 invMatrix = matrix.Transpose();

		auto localVector = invMatrix * (targPos - attackerPos);
		auto targCenter = attackerPos + matrix * RE::NiPoint3(localVector.x, localVector.y, 0.f);

		dataHandler->trueHUD_API->DrawLine(attackerPos, targCenter, time, yellowColor);

		dataHandler->trueHUD_API->DrawArc(attackerPos, max_distance, a_startRadian, a_endRadian, matrix, 16, time, greenColor);
		dataHandler->trueHUD_API->DrawArc(attackerPos, min_distance, a_startRadian, a_endRadian, matrix, 16, time, redColor);

		auto axis_x = RE::NiPoint3(matrix.entry[0][0], matrix.entry[0][1], matrix.entry[0][2]), axis_y = RE::NiPoint3(matrix.entry[1][0], matrix.entry[1][1], matrix.entry[1][2]);
		dataHandler->trueHUD_API->DrawCircle(targCenter, axis_x, axis_y, a_targ->GetBoundRadius(), 26, time, yellowColor);
	}

}
