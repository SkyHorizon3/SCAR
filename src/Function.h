#pragma once

namespace SCAR
{
	float GetGameSettingFloat(const std::string a_name, const float a_default);

	class AttackRangeCheck
	{
	public:
		static bool CheckPathing(RE::Actor* a_attacker, RE::Actor* a_target);

		static bool WithinAttackRange(RE::Actor* a_attacker, RE::Actor* a_targ, float max_distance, float min_distance, float a_startRadian, float a_endRadian);

		static void DrawOverlay(RE::Actor* a_attacker, RE::Actor* a_targ, float max_distance, float min_distance, float a_startRadian, float a_endRadian);
	};

	inline bool CanNavigateToPosition(RE::Actor* a_this, const RE::NiPoint3& a_pos, const RE::NiPoint3& a_new_pos, float a_speed, float a_distance)
	{
		using func_t = decltype(&CanNavigateToPosition);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46050, 47314) };
		return func(a_this, a_pos, a_new_pos, a_speed, a_distance);
	}

}
